import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from scipy.optimize import minimize

# === Parameters ===
M = 100  # kg
m_roue = 1  # kg
Cx = 0.12
Sf = 0.3
rho_air = 1.2
Crr = 0.0015
g = 9.81
mu = 0.8
r_roue = 0.3
eta_transmission = 0.9
P_max = 2000  # W
Max_speed = 20  # m/s
Min_speed = 5  # m/s
a_brake_max = 2.0  # m/s²
a_max = 0.5 # m/s²
T_lap = 90  # Target lap time in seconds

# === Load CSV file ===
def load_csv(file_path):
    df = pd.read_csv(file_path)
    mean_utm_x = df['utmx'].mean()
    mean_utm_y = df['utmy'].mean()
    df['utmx'] -= mean_utm_x
    df['utmy'] -= mean_utm_y
    return list(zip(df['utmy'], df['utmx'], df['alt']))

# === Get distance between two points ===
def get_dist(x1, y1, x2, y2):
    return np.sqrt((x2 - x1)**2 + (y2 - y1)**2)

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

# === Preprocess track data ===
def preprocess_track(track_data):
    n = len(track_data)
    distances = np.zeros(n)
    alt_diff = np.zeros(n)
    cos_slopes = np.zeros(n)
    sin_slopes = np.zeros(n)
    curvatures = compute_curvature(track_data)
    for i in range(n):
        x1, y1, ele1 = track_data[i % n]
        x2, y2, ele2 = track_data[(i + 1) % n]
        dist = get_dist(x1, y1, x2, y2)
        alt_diff[i] = ele2 - ele1
        slope_angle = np.arctan2(ele2 - ele1, dist) if dist > 0 else 0.0
        distances[i] = dist
        cos_slopes[i] = np.cos(slope_angle)
        sin_slopes[i] = np.sin(slope_angle)
    return distances, alt_diff, cos_slopes, sin_slopes, curvatures

# === Load and preprocess ===
full_track_data = load_csv("Data/continuous_path_data.csv")
x = 3  # Keep 1 out of every x points
track_data = full_track_data[::x]  # downsampled data
distances, alt_diff, cos_slopes, sin_slopes, curvatures = preprocess_track(track_data)
n = len(track_data)

# === Objective: Total Energy ===
def objective(speeds):
    energy = 0.0
    for i in range(n):
        v = speeds[i]
        v_prev = speeds[(i - 1) % n]
        dist = distances[(i - 1) % n]
        if dist <= 0 or v <= 0 or v_prev <= 0:
            continue

        v_avg = (v + v_prev) / 2
        acc = (v**2 - v_prev**2) / (2 * dist)

        R_aero = 0.5 * rho_air * Cx * Sf * v_avg**2
        R_roll = Crr * M * g * cos_slopes[i]
        R_slope = M * g * sin_slopes[i]
        R_force_acc = (M+4*m_roue) * acc
        R_total = (R_aero + R_roll + R_slope + R_force_acc) / eta_transmission
        power = R_total * v
        energy += power * (dist / v_avg)  # P * dt = E

    return energy

# === Constraints ===
def constraint_lap_time(speeds):
    return T_lap - np.sum(distances / np.maximum(speeds, Min_speed))

def constraint_braking(speeds):
    # Shift speeds forward to get v_{i+1} and v_i
    v_i = speeds
    v_next = np.roll(speeds, -1)
    d = distances  # distance[i] corresponds to segment from i to i+1 (with wraparound)

    acc = (v_next**2 - v_i**2) / (2 * d)
    return a_brake_max + acc  # Must be ≤ 0 → acc ≥ -a_brake_max

def constraint_acceleration(speeds):
    v_i = speeds
    v_next = np.roll(speeds, -1)
    d = distances

    acc = (v_next**2 - v_i**2) / (2 * d)
    return a_max - acc  # Must be ≥ 0 → acc ≤ a_max

def constraint_curvature(speeds):
    v_limit = np.full(n, Max_speed)
    for i in range(n):
        R = curvatures[i]
        if R < np.inf:
            v_limit[i] = min(Max_speed, np.sqrt(mu * g * R))
    return v_limit - speeds

def constraint_overlap(speeds):
    return speeds[0] - speeds[-1]

# === Initial guess ===
initial_guess = np.full(n, (Min_speed + Max_speed) / 2)

# === Bounds ===
bounds = [(Min_speed, Max_speed) for _ in range(n)]

# === Constraints for minimize ===
constraints = [
    {'type': 'eq', 'fun': constraint_lap_time},
    {'type': 'ineq', 'fun': constraint_braking},
    {'type': 'ineq', 'fun': constraint_acceleration},
    {'type': 'ineq', 'fun': constraint_curvature},
    {'type': 'eq', 'fun': constraint_overlap},
]

# === Callback function to monitor iterations ===
def iteration_callback(v):
    print(f"Loop {iteration_callback.counter}")
    iteration_callback.counter += 1
iteration_callback.counter = 0  # initialize counter
# === Solve Optimization ===
res = minimize(
    objective,
    initial_guess,
    method='SLSQP',
    bounds=bounds,
    constraints=constraints,
    options={'disp': True, 'maxiter': 50}, 
    callback=iteration_callback
)

# === Results ===
speeds_opt = res.x

# === Compute power from speed and track data ===
def compute_powers(speeds):
    n = len(speeds)
    powers = np.zeros(n)
    for i in range(n):
        # Current and previous points
        v_prev = speeds[(i - 1) % n]
        v_new = speeds[i % n]
        dist = distances[(i - 1) % n]
        if dist <= 0 or v_new <= 0 or v_prev <= 0:
            continue

        v_avg = (v_new + v_prev) / 2
        acc = (v_new**2 - v_prev**2) / (2 * dist)

        R_aero = 0.5 * rho_air * Cx * Sf * v_avg**2
        R_roll = Crr * M * g * cos_slopes[i]
        R_slope = M * g * sin_slopes[i]
        R_force_acc = (M+4*m_roue) * acc
        R_total = (R_aero + R_roll + R_slope + R_force_acc) / eta_transmission
        power = R_total * v_new
        if power > P_max:
            power = P_max
        if power < 0:
            power = 0
        powers[i] = power/1000  # Convert to kW

    return powers

# === Plotting ===
positions = [i * x for i in range(len(track_data))]
T = 100  # total lap time in seconds
powers = compute_powers(speeds_opt)
lap_time = 1271.93 / (np.mean(speeds_opt)) # lap lenght from the shortest path search

plt.figure(figsize=(12, 8))

# track data
plt.subplot(3, 1, 1)
plt.plot([x[1] for x in full_track_data], [x[0] for x in full_track_data], label="Circuit", color='black')
every_100_indices = range(0, len(full_track_data), 100)
x_vals = [full_track_data[i][1] for i in every_100_indices]
y_vals = [full_track_data[i][0] for i in every_100_indices]
plt.scatter(x_vals, y_vals, color='red', marker='o', label="Point every 100")
for i, (x, y) in enumerate(zip(x_vals, y_vals)):
    plt.text(x, y, str(every_100_indices[i]), fontsize=10, ha='left', va='bottom', color='blue')
plt.xlabel("Latitude")
plt.ylabel("Longitude")
plt.title("Circuit")
plt.legend()
plt.grid()

# speed profile
plt.subplot(3, 1, 2)
plt.plot(positions, speeds_opt * 3.6, label="Continuous optimal speed", color='blue')
plt.xlabel("Position on the track")
plt.ylabel("Speed (km/h)")
plt.title(f"Rotation-invariant optimal speed (lap made in {lap_time:.2f} s)")
plt.legend()
plt.grid()

# engine power
plt.subplot(3, 1, 3)
plt.plot(positions, powers, label="Engine power", color='green')
plt.xlabel("Position on the track")
plt.ylabel("Power (kW)")
plt.title(f"Engine power on track (mean : {np.mean(powers):.2f} kW)")
plt.legend()
plt.grid()

plt.tight_layout()
plt.savefig("Visuals/speeds_and_powers.png")

# === Plot constraints ===
def evaluate_constraints(speeds, tol=1e-3):
    constraint_values = {
        "braking": constraint_braking(speeds),
        "acceleration": constraint_acceleration(speeds),
        "curvature": constraint_curvature(speeds),
    }
    return constraint_values
values = evaluate_constraints(speeds_opt)

fig, axs = plt.subplots(2, 1, figsize=(12, 5), sharex=True)

# Speed profile
axs[0].set_title(f"Lap Time Constraint: Target = {T_lap:.2f}s, Achieved = {lap_time:.2f}s")
axs[0].plot(positions, speeds_opt * 3.6, label="Speed (km/h)", color='blue')
axs[0].set_ylabel("Speed (km/h)")
axs[0].legend()
axs[0].grid(True)

# Constraint values
axs[1].set_title("Constraint Values")
axs[1].plot(positions, values['braking'], label="Braking", color='orange')
axs[1].plot(positions, values['acceleration'], label="Acceleration", color='green')
axs[1].plot(positions, values['curvature'], label="Curvature", color='purple')
axs[1].axhline(0, linestyle='--', color='black')
axs[1].legend()
axs[1].set_ylabel("Constraint Value")
axs[1].grid(True)

plt.xlabel("Track point index")
plt.tight_layout()
plt.savefig("Visuals/constraints.png")

