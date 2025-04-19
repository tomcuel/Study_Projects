import numpy as np
import pandas as pd
from scipy.optimize import minimize
from matplotlib import pyplot as plt

# === Parameters ===
M = 100  # vehicle mass in kg (including driver)
Cx = 0.12  # aerodynamic drag coefficient
Sf = 0.3  # frontal area in m²
rho_air = 1.2  # air density in kg/m³
Crr = 0.0015  # rolling resistance coefficient
g = 9.81  # gravity in m/s²
mu = 0.8  # tire-road friction coefficient
r_roue = 0.3  # radius of the wheels in m
eta_transmission = 0.9  # transmission efficiency
P_max = 1000  # W

# === Load CSV file ===
def load_csv(file_path):
    df = pd.read_csv(file_path)
    return list(zip(df['longy'], df['longx'], df['alt']))

# === Get distance between two points ===
def get_dist(lat1, lon1, lat2, lon2):
    return np.hypot(lat2 - lat1, lon2 - lon1) * 111000  # approx meters

# === Compute curvature radius ===
def compute_curvature(track_data):
    curvatures = np.full(len(track_data), np.inf)
    for i in range(1, len(track_data) - 1):
        x1, y1, _ = track_data[i - 1]
        x2, y2, _ = track_data[i]
        x3, y3, _ = track_data[i + 1]
        a = np.hypot(x2 - x1, y2 - y1)
        b = np.hypot(x3 - x2, y3 - y2)
        c = np.hypot(x3 - x1, y3 - y1)
        s = (a + b + c) / 2
        A = np.sqrt(max(s * (s - a) * (s - b) * (s - c), 0))
        R = (a * b * c) / (4 * A) if A != 0 else np.inf
        curvatures[i] = R
    return curvatures

# === Optimization-based energy minimization ===
def optimize_speed_energy(track_data, T, Min_speed=3, Max_speed=18, a_brake_max=2.0, a_accel_max=2.0):
    n = len(track_data)
    curvatures = compute_curvature(track_data)

    # --- Compute distances and slopes ---
    distances = np.zeros(n)
    slopes = np.zeros(n)
    for i in range(n):
        lat1, lon1, ele1 = track_data[i]
        lat2, lon2, ele2 = track_data[(i + 1) % n]
        dist = get_dist(lat1, lon1, lat2, lon2)
        slope = np.arctan2(ele2 - ele1, dist) if dist != 0 else 0
        distances[i] = dist
        slopes[i] = slope

    # --- Energy to be minimized ---
    def total_energy(v):
        energy = 0.0
        for i in range(n):
            v_i = max(v[i], 1e-3)  # avoid division by zero
            slope = slopes[i]
            R_aero = 0.5 * rho_air * Cx * Sf * v_i**2
            R_roll = Crr * M * g * np.cos(slope)
            R_slope = M * g * np.sin(slope)
            R_total = R_aero + R_roll + R_slope
            power = R_total * v_i / eta_transmission
            energy += power * (distances[i] / v_i)  # P * dt = E
        return energy

    # --- Time constraint: total lap time = T ---
    def time_constraint(v):
        return T - np.sum(distances / v)

    constraints = [{'type': 'eq', 'fun': time_constraint}]

    # --- Bounds from curvature and min/max speed ---
    bounds = []
    for R in curvatures:
        if R < np.inf:
            v_max_curve = np.sqrt(mu * g * R)
        else:
            v_max_curve = Max_speed
        v_upper = min(Max_speed, v_max_curve)
        v_lower = min(Min_speed, v_upper)  # ensure v_lower <= v_upper
        bounds.append((v_lower, v_upper))

    # --- Initial guess: constant speed to meet time T ---
    total_dist = np.sum(distances)
    v_guess = total_dist / T
    v0 = np.clip(np.full(n, v_guess), Min_speed, Max_speed)

    # --- Callback function to monitor iterations ---
    def iteration_callback(v):
        print(f"Loop {iteration_callback.counter}")
        iteration_callback.counter += 1
    iteration_callback.counter = 0  # initialize counter

    # --- Solve optimization ---
    result = minimize(
        total_energy,
        v0,
        bounds=bounds,
        constraints=constraints,
        method='SLSQP',
        options={'disp': True, 'maxiter': 100},
        callback=iteration_callback
    )
    return result.x

# === Compute power from speed and track data ===
def compute_powers(speeds, track_data):
    n = len(speeds)
    powers = []
    for i in range(n):
        # Current and previous points
        v_prev = speeds[(i - 1) % n]
        v_new = speeds[i % n]
        lat1, lon1, ele1 = track_data[(i - 1) % n]
        lat2, lon2, ele2 = track_data[i % n]
        dist = get_dist(lat1, lon1, lat2, lon2)

        if dist == 0:
            slope = 0
        else:
            slope = np.arctan2((ele2 - ele1), dist)

        # --- Resistance forces ---
        R_aero = 0.5 * rho_air * Cx * Sf * v_prev**2
        R_roll = Crr * M * g * np.cos(slope)
        R_pente = M * g * np.sin(slope)
        R_total = R_aero + R_roll + R_pente

        # --- Acceleration ---
        acceleration = (v_new**2 - v_prev**2) / (2 * dist) if dist > 0 else 0
        F_inertia = M * acceleration

        if v_new < v_prev:
            power = 0.0  # Braking or coasting: no engine power needed
        else:
            P_total = ((R_total + F_inertia) * v_prev) / eta_transmission  # W
            power = max(P_total / 1000, 0)  # convert to kW and clamp to 0

        powers.append(min(power, P_max/1000))

    return powers

# === Main ===
if __name__ == "__main__":
    track_data = load_csv("continuous_path_data.csv")
    x = 5  # Keep 1 out of every x points
    short_track_data = track_data[::x]  # downsampled data
    positions = list(range(len(short_track_data)))
    T = 100  # total lap time in seconds
    optimal_speeds = optimize_speed_energy(short_track_data, T)
    powers = compute_powers(optimal_speeds, short_track_data)

    lap_time = 1271.93 / (np.mean(optimal_speeds)) # lap lenght from the shortest path search

    plt.figure(figsize=(12, 8))

    plt.subplot(3, 1, 1)
    plt.plot([x[1] for x in track_data], [x[0] for x in track_data], label="Circuit", color='black')
    every_100_indices = range(0, len(track_data), 100)
    x_vals = [track_data[i][1] for i in every_100_indices]
    y_vals = [track_data[i][0] for i in every_100_indices]
    plt.scatter(x_vals, y_vals, color='red', marker='o', label="Point every 100")
    for i, (x, y) in enumerate(zip(x_vals, y_vals)):
        plt.text(x, y, str(every_100_indices[i]), fontsize=10, ha='left', va='bottom', color='blue')
    plt.xlabel("Latitude")
    plt.ylabel("Longitude")
    plt.title("Circuit")
    plt.legend()
    plt.grid()

    plt.subplot(3, 1, 2)
    plt.plot(positions, optimal_speeds * 3.6, label="Continuous optimal speed", color='blue')
    plt.xlabel("Position on the track")
    plt.ylabel("Speed (km/h)")
    plt.title(f"Rotation-invariant optimal speed (lap made in {lap_time:.2f} s)")
    plt.legend()
    plt.grid()

    plt.subplot(3, 1, 3)
    plt.plot(positions, powers, label="Engine power", color='green')
    plt.xlabel("Position on the track")
    plt.ylabel("Power (kW)")
    plt.title(f"Engine power on track (mean : {np.mean(powers):.2f} kW)")
    plt.legend()
    plt.grid()

    plt.tight_layout()
    plt.savefig("V1_minimize.png")



