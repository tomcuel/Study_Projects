import matplotlib.pyplot as plt
import random


# getting the track data
file_path = "Data/track_data.csv"
with open(file_path, "r") as file:
    lines = file.read().strip().split("\n")
lines = lines[1:]
track_points = []
for line in lines:
    listed = line.strip().split(",")
    alt, utmx, utmy, longx, longy = float(listed[1]), float(listed[2]), float(listed[3]), float(listed[4]), float(listed[5])
    track_points.append((alt, utmx, utmy, longx, longy))
# center the data around the middle of the track
utmx_median = sum([utmx for _, utmx, _, _, _ in track_points]) / len(track_points)
utmy_median = sum([utmy for _, _, utmy, _, _ in track_points]) / len(track_points)
longx_median = sum([longx for _, _, _, longx, _ in track_points]) / len(track_points)
longy_median = sum([longy for _, _, _, _, longy in track_points]) / len(track_points)
for i, (alt, utmx, utmy, longx, longy) in enumerate(track_points):
    track_points[i] = (alt, utmx - utmx_median, utmy - utmy_median, longx - longx_median, longy - longy_median)
with open("Data/track_data_centered.csv", "w") as file:
    file.write("id,alt,utmx_norm, utmy_norm, longx_norm, longy_norm\n")
    for i, (alt, utmx, utmy, longx, longy) in enumerate(track_points):
        file.write(f"{i},{alt},{utmx},{utmy},{longx},{longy}\n")


# choosing the start point
start_point = track_points[0][1:]
# placing the vehicle randomly
random_vehicle_position = random.choice(track_points)[1:]


# plotting the track based on the UTM coordinates
plt.figure(figsize=(10, 5))
track_x, track_y = [x for _, x, _, _, _ in track_points], [y for _, _, y, _, _ in track_points]
plt.plot(track_x, track_y, label="Track", color="blue")
# smaller green circle for the start point
departure_radius = 10
plt.scatter(start_point[0], start_point[1], color='green', s=departure_radius**2, label="Start", edgecolors='black', zorder=5)
# bigger red circle for the vehicle
vehicle_radius = 14
plt.scatter(random_vehicle_position[0], random_vehicle_position[1], color='red', s=vehicle_radius**2, label="Vehicule", edgecolors='black', zorder=5)
plt.title("Track based on centered UTM Coordinates")
plt.xlabel("x (meters)")
plt.ylabel("y (meters)")
plt.legend()
plt.grid(True, linestyle="--", color="gray")
plt.gca().set_facecolor('white') 
plt.gca().spines['top'].set_linewidth(2) 
plt.gca().spines['right'].set_linewidth(2)  
plt.gca().spines['left'].set_linewidth(2)  
plt.gca().spines['bottom'].set_linewidth(2) 
plt.savefig("Visuals/track_data_utm.png")


# plotting the track based on the latitude and longitude coordinates
plt.figure(figsize=(10, 5))
track_x, track_y = [x for _, _, _, x, _ in track_points], [y for _, _, _, _, y in track_points]
plt.plot(track_x, track_y, label="Piste", color="blue")
# smaller green circle for the start point
departure_radius = 10
plt.scatter(start_point[2], start_point[3], color='green', s=departure_radius**2, label="Départ", edgecolors='black', zorder=5)
# bigger red circle for the vehicle
vehicle_radius = 14
plt.scatter(random_vehicle_position[2], random_vehicle_position[3], color='red', s=vehicle_radius**2, label="Véhicule", edgecolors='black', zorder=5)
plt.title("Track based on centered Latitude and Longitude")
plt.xlabel("longitude")
plt.ylabel("latitude")
plt.legend()
plt.grid(True, linestyle="--", color="gray")
plt.gca().set_facecolor('white') 
plt.gca().spines['top'].set_linewidth(2) 
plt.gca().spines['right'].set_linewidth(2)  
plt.gca().spines['left'].set_linewidth(2)  
plt.gca().spines['bottom'].set_linewidth(2) 
plt.savefig("Visuals/track_data_latlon.png")
