import matplotlib.pyplot as plt
import re


# the first part is here is plot the differents graph to visually see what is going on based on the txt graph and path representations 


# get the data from the graph and shortest path files
def get_data_from_file(graph_file, shortest_path_file, track_center_file):
    with open(graph_file, 'r') as file:
        graph_data = file.read().strip().split('\n')
    graph_data = graph_data[1:] # skip the header


    # getting the obstacles segments
    obstacles = []
    obstacle_pattern = r"Segment : \((-?\d+(?:\.\d+)?(?:e[-+]?\d+)?)\s*,\s*(-?\d+(?:\.\d+)?(?:e[-+]?\d+)?)\) -> \((-?\d+(?:\.\d+)?(?:e[-+]?\d+)?)\s*,\s*(-?\d+(?:\.\d+)?(?:e[-+]?\d+)?)\)"
    graph_data = graph_data[2:] # skip the start and goal points
    while graph_data[0] != 'all points : ':
        matches = re.findall(obstacle_pattern, graph_data[0])
        for match in matches:
            x1, y1 = float(match[0]), float(match[1])
            x2, y2 = float(match[2]), float(match[3])
            obstacles.append(((x1, y1), (x2, y2)))
        graph_data = graph_data[1:]
    graph_data = graph_data[1:] # skip the 'all points : ' line
    

    # getting the points in the grap
    points = {}
    point_pattern = r"\((-?\d+(?:\.\d+)?(?:e[-+]?\d+)?)\s*,\s*(-?\d+(?:\.\d+)?(?:e[-+]?\d+)?)\)"
    while graph_data[0] != 'graph arcs : ':
        match = re.search(point_pattern, graph_data[0])
        if match:
            x = float(match.group(1))
            y = float(match.group(2))
            point = (x, y)
            points[point] = point
        graph_data = graph_data[1:]


    # getting the segments
    segments = []
    # segment_pattern = r"Segment : \((-?\d+(\.\d+)?),(-?\d+(\.\d+)?)\) -> \((-?\d+(\.\d+)?),(-?\d+(\.\d+)?)\)"
    segment_pattern = r"Segment : \((-?\d+(?:\.\d+)?(?:e[-+]?\d+)?)\s*,\s*(-?\d+(?:\.\d+)?(?:e[-+]?\d+)?)\) -> \((-?\d+(?:\.\d+)?(?:e[-+]?\d+)?)\s*,\s*(-?\d+(?:\.\d+)?(?:e[-+]?\d+)?)\)"
    while graph_data :
        matches = re.findall(segment_pattern, graph_data[0])
        for match in matches:
            x1, y1 = float(match[0]), float(match[1]) # First point
            x2, y2 = float(match[2]), float(match[3]) # Second point
            segments.append(((x1, y1), (x2, y2)))
        graph_data = graph_data[1:]

    
    # getting the shortest path segments
    with open(shortest_path_file, 'r') as file:
        graph_data = file.read().strip().split('\n')
    graph_data = graph_data[1:] # skip the header
    shortest_path_segments = []
    while graph_data : # getting the shortest path segments as earlier
        matches = re.findall(segment_pattern, graph_data[0])
        for match in matches:
            x1, y1 = float(match[0]), float(match[1])
            x2, y2 = float(match[2]), float(match[3])
            shortest_path_segments.append(((x1, y1), (x2, y2)))
        graph_data = graph_data[1:]


    # getting the track center points
    with open(track_center_file, "r") as file:
        lines_center = file.read().strip().split("\n")
    lines_center = lines_center[1:] # skip the header
    track_center = []
    for line in lines_center:
        listed = line.strip().split(",")
        alt, utmx, utmy = 0.0, float(listed[0]), float(listed[1])
        track_center.append((alt, utmx, utmy))


    # return the points, segments and shortest path segments
    return points, segments, shortest_path_segments, obstacles, track_center


# save the graph as a png file
def plot_graph(points, segments, shortest_path_segments, obstacles, track_center, filename, with_arcs):

    # create the plot
    plt.figure(figsize=(20, 10))
    need_to_plot_points_coords = True
    if (len(points) > 10):
        need_to_plot_points_coords = False


    # first, plot obstacles (black segments)
    for seg_start, seg_end in segments:
        if (seg_start, seg_end) in obstacles or (seg_end, seg_start) in obstacles:
            color = 'black'  # Obstacles in black
            new_linewidth = 4
            x_values = [seg_start[0], seg_end[0]]
            y_values = [seg_start[1], seg_end[1]]
            plt.plot(x_values, y_values, color=color, linewidth=new_linewidth)
        else :
            if with_arcs:
                color = (0.4, 0.4, 0.4) # Other segments in grey
                x_values = [seg_start[0], seg_end[0]]
                y_values = [seg_start[1], seg_end[1]]
                plt.plot(x_values, y_values, color=color, linewidth=2)


    # then, plot shortest path (red segments) above obstacles and other graph arc
    for seg_start, seg_end in shortest_path_segments:
        color = 'red'  # Shortest path in red
        x_values = [seg_start[0], seg_end[0]]
        y_values = [seg_start[1], seg_end[1]]
        plt.plot(x_values, y_values, color=color, linewidth=2)


    # plot the points
    for point, coords in points.items():
        plt.scatter(coords[0], coords[1], color='blue', s=20)
        if need_to_plot_points_coords: # add labels to the points only if needed
            plt.text(coords[0], coords[1], f'({coords[0]}, {coords[1]})', fontsize=10, ha='right')


    # plot the track center points
    track_center_x, track_center_y = [x for _, x, _ in track_center], [y for _, _, y in track_center]
    plt.plot(track_center_x, track_center_y, color="black")


    # set plot limits
    max_x_coord = max([point[0] for point in points.values()])
    min_x_coord = min([point[0] for point in points.values()])
    max_y_coord = max([point[1] for point in points.values()])
    min_y_coord = min([point[1] for point in points.values()])
    plt.xlim(min_x_coord - 1, max_x_coord + 1)
    plt.ylim(min_y_coord - 1, max_y_coord + 1)
    # Add title and grid
    plt.title("Track with shortest path")
    plt.gca().set_aspect('equal', adjustable='box')
    plt.grid(True)
    # Show the plot
    plt.savefig(filename)


# call the function to save the graph figs
points, segments, shortest_path_segments, obstacles, track_center = get_data_from_file('Data/graph.txt', 'Data/path.txt', 'Data/track_center_points.csv')
plot_graph(points, segments, shortest_path_segments, obstacles, track_center, 'Visuals/track_visual_result.png', False)
plot_graph(points, segments, shortest_path_segments, obstacles, track_center, 'Visuals/track_visual_with_arcs.png', True)




# getting the track data to have the based data to work with to convert back the path to the original coordinates
file_path = "Data/track_data.csv"
with open(file_path, "r") as file:
    lines = file.read().strip().split("\n")
lines = lines[1:] # remove the header
track_points = []
for line in lines:
    listed = line.strip().split(",")
    alt, utmx, utmy, longx, longy = float(listed[1]), float(listed[2]), float(listed[3]), float(listed[4]), float(listed[5])
    track_points.append((alt, utmx, utmy, longx, longy))
# get the data center
utmx_median = sum([utmx for _, utmx, _, _, _ in track_points]) / len(track_points)
utmy_median = sum([utmy for _, _, utmy, _, _ in track_points]) / len(track_points)
longx_median = sum([longx for _, _, _, longx, _ in track_points]) / len(track_points)
longy_median = sum([longy for _, _, _, _, longy in track_points]) / len(track_points)


# getting the path data
with open("Data/path.csv", "r") as file:
    lines = file.read().strip().split("\n")
lines = lines[1:] # remove the header
path_points = []
for line in lines:
    listed = line.strip().split(",")
    alt, utmx, utmy, longx, longy = float(listed[0]), float(listed[1]), float(listed[2]), float(listed[3]), float(listed[4])
    path_points.append((alt, utmx + utmx_median, utmy + utmy_median, longx + longx_median, longy + longy_median))
# write the path data to a file
with open("Data/path_data.csv", "w") as file:
    file.write("alt,utmx,utmy,longx,longy\n")
    for i, (alt, utmx, utmy, longx, longy) in enumerate(path_points):
        file.write(f"{alt},{utmx},{utmy},{longx},{longy}\n")


path_points += [path_points[0]] # close the path
# plotting the track based on the latitude and longitude coordinates and looking for differences with the based track center data 
plt.figure(figsize=(20, 10))
track_x, track_y = [x for _, _, _, x, _ in path_points], [y for _, _, _, _, y in path_points]
plt.plot(track_x, track_y, label="Shortest Path", color="red")
center_track_x, center_track_y = [x for _, _, _, x, _ in track_points], [y for _, _, _, _, y in track_points]
plt.plot(center_track_x, center_track_y, label="Track center", color="blue")
plt.title("Track based on Latitude and Longitude")
plt.xlabel("longitude")
plt.ylabel("latitude")
plt.legend()
plt.grid(True, linestyle="--", color="gray")
plt.gca().set_facecolor('white') 
plt.gca().spines['top'].set_linewidth(2) 
plt.gca().spines['right'].set_linewidth(2)  
plt.gca().spines['left'].set_linewidth(2)  
plt.gca().spines['bottom'].set_linewidth(2) 
plt.savefig("Visuals/track_visual_lat_long.png")

