import matplotlib.pyplot as plt
import matplotlib
import numpy as np
import pylops
import cvxpy as cp
from scipy.sparse import csr_matrix
import os
import time

"""
matplotlib setup
"""
# matplotlib setup
import matplotlib
# adjust the font size accordingly
font = {'family' : 'sans',
        'size'   : 12}
matplotlib.rc('font', **font)

"""
Image loading functions
"""
def load_image_option_I(file_name = "dog_rgb.npy", show_image = False, exp_coef_z = 0.1, exp_coef_x = 0.3, sampling_size = 5):
    sampling = sampling_size
    im = np.load(file_name)[::sampling, ::sampling, 2]
    Nz, Nx = im.shape

    # Blurring Gaussian operator
    nh = [15, 25]
    hz = np.exp(-exp_coef_z * np.linspace(-(nh[0] // 2), nh[0] // 2, nh[0]) ** 2)
    hx = np.exp(-exp_coef_x * np.linspace(-(nh[1] // 2), nh[1] // 2, nh[1]) ** 2)
    hz /= np.trapezoid(hz)  # normalize the integral to 1
    hx /= np.trapezoid(hx)  # normalize the integral to 1
    h = hz[:, np.newaxis] * hx[np.newaxis, :]

    # make sure the directory exists
    os.makedirs("Results/Images", exist_ok=True)

    if show_image:
        fig, ax = plt.subplots(1, 1, figsize=(5, 3))
        him = ax.imshow(h)
        ax.set_title("Blurring operator")
        fig.colorbar(him, ax=ax)
        ax.axis("tight")
        plt.savefig("Results/Images/Blurring_operator_I.pdf")
        plt.show()
    Cop = pylops.signalprocessing.Convolve2D(
        (Nz, Nx), h=h, offset=(nh[0] // 2, nh[1] // 2), dtype="float32"
    )

    imblur = Cop * im
    if show_image:
        plt.imshow(im, cmap="viridis", vmin=0, vmax=255)
        plt.savefig("Results/Images/Original_image_I.pdf")
        plt.show()
        plt.imshow(imblur, cmap="viridis", vmin=0, vmax=255)
        plt.savefig("Results/Images/Blurred_image_I.pdf")
        plt.show()

    Wop = pylops.signalprocessing.DWT2D((Nz, Nx), wavelet="haar", level=3)

    # This is your A and b for your f1 cost!
    A = Cop * Wop.H
    b = imblur.ravel()

    return Wop, A, b, im, imblur

def load_image_option_II(file_name = "chateau.npy", show_image = False, exp_coef_z = 0.1, exp_coef_x = 0.3, sampling_size = 2):
    sampling = sampling_size
    im = np.load(file_name)[::sampling, ::sampling, 1]
    Nz, Nx = im.shape

    # Blurring Gaussian operator
    nh = [15, 25]
    hz = np.exp(-exp_coef_z * np.linspace(-(nh[0] // 2), nh[0] // 2, nh[0]) ** 2)
    hx = np.exp(-exp_coef_x * np.linspace(-(nh[1] // 2), nh[1] // 2, nh[1]) ** 2)
    hz /= np.trapezoid(hz)  # normalize the integral to 1
    hx /= np.trapezoid(hx)  # normalize the integral to 1
    h = hz[:, np.newaxis] * hx[np.newaxis, :]

    # make sure the directory exists
    os.makedirs("Results/Images", exist_ok=True)

    if show_image:
        fig, ax = plt.subplots(1, 1, figsize=(5, 3))
        him = ax.imshow(h)
        ax.set_title("Blurring operator")
        fig.colorbar(him, ax=ax)
        ax.axis("tight")
        plt.savefig("Results/Images/Blurring_operator_II.pdf")
        plt.show()
    Cop = pylops.signalprocessing.Convolve2D(
        (Nz, Nx), h=h, offset=(nh[0] // 2, nh[1] // 2), dtype="float32"
    )

    imblur = Cop * im
    if show_image:
        plt.imshow(im, cmap="gray", vmin=0, vmax=255)
        plt.savefig("Results/Images/Original_image_II.pdf")
        plt.show()
        plt.imshow(imblur, cmap="gray", vmin=0, vmax=255)
        plt.savefig("Results/Images/Blurred_image_II.pdf")
        plt.show()

    Wop = pylops.signalprocessing.DWT2D((Nz, Nx), wavelet="haar", level=3)

    # This is your A and b for your f1 cost!
    A = Cop * Wop.H
    b = imblur.ravel()

    return Wop, A, b, im, imblur



"""
Proximal function
"""
def soft_threshold(x, lambda_):
    """ Soft thresholding operator """
    return np.sign(x) * np.maximum(0, np.abs(x) - lambda_)

""" 
Code of the ISTA and FISTA algorithm
Return: optimal x, opt_gap_cost (history of cost-optcost)
"""
def my_fista(A, b, opt_cost, alpha_coef = 1, eps=1e-1, niter=100, tol=1e-10, acceleration=False):

    m, n = A.shape  # A is m x n
    x = np.zeros(n)  # initial solution
    y_prev = np.zeros(n)
    lambda_prev = 0

    L = A.eigs(neigs=1, symmetric=True)[0].real  # PyLops eigenvalue computation    
    alpha = alpha_coef / L 
    opt_gap_cost = []  # To store the optimization gap history

    for k in range(niter):
        gradient = A.H @ (A @ x - b)  # Gradient of the least squares term
        v_k = x - alpha * gradient

        if acceleration:  # FISTA
            lambda_new = (1 + np.sqrt(1 + 4 * lambda_prev**2)) / 2
            gamma_k = (lambda_prev - 1) / lambda_new
            y_new = soft_threshold(v_k, eps * alpha)
            x_new = y_new + gamma_k * (y_new - y_prev)
            lambda_prev = lambda_new
            y_prev = y_new
        else : # ISTA
            x_new = soft_threshold(v_k, eps * alpha)

        # update x
        x = x_new 

        # calculate the optimization gap (difference from optimal cost)
        cost = 0.5 * np.linalg.norm(A @ x - b) ** 2 + eps * np.linalg.norm(x, 1)
        opt_gap = np.abs(cost - opt_cost)
        opt_gap_cost.append(opt_gap)

        # check for convergence
        if opt_gap < tol:
            break

    return x, opt_gap_cost

"""
Function to compare the results of the ISTA and FISTA algorithms for given parameters
"""
def run_comparaison_program(A, b, Wop, eps_value=0.1, baseline_iter=1000, my_iter=100, plot = True, show_image = False, name="default_comparaison"):
    # baseline from pylops
    imdeblurfista0, n_eff_iter, cost_history = pylops.optimization.sparsity.fista(
        A, b, eps=eps_value, niter=baseline_iter
    )
    opt_cost = cost_history[-1]

    # ISTA
    my_imdeblurfista, opt_gap_cost = my_fista(
        A, b, opt_cost, alpha_coef=1, eps=eps_value, niter=my_iter, acceleration=False)

    # FISTA
    my_imdeblurfista1, opt_gap_cost1 = my_fista(
        A, b, opt_cost, alpha_coef=1, eps=eps_value, niter=my_iter, acceleration=True)
    
    # make sure the directory exists
    os.makedirs("Results/ISTA_FISTA_Results", exist_ok=True)

    if plot:
        plt.loglog(opt_gap_cost, 'C0', label='ISTA')
        plt.loglog(opt_gap_cost1, 'C1', label='FISTA')
        plt.grid()
        plt.loglog([3, 30], [1e6, 1e5], 'C0--', label='1/k')
        plt.loglog([3, 30], [.5e5, .5e3], 'C1--', label='1/k2')
        plt.xlabel('Iteration')
        plt.ylabel('Optimization gap')
        plt.legend()
        plt.savefig(f"Results/ISTA_FISTA_Results/{name}.pdf")
        if show_image:
            plt.show()
        plt.clf()

    imdeblurfista = my_imdeblurfista1.reshape(A.dims)
    imdeblurfista = Wop.H * imdeblurfista

    return imdeblurfista

"""
Function to visualise the results of the deblurring for the FISTA algorithm
"""
def visualise_results(im, imblur, imdeblurfista, show_image = False, name="default_visualisation_FISTA", is_image_I = True):

    color = "viridis" if is_image_I else "gray"
    # make sure the directory exists
    os.makedirs("Results/ISTA_FISTA_Results", exist_ok=True)

    fig = plt.figure(figsize=(12, 6))
    fig.suptitle("Deblurring", fontsize=14, fontweight="bold", y=0.95)
    ax1 = plt.subplot2grid((2, 5), (0, 0))
    ax2 = plt.subplot2grid((2, 5), (0, 1))
    ax3 = plt.subplot2grid((2, 5), (0, 2))

    ax1.imshow(im, cmap=color, vmin=0, vmax=250)
    ax1.axis("tight")
    ax1.set_title("Original")
    ax2.imshow(imblur, cmap=color, vmin=0, vmax=250)
    ax2.axis("tight")
    ax2.set_title("Blurred")

    ax3.imshow(imdeblurfista, cmap=color, vmin=0, vmax=250)
    ax3.axis("tight")
    ax3.set_title("FISTA deblurred")

    plt.tight_layout()
    plt.subplots_adjust(top=0.8)
    plt.savefig(f"Results/ISTA_FISTA_Results/{name}.pdf")

    if show_image:
        plt.show()

"""
Function to launch the first part of the project
"""
def test_result (Wop, A, b, im, imblur):
    imdeblurfista = run_comparaison_program(A,b, Wop)
    visualise_results(im, imblur, imdeblurfista)

# start = time.time()
## Load the image according to your option
# Wop, A, b, im, imblur = load_image_option_I()
# Wop, A, b, im, imblur = load_image_option_II(show_image=True)
# test_result(Wop, A, b, im, imblur)
# end = time.time()
# print(f"Time to run the program: {end-start}")
# 6.8s for image I

""""
Function to launch the evaluation of the different epsilons values
"""
def test_different_epsilon(Wop, A, b, im, imblur, baseline_iter=1000, my_iter=100, show_image = False, name="default_comparaison_epsilon"):
    # make sure the directory exists
    os.makedirs("Results/ISTA_FISTA_Results", exist_ok=True)
    plt.grid()

    eps_values = [0.001, 0.01, 0.1, 1, 10]
    colors = plt.cm.viridis(np.linspace(0, 1, len(eps_values)))  # generate distinct colors

    for eps_value, color in zip(eps_values, colors):
        label = rf"$\epsilon = {eps_value}$"
    
        # baseline from pylops
        imdeblurfista0, n_eff_iter, cost_history = pylops.optimization.sparsity.fista(
            A, b, eps=eps_value, niter=baseline_iter
        )
        opt_cost = cost_history[-1]

        # FISTA
        my_imdeblurfista1, opt_gap_cost1 = my_fista(
            A, b, opt_cost, alpha_coef=1, eps=eps_value, niter=my_iter, acceleration=True)
        
        plt.loglog(opt_gap_cost1, color=color, label=label)

    # reference convergence rates
    plt.loglog([3, 30], [1e6, 1e5], 'r--')
    plt.loglog([3, 30], [0.5e5, 0.5e3], 'r--')
    
    # label and legend
    plt.xlabel('Iteration')
    plt.ylabel('Optimization gap')
    plt.title(rf"Convergence of FISTA algorithm for different $\epsilon$ values")
    plt.legend()
    plt.savefig(f"Results/ISTA_FISTA_Results/{name}.pdf")    
    if show_image:
        plt.show()
# test_different_epsilon(Wop, A, b, im, imblur)

""""
Function to launch the evaluation of the different step size values
"""
def test_different_step_size(Wop, A, b, im, imblur, baseline_iter=1000, my_iter=100, show_image = False, name="default_comparaison_alpha"):
    # make sure the directory exists
    os.makedirs("Results/ISTA_FISTA_Results", exist_ok=True)
    plt.grid()

    alpha_values = [0.001, 0.01, 0.1, 1]
    colors = plt.cm.viridis(np.linspace(0, 1, len(alpha_values)))  # generate distinct colors

    for alpha_value, color in zip(alpha_values, colors):
        label = rf"$\alpha = \frac{{{alpha_value}}}{{L}}$"
    
        # baseline from pylops
        imdeblurfista0, n_eff_iter, cost_history = pylops.optimization.sparsity.fista(
            A, b, eps=0.1, niter=baseline_iter
        )
        opt_cost = cost_history[-1]

        # FISTA
        my_imdeblurfista1, opt_gap_cost1 = my_fista(
            A, b, opt_cost, alpha_coef=alpha_value, eps=0.1, niter=my_iter, acceleration=True)
        
        plt.loglog(opt_gap_cost1, color=color, label=label)

    # reference convergence rates
    plt.loglog([3, 30], [1e6, 1e5], 'r--')
    plt.loglog([3, 30], [0.5e5, 0.5e3], 'r--')
    
    # label and legend
    plt.xlabel('Iteration')
    plt.ylabel('Optimization gap')
    plt.title(rf"Convergence of FISTA algorithm for different $\alpha$ values")
    plt.legend()
    plt.savefig(f"Results/ISTA_FISTA_Results/{name}.pdf")    
    if show_image:
        plt.show()
# test_different_step_size(Wop, A, b, im, imblur)


"""
Function to test different blurring 
"""
def test_different_blurring(image_option = 1):
    if image_option == 1:
        Wop, A, b, im, imblur_0_1 = load_image_option_I(exp_coef_z=0.01, exp_coef_x=0.03)
        imdeblurfista_0_1 = run_comparaison_program(A,b, Wop, name = "convergence_0_1_I")
        Wop, A, b, im, imblur_1 = load_image_option_I(exp_coef_z=0.1, exp_coef_x=0.3)
        imdeblurfista_1 = run_comparaison_program(A,b, Wop, name = "convergence_1_I")
        Wop, A, b, im, imblur_10 = load_image_option_I(exp_coef_z=1, exp_coef_x=3)
        imdeblurfista_10 = run_comparaison_program(A,b, Wop, name = "convergence_10_I")
        visualise_results(imblur_0_1, imblur_1, imblur_10, is_image_I=True, name="base_image_I_setup")
        visualise_results(imdeblurfista_0_1, imdeblurfista_1, imdeblurfista_10, is_image_I=True, name="deblurring_different_blurring_I")
    else:
        Wop, A, b, im, imblur_0_1 = load_image_option_II(exp_coef_z=0.01, exp_coef_x=0.03)
        imdeblurfista_0_1 = run_comparaison_program(A,b, Wop, name = "convergence_0_1_II")
        Wop, A, b, im, imblur_1 = load_image_option_II(exp_coef_z=0.1, exp_coef_x=0.3)
        imdeblurfista_1 = run_comparaison_program(A,b, Wop, name = "convergence_1_II")
        Wop, A, b, im, imblur_10 = load_image_option_II(exp_coef_z=1, exp_coef_x=3)
        imdeblurfista_10 = run_comparaison_program(A,b, Wop, name = "convergence_10_II")
        visualise_results(imblur_0_1, imblur_1, imblur_10, is_image_I=False, name="base_image_II_setup")
        visualise_results(imdeblurfista_0_1, imdeblurfista_1, imdeblurfista_10, is_image_I=False, name="deblurring_different_blurring_II")
# test_different_blurring()


"""
Function to diminish the sample size
"""
def test_diminishing_sample_size(image_option = 1):
    if image_option == 1:
        Wob, A, b, im, imblur = load_image_option_I(sampling_size=3)
        imdeblurfista = run_comparaison_program(A,b, Wob, plot=False)
        visualise_results(im, imblur, imdeblurfista, name="diminishing_sample_size_I")
    else:
        Wob, A, b, im, imblur = load_image_option_II(sampling_size=3)
        imdeblurfista = run_comparaison_program(A,b, Wob, plot=False)
        visualise_results(im, imblur, imdeblurfista, name="diminishing_sample_size_II")
# test_diminishing_sample_size()


"""
Function to test the cvxpy implementation
"""
def test_cvxpy(image_option = 1, sampling = 50, show = False):
    if image_option == 1:
        Wop, A, b, im, imblur = load_image_option_I(sampling_size=sampling)
        A_sparse = csr_matrix(A.todense())
        b_sparse = b
        x = cp.Variable(A_sparse.shape[1])
        objective = cp.Minimize(0.5*(cp.norm(A_sparse*x-b_sparse, 2))**2 +0.1*cp.norm(x,1))
        prob = cp.Problem(objective)
        result = prob.solve()
        x1 = x.value.reshape(A.dims)
        x1 = Wop.H * x1

        name_fig = f"cvxpy_I_{sampling}"
        visualise_results(im,imblur,x1, name=name_fig, show_image=show)
    else:
        Wop, A, b, im, imblur = load_image_option_II(sampling_size=sampling)
        A_sparse = csr_matrix(A.todense())
        b_sparse = b
        x = cp.Variable(A_sparse.shape[1])
        objective = cp.Minimize(0.5*(cp.norm(A_sparse*x-b_sparse, 2))**2 +0.1*cp.norm(x,1))
        prob = cp.Problem(objective)
        result = prob.solve()
        x1 = x.value.reshape(A.dims)
        x1 = Wop.H * x1

        name_fig = f"cvxpy_II_{sampling}"
        visualise_results(im,imblur,x1, name=name_fig, show_image=show)
# mesuring the time it takes to solve the problem
# sampling_test = 25
# start = time.time()
# test_cvxpy(sampling=sampling_test)
# end = time.time()
# print(f"Time to solve the problem with cvxpy for sampling size {sampling_test}: {end-start}")
# 0.77s for sampling size 50
# 22s for sampling size 25

