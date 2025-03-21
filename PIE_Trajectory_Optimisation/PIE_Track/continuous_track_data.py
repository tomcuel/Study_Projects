from math import sqrt, cos, radians
import matplotlib.pyplot as plt



# getting the path data
with open("Data/path_data.csv", "r") as file:
    lines = file.read().strip().split("\n")
lines = lines[1:] # remove the header
path_points = []
for line in lines:
    listed = line.strip().split(",")
    alt, utmx, utmy, longx, longy = float(listed[0]), float(listed[1]), float(listed[2]), float(listed[3]), float(listed[4])
    path_points.append((alt, utmx, utmy, longx, longy))



# approximate meters per degree of latitude
METERS_PER_DEGREE_LAT = 111132
# approximate meters per degree of longitude at a given latitude
def meters_per_degree_longitude(latitude):
    return 111320 * cos(radians(latitude)) 



# generate new path points with points every 1 meter for continuity
new_path_points = []
generation_path_points = path_points + [path_points[0]] # add the first point to the end to close the loop
for i in range(len(generation_path_points) - 1):
    p1 = generation_path_points[i]
    new_path_points.append(p1)
    p2 = generation_path_points[i + 1]

    # direction vector in UTM
    direction = (p2[1] - p1[1], p2[2] - p1[2])  # (Δutmx, Δutmy)
    distance = sqrt(direction[0]**2 + direction[1]**2)
    
    if distance <= 1:
        continue  # skip points that are too close together

    step = (direction[0] / distance, direction[1] / distance)  # step by 1 meter

    # compute meters per degree at the starting latitude
    meters_per_deg_long = meters_per_degree_longitude(p1[4])  # longitude scaling factor
    meters_per_deg_lat = METERS_PER_DEGREE_LAT  # latitude scaling factor

    # compute longitude and latitude step
    long_step = step[0] / meters_per_deg_long  # convert UTM x step to longitude step
    lat_step = step[1] / meters_per_deg_lat  # convert UTM y step to latitude step

    # generate intermediate points
    new_p = (p1[0], p1[1] + step[0], p1[2] + step[1], p1[3] + long_step, p1[4] + lat_step)  

    # while the distance between the new point and the next point is greater than 1 meter, we add the new point to the path
    while sqrt((new_p[1] - p2[1])**2 + (new_p[2] - p2[2])**2) > 1:
        new_path_points.append(new_p)
        new_p = (new_p[0], new_p[1] + step[0], new_p[2] + step[1], new_p[3] + long_step, new_p[4] + lat_step)
    
    new_path_points.append(p2)



# suppress all the points that more than once in the new path points, while keeping the order
new_path_points = list(dict.fromkeys(new_path_points))


# export new path points to a csv file
with open("Data/continuous_path_data.csv", "w") as file:
    file.write("alt,utmx,utmy,longx,longy\n")
    for i, (alt, utmx, utmy, longx, longy) in enumerate(new_path_points):
        file.write(f"{alt},{utmx},{utmy},{longx},{longy}\n")



# extract UTM and Lat/Long data from path_points
num_points = len(path_points)
utmx_vals = [p[1] for p in path_points]
utmy_vals = [p[2] for p in path_points]
long_vals = [p[3] for p in path_points]
lat_vals = [p[4] for p in path_points]

# extract UTM and Lat/Long data from new_path_points
new_num_points = len(new_path_points)
new_utmx_vals = [p[1] for p in new_path_points]
new_utmy_vals = [p[2] for p in new_path_points]
new_long_vals = [p[3] for p in new_path_points]
new_lat_vals = [p[4] for p in new_path_points]


plt.figure(figsize=(12, 5))

# plotting the track based on the utm coordinates to see if there is any difference with the based track center data
plt.subplot(1, 2, 1)
plt.plot(utmx_vals, utmy_vals, marker="o", linestyle="-", markersize=5, color="red", label="Original Path")  # larger red markers
plt.plot(new_utmx_vals, new_utmy_vals, marker="o", linestyle="-", markersize=2, color="blue", label="Interpolated Path")  # smaller blue markers
plt.xlabel("UTM X")
plt.ylabel("UTM Y")
plt.title(f"Track in UTM Coordinates\n(Number of points : {num_points} original, {new_num_points} interpolated)")
plt.axis("equal")  # Keep aspect ratio
plt.legend()

# plotting the track based on the latitude and longitude coordinates to see if there is any difference with the utm coordinates (because conversion could mess things up)
plt.subplot(1, 2, 2)
plt.plot(long_vals, lat_vals, marker="o", linestyle="-", markersize=5, color="red", label="Original Path")  # larger red markers
plt.plot(new_long_vals, new_lat_vals, marker="o", linestyle="-", markersize=2, color="blue", label="Interpolated Path")  # smaller blue markers
plt.xlabel("Longitude")
plt.ylabel("Latitude")
plt.title(f"Track in Latitude/Longitude\n(Number of points : {num_points} original, {new_num_points} interpolated)")
plt.axis("equal")
plt.legend()

plt.tight_layout()
plt.savefig("Visuals/continuous_path_data.png")

