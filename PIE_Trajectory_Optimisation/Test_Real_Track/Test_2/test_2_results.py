import matplotlib.pyplot as plt
import re

# getting the track datas
file_path_inside = "inside_track_2.txt"
with open(file_path_inside, "r") as file:
    lines_inside = file.read().strip().split("\n")
track_points_inside = []
for line in lines_inside:
    listed = line.strip().split(",")
    alt, utmx, utmy = 0.0, float(listed[0]), float(listed[1])
    track_points_inside.append((alt, utmx, utmy))

file_path_outside = "outside_track_2.txt"
with open(file_path_outside, "r") as file:
    lines_outside = file.read().strip().split("\n")
track_points_outside = []
for line in lines_outside:
    listed = line.strip().split(",")
    alt, utmx, utmy = 0.0, float(listed[0]), float(listed[1])
    track_points_outside.append((alt, utmx, utmy))

# plotting the track centerline
file_path_centerline = "track_data_centered_test_2.csv"
with open(file_path_centerline, "r") as file:
    lines_centerline = file.read().strip().split("\n")
lines_centerline = lines_centerline[1:]
track_points_centerline = []
for line in lines_centerline:
    listed = line.strip().split(",")
    alt, utmx, utmy = 0.0, float(listed[2]), float(listed[3])
    track_points_centerline.append((alt, utmx, utmy))
track_points_centerline.append(track_points_centerline[0])

# shortest path points
def extract_unique_points(file_name):
    unique_points = []
    seen = set()
    with open(file_name, 'r') as file:
        for line in file:
            matches = re.findall(r'\((-?\d*\.?\d*),(-?\d*\.?\d*)\)', line)
            for match in matches:
                point = tuple(map(float, match))
                if point not in seen:
                    unique_points.append(point)
                    seen.add(point)
    return unique_points
file_name = "path_2.txt"
path_points = extract_unique_points(file_name)


plt.figure(figsize=(10, 5))

# plotting the different tracks parts 
inside_track_x, inside_track_y = [x for _, x, _ in track_points_inside], [y for _, _, y in track_points_inside]
plt.plot(inside_track_x, inside_track_y, label="Bord intérieur", color="blue")

outside_track_x, outside_track_y = [x for _, x, _ in track_points_outside], [y for _, _, y in track_points_outside]
plt.plot(outside_track_x, outside_track_y, label="Bord intérieur", color="red")

centerline_x, centerline_y = [x for _, x, _ in track_points_centerline], [y for _, _, y in track_points_centerline]
plt.plot(centerline_x, centerline_y, label="Centerline", color="black")

path_x, path_y = [x for x, _ in path_points], [y for _, y in path_points]
plt.plot(path_x, path_y, label="Shortest path", color="green")

plt.title("Track")
plt.xlabel("x (meters)")
plt.ylabel("y (meters)")
plt.legend()
plt.grid(True, linestyle="--", color="gray")
plt.gca().set_facecolor('white') 
plt.gca().spines['top'].set_linewidth(2) 
plt.gca().spines['right'].set_linewidth(2)  
plt.gca().spines['left'].set_linewidth(2)  
plt.gca().spines['bottom'].set_linewidth(2) 
plt.savefig("inside_outside_layout_2.png")
