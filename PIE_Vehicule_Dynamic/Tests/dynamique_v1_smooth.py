import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from scipy.signal import savgol_filter

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

# === Get distance between two points ===
def get_dist(lat1, lon1, lat2, lon2):
    return np.hypot(lat2 - lat1, lon2 - lon1) * 111000  # approx meters

# === Load CSV file ===
def load_csv(file_path):
    df = pd.read_csv(file_path)
    return list(zip(df['longy'], df['longx'], df['alt']))

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

# === Speed simulation from a given track data ===
def simulate_speed(track_data, P_max=2000, Max_speed=20, Min_speed=5, a_brake_max=2.0):
    curvatures = compute_curvature(track_data)
    n = len(track_data)
    speeds = [Min_speed]
    for i in range(1, n):
        lat1, lon1, ele1 = track_data[(i - 1) % n]
        lat2, lon2, ele2 = track_data[i % n]
        dist = get_dist(lat1, lon1, lat2, lon2)
        v_prev = max(speeds[-1], Min_speed)

        # --- Max possible speed with full power ---
        v_max_power = np.sqrt(v_prev**2 + 2 * (P_max / (M * v_prev)) * dist)

        # --- Max allowed speed in corner ---
        R_curve = curvatures[i]
        if R_curve < np.inf:
            v_max_curve = np.sqrt(mu * g * R_curve)
        else:
            v_max_curve = Max_speed

        # --- Braking limit ---
        v_brake_limit = np.sqrt(max(v_prev**2 - 2 * a_brake_max * dist, Min_speed**2))

        # --- Final speed (considering power, braking, and cornering) ---
        v_target = min(v_max_power, v_max_curve)
        v_new = max(v_target, v_brake_limit)
        v_new = np.clip(v_new, Min_speed, Max_speed)
        speeds.append(v_new)

    # Wrap continuity
    speeds[0] = speeds[-1]
    return speeds

# === Multiple start simulation and envelope max for speed ===
def compute_envelope_speed(track_data, num_rotations=10):
    n = len(track_data)
    all_speeds = np.zeros((num_rotations, n))
    for k in range(num_rotations):
        offset = (k * n) // num_rotations
        rotated_track = track_data[offset:] + track_data[:offset]
        speeds = simulate_speed(rotated_track)
        all_speeds[k] = speeds[-offset:] + speeds[:-offset]
    max_speeds = np.max(all_speeds, axis=0)
    window = min(len(max_speeds) // 2 * 2 + 1, 15)
    smoothed = savgol_filter(max_speeds, window_length=window, polyorder=2, mode='wrap')
    return list(range(n)), smoothed

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

        powers.append(power)

    return powers

# === Main ===
if __name__ == "__main__":
    track_data = load_csv("continuous_path_data.csv")
    offset = 0
    track_data = track_data[-offset:] + track_data[:-offset]  # rotate the track data
    positions, envelope_speeds = compute_envelope_speed(track_data, num_rotations=len(track_data))
    envelope_powers = compute_powers(envelope_speeds, track_data)
    lap_time = 1271.93 / (np.mean(envelope_speeds)) # lap lenght from the shortest path search

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
    plt.plot(positions, envelope_speeds * 3.6, label="Continuous optimal speed", color='blue')
    plt.xlabel("Position on the track")
    plt.ylabel("Speed (km/h)")
    plt.title(f"Rotation-invariant optimal speed (lap made in {lap_time:.2f} s)")
    plt.legend()
    plt.grid()

    plt.subplot(3, 1, 3)
    plt.plot(positions, envelope_powers, label="Engine power", color='green')
    plt.xlabel("Position on the track")
    plt.ylabel("Power (kW)")
    plt.title(f"Engine power on track (mean : {np.mean(envelope_powers):.2f} kW)")
    plt.legend()
    plt.grid()

    plt.tight_layout()
    plt.savefig("V1_smooth_speed_and_power.png")

