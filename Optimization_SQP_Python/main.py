import time 
import numpy as np

from auto_SQP_classe import Auto_SQP
from hand_made_SQP_classe import Hand_Made_SQP
from hand_made_SQP_classe_with_constraints_changes import Hand_Made_SQP_Classe_with_Constraints_Changed

# Initial guess for the optimization (x_0, lambda_0)
x_01 = np.array([-1.71, 1.59, 1.82, -0.763, -0.763])
x_02 = np.array([-1.9, 1.82, 2.02, -0.9, -0.9])
# (n=5, m=3 since there is 3 constraints, so 3 lagrange multipliers)
# lambda_0 will be modified in the optimization process, to see how it affects the optimization
lambda_01 = np.zeros(3)

# Load the optimization classes
auto_sqp = Auto_SQP()
hand_made_sqp = Hand_Made_SQP()
hand_made_sqp_with_constraints_changes = Hand_Made_SQP_Classe_with_Constraints_Changed()

# Showing a result progression for the by hand optimization
# method = 1 for auto_sqp, 2 for hand_made_sqp, 3 for hand_made_sqp_with_constraints_changes
def showing_a_result(method, x_0, lambda_0, use_callback):
    print()
    # Run the optimization and measure the time spent
    start_time = time.perf_counter()
    result_x, result_f_value, nb_iter = 0, 0, 0
    if method == 1:
        result_x, result_f_value, nb_iter = auto_sqp.solve(x_0, use_callback)
    elif method == 2:
        result_x, result_f_value, nb_iter = hand_made_sqp.optimize(x_0, lambda_0, use_callback)
    elif method == 3:
        result_x, result_f_value, nb_iter = hand_made_sqp_with_constraints_changes.optimize(x_0, lambda_0, use_callback)
    end_time = time.perf_counter()
    elapsed_time = end_time - start_time  
    if method == 1:
        print("Auto SQP")
    elif method == 2:
        print("Hand Made SQP")
    elif method == 3:
        print("Hand Made SQP with Constraints Changes")
    print(f"The function took {elapsed_time:.6f} seconds to run.")
    print("Optimal Solution : ", result_x)
    print(f"Optimal Objective Value : ", result_f_value)
    print(f"convergence after {nb_iter} iterations\n")

# Result that failed 
# showing_a_result(2, [1, 0, 3, 0, 0], lambda_01, True)
# showing_a_result(1, [1, 0, 3, 0, 0], lambda_01, False)
# Progression to get the result
# showing_a_result(2, x_01, lambda_01, True)

# making a comparaison between the 3 classes for x_01 and x_02 and lambda_0 = [0, 0, 0]
# showing_a_result(1, x_01, lambda_01, False)
# showing_a_result(2, x_01, lambda_01, True)
# showing_a_result(3, x_01, lambda_01, False)
# showing_a_result(1, x_02, lambda_01, False)
# showing_a_result(2, x_02, lambda_01, False)
# showing_a_result(3, x_02, lambda_01, False)


# making a comparaison between the 3 classes for x_01 lambda_0 that changes
def means_for_method(method, x_0, lambda_array):
    mean_time = 0
    mean_iter = 0
    mean_x = np.zeros(5)
    for lambda_0 in lambda_array:
        start_time = time.perf_counter()
        result_x, result_f_value, nb_iter = 0, 0, 0
        if method == 1:
            result_x, result_f_value, nb_iter = auto_sqp.solve(x_0, False)
        elif method == 2:
            result_x, result_f_value, nb_iter = hand_made_sqp.optimize(x_0, lambda_0, False)
        elif method == 3:
            result_x, result_f_value, nb_iter = hand_made_sqp_with_constraints_changes.optimize(x_0, lambda_0, False)
        end_time = time.perf_counter()
        elapsed_time = end_time - start_time  
        mean_time += elapsed_time
        mean_iter += nb_iter
        mean_x += result_x
    mean_time /= len(lambda_array)
    mean_iter /= len(lambda_array)
    mean_x /= len(lambda_array)
    print()
    if method == 1:
        print("Auto SQP")
    elif method == 2:
        print("Hand Made SQP")
    elif method == 3:
        print("Hand Made SQP with Constraints Changes")
    print(f"Mean time : {mean_time}")
    print("Mean x : ", mean_x)
    print(f"Mean iterations : {mean_iter}")
    
def make_comparaison(x_0):
    nb_max_in_each_direction = 1 # above that there is some exponential overflow issues
    nb_in_each_direction = 10
    nb_values = nb_in_each_direction * nb_in_each_direction * nb_in_each_direction
    lambda_array = [np.zeros(3) for i in range(nb_values)]
    for i in range(nb_in_each_direction):
        for j in range(nb_in_each_direction):
            for k in range(nb_in_each_direction):
                lambda_array[i * nb_in_each_direction * nb_in_each_direction + j * nb_in_each_direction + k] = np.array([i * nb_max_in_each_direction / nb_in_each_direction - nb_max_in_each_direction / 2, j * nb_max_in_each_direction / nb_in_each_direction - nb_max_in_each_direction / 2, k * nb_max_in_each_direction / nb_in_each_direction - nb_max_in_each_direction / 2])
    means_for_method(1, x_0, lambda_array)
    means_for_method(2, x_0, lambda_array)
    means_for_method(3, x_0, lambda_array)

# make_comparaison(x_01)