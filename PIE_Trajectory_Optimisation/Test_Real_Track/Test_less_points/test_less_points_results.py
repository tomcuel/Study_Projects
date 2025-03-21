import matplotlib.pyplot as plt
import re



# get the data from the graph and shortest path files
def get_data_from_file(graph_file, shortest_path_file, track_center_file):
    with open(graph_file, 'r') as file:
        graph_data = file.read().strip().split('\n')
    graph_data = graph_data[1:] # skip the header


    # getting the points
    points = {}
    point_pattern = r"\((-?\d+(?:\.\d+)?(?:e[-+]?\d+)?)\s*,\s*(-?\d+(?:\.\d+)?(?:e[-+]?\d+)?)\)"

    start_point_line = graph_data[0]
    match_start = re.search(point_pattern, start_point_line)
    if match_start:
        x = float(match_start.group(1))
        y = float(match_start.group(2))
        start_point = (x, y)
        points['start'] = start_point

    goal_point_line = graph_data[1]
    match_goal = re.search(point_pattern, goal_point_line)
    if match_goal:
        x = float(match_goal.group(1))
        y = float(match_goal.group(2))
        goal_point = (x, y)
        points['goal'] = goal_point

    
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
    

    # getting the points in the graph other than the start and goal points
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
    track_center = []
    for line in lines_center:
        listed = line.strip().split(",")
        alt, utmx, utmy = 0.0, float(listed[0]), float(listed[1])
        track_center.append((alt, utmx, utmy))


    # return the points, segments and shortest path segments
    return points, segments, shortest_path_segments, obstacles, track_center




# save the graph as a png file
def plot_graph(points, segments, shortest_path_segments, obstacles, track_center, filename):

    # Create the plot
    plt.figure(figsize=(15, 15))

    need_to_plot_points_coords = True
    if (len(points) > 10):
        need_to_plot_points_coords = False

    # First, plot obstacles (black segments)
    for seg_start, seg_end in segments:
        if (seg_start, seg_end) in obstacles or (seg_end, seg_start) in obstacles:
            color = 'black'  # Obstacles in black
            new_linewidth = 4
            x_values = [seg_start[0], seg_end[0]]
            y_values = [seg_start[1], seg_end[1]]
            plt.plot(x_values, y_values, color=color, linewidth=new_linewidth)
        """else :
            color = (0.4, 0.4, 0.4) # Other segments in grey
            x_values = [seg_start[0], seg_end[0]]
            y_values = [seg_start[1], seg_end[1]]
            plt.plot(x_values, y_values, color=color, linewidth=2)"""

    # Then, plot shortest path (red segments) above obstacles and other graph arc
    for seg_start, seg_end in shortest_path_segments:
        color = 'red'  # Shortest path in red
        x_values = [seg_start[0], seg_end[0]]
        y_values = [seg_start[1], seg_end[1]]
        plt.plot(x_values, y_values, color=color, linewidth=2)

    # Plot the points
    for point, coords in points.items():
        if point == 'start':
            plt.scatter(coords[0], coords[1], color='green', s=100, label='Start')
        elif point == 'goal':
            plt.scatter(coords[0], coords[1], color='green', s=100, label='Goal')
        else:
            plt.scatter(coords[0], coords[1], color='blue', s=20)

    # Add labels to the points
    for point, coords in points.items():
        if need_to_plot_points_coords:
            plt.text(coords[0], coords[1], f'({coords[0]}, {coords[1]})', fontsize=10, ha='right')

    # Plot the track center points
    track_center_x, track_center_y = [x for _, x, _ in track_center], [y for _, _, y in track_center]
    plt.plot(track_center_x, track_center_y, label="Track center", color="black")

    # Set plot limits
    max_x_coord = max([point[0] for point in points.values()])
    min_x_coord = min([point[0] for point in points.values()])
    max_y_coord = max([point[1] for point in points.values()])
    min_y_coord = min([point[1] for point in points.values()])
    plt.xlim(min_x_coord - 1, max_x_coord + 1)
    plt.ylim(min_y_coord - 1, max_y_coord + 1)

    # Add title and grid
    plt.title("Graph Representation with Obstacles and Shortest Path")
    plt.gca().set_aspect('equal', adjustable='box')
    plt.grid(True)

    # Add a legend
    plt.legend()

    # Show the plot
    plt.savefig(filename)


# Call the function to save the graph figs
points, segments, shortest_path_segments, obstacles, track_center = get_data_from_file('graph_less_points.txt', 'path_less_points.txt', 'track_center_less_points.txt')
plot_graph(points, segments, shortest_path_segments, obstacles, track_center, 'track_less_points.png')
print('Graph created')

