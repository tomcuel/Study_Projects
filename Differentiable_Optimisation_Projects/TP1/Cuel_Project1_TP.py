import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import minimize
import cvxpy as cp
import os



##================================================================================================
#### Elements to compute the Newton's method
##================================================================================================
'''
## Objective function
arguments:
    z = [x1,...,xN,y1,...,yN] is the vector of the variables
'''
def cost(z):
    N = int(len(z)/2)
    e = np.zeros(2*N)
    e[N:2*N] = np.ones(N)
    # e = [0,0,...,0,1,1,...,1], z = [x1,...,xN,y1,...,yN]
    # the cost is th sum of the y coordinates
    return np.dot(e, z)


'''
## Evaluate the constraint function and make a vector out of every constraint
arguments:
    z = [x1,...,xN,y1,...,yN] is the vector of the variables
    L is the length of each of the bars (supposed to be the same)
    (xN+1,yN+1)=(a,b) are the coordinates of the end points ((x0,y0)=(0,0) is the starting point)
'''
def constraint_value(z, L, a, b):
    N = int(len(z)/2)
    
    c = np.zeros(N+1)
    c[0] = (z[0]-0.)**2 + (z[N]-0.)**2 - L**2 # first bar
    for i in range(1,N):
        c[i] = (z[i]-z[i-1])**2 + (z[N+i]-z[N+i-1])**2 - L**2
    c[N] = (a-z[N-1])**2 + (b-z[2*N-1])**2 - L**2 # last bar
    
    return c


'''
## Compute the jacobian matric of the constraint
arguments:
    z = [x1,...,xN,y1,...,yN] is the vector of the variables
    L is the length of each of the bars (supposed to be the same)
    (a,b) are the coordinates of the end points ((0,0) is the starting point)
'''
def nabla_res(z, L, a, b):
    N = int(len(z)/2)
    C = np.zeros([2*N, N+1])
    
    for i in range(1,N):
        C[i,i] = 2*(z[i]-z[i-1])
        C[i+N,i] = 2*(z[i+N]-z[i-1+N])
        if i < N-1:
            C[i,i+1] = -2*(z[i+1]-z[i])
            C[i+N,i+1] = -2*(z[i+1+N]-z[i+N])

    C[0,0] = 2*(z[0]-0.)
    C[N,0] = 2*(z[N]-0.)
    C[0, 1] = 2*(z[0]-z[1])
    C[N, 1] = 2*(z[N]-z[N+1])
    C[N-1,N] = -2*(a-z[N-1])
    C[2*N-1,N] = -2*(b-z[2*N-1])

    return np.asmatrix(C)


'''
## Verify the gradient computation
arguments:
    z = [x1,...,xN,y1,...,yN] is the vector of the variables
    L is the length of each of the bars (supposed to be the same)
    (a,b) are the coordinates of the end points ((0,0) is the starting point)
'''
def check_der(z, L, a, b):
    N = int(len(z) / 2)
    dz = 0.01*np.random.random(2*N)
    C = nabla_res(z, L, a, b)
    der = (constraint_value(z+dz, L, a, b) - constraint_value(z, L, a, b)) - np.dot(nabla_res(z, L, a, b).transpose(), dz)
    print('NORM ERROR: ', np.linalg.norm(der)/np.linalg.norm(dz))
    return


'''
## Compute the Hessian of the Lagrangian
--> computes the upper left block of the Newton's method Hessian (derivative on the z variables)
arguments:
    z = [x1,...,xN,y1,...,yN] is the vector of the variables
    lbd = [lbd1,...,lbdN+1] is the vector of the multipliers
'''
def nabla_F(z, lbd):
    
    N = int(len(z) / 2)
    nF = np.zeros([2*N, 2*N])
    for i in range(N):
        if i>0:
            nF[i,i-1] = -2*lbd[i]
            nF[N+i, N+i-1] = -2*lbd[i]

        nF[i,i] = 2*(lbd[i]+lbd[i+1])
        nF[N+i,N+i] = 2*(lbd[i] + lbd[i+1])

        if i<N-1:
            nF[i,i+1] = -2*lbd[i+1]
            nF[N+i,N+i+1] = -2*lbd[i+1]

    return nF


'''
## Compute the elements of the Newton's method system for a given state
arguments:
    z = [x1,...,xN,y1,...,yN] is the vector of the variables
    lbd = [lbd1,...,lbdN+1] is the vector of the multipliers
    L is the length of each of the bars (supposed to be the same)
    (a,b) are the coordinates of the end points ((0,0) is the starting point)
'''
'''
KKT system 
e + nabla_z c(z) lbd = 0
c(z) = 0
becomes : 
nabla_F(z) dz + nabla_res(z) dlbd = -e - nabla_res(z) lbd
nabla_res(z) dz = 0
that can be written in matrix form as :
[A11 A12] [dz] = -rhs1
[A21 A22] [dlbd] = -rhs2
'''
def newton_iteration_elements(z, lbd, L, a, b):
    N = int(len(z)/2)

    A11 = nabla_F(z, lbd)
    A12 = nabla_res(z, L, a, b)
    A21 = A12.transpose()
    A22 = np.zeros([N + 1, N + 1])
    A1r = np.concatenate((A11, A12), axis=1)
    A2r = np.concatenate((A21, A22), axis=1)
    A = np.concatenate((A1r, A2r), axis=0)
    
    e = np.zeros(2 * N)
    e[N:2 * N] = np.ones(N)
    rhs1 = e + np.dot(A12, lbd) # e+nabla_res(z)*lbd
    rhs2 = constraint_value(z, L, a, b) # c(z)
    rhs = np.zeros([3 * N + 1])
    rhs[:2 * N] = rhs1
    rhs[2 * N:] = rhs2

    return A, rhs


'''
## Perform a Newton's step
arguments:
    z = [x1,...,xN,y1,...,yN] is the vector of the variables
    lbd = [lbd1,...,lbdN+1] is the vector of the multipliers
    L is the length of each of the bars (supposed to be the same)
    (a,b) are the coordinates of the end points ((0,0) is the starting point)
    backtracking is a int to activate the backtracking line search (option1 = 1, option2 = 2)
    tau is the reduction factor in the backtracking (tau in (0,1))
    beta is the sufficient decrease factor in the backtracking (beta in (0,1/2))
'''
def newton_iteration(z, lbd, L, a, b, backtracking=0, tau=0.5, beta=0.25, epsilon=1e-3):
    N = int(len(z)/2)
    # build system
    A, rhs = newton_iteration_elements(z, lbd, L, a, b)

    # solve for d using Newton's step
    d = np.linalg.solve(A, -rhs)
    dz = d[:2*N]  
    dlbd = d[2*N:]
   
    # initialize step size parameters
    alpha = 1.0  # start with a full step (alpha_k = 1)
    # reduction factor (tau in (0,1))
    # sufficient decrease factor (beta in (0,1/2))
    
    # backtracking 
    # damped Newton's method (for fun)
    if backtracking == 1:
        # compute residual at current point
        norm_r_k = np.linalg.norm(rhs)
        
        # backtracking loop condition
        while np.linalg.norm(newton_iteration_elements(z + alpha * dz, lbd + alpha * dlbd, L, a, b)[1]) > (1-beta*alpha)*norm_r_k:
            alpha = tau * alpha  # reduce alpha

    # uniform gridding 
    elif backtracking == 2:
        grid_size = int(np.floor((L/epsilon)))
        alpha_values = np.linspace(0, 1.0, grid_size)  # uniform grid from 0 to 1.0 (we just skip alpha=0)
        best_alpha = 1.0
        min_residual = np.inf

        for alpha_candidate in alpha_values:
            if alpha_candidate == 0:
                continue
            new_rhs = newton_iteration_elements(z + alpha_candidate*dz, lbd + alpha_candidate*dlbd, L, a, b)[1]
            residual = np.linalg.norm(new_rhs)

            if residual < min_residual:
                min_residual = residual
                best_alpha = alpha_candidate

        alpha = best_alpha  # choose the best step size

    # update z and lbd following the Newton's step method
    z = z + alpha * dz
    lbd = lbd + alpha * dlbd
    # compute the optimality gap
    gap = np.linalg.norm(rhs)

    return z, lbd, gap


'''
## Solving the chain with your Newton method
arguments:
    z0 = [x1,...,xN,y1,...,yN] is the vector of the variables we're starting from
    lbd0 = [lbd1,...,lbdN+1] is the vector of the multipliers we're starting from
    L is the length of each of the bars (supposed to be the same)
    (a,b) are the coordinates of the end points ((0,0) is the starting point)
    Nmax is the maximum number of iterations
    tol is the tolerance for the stopping criterion
    backtracking is a int to activate the backtracking line search (option1 = 1, option2 = 2)
    tau is the reduction factor in the backtracking (tau in (0,1))
    beta is the sufficient decrease factor in the backtracking (beta in (0,1/2))
    epsilon is the step size for the uniform griding backtracking
'''
def solve_chain(z0, lbd0, L, a, b, Nmax=100, tol=1e-6, backtracking=0, tau=0.5, beta=0.25, epsilon=1e-3):

    err = 1
    z= z0
    lbd = lbd0
    g = list()
    k = 0
    while (k < Nmax) and (err > tol): # Stopping criterion
        k += 1
        # newton iteration
        z, lbd, gap = newton_iteration(z, lbd, L, a, b, backtracking=backtracking, tau=tau, beta=beta, epsilon=epsilon)
        g.append(gap)
        err = gap

    return z, lbd, g


'''
## Check the stationarity of the solution
arguments:
    z = [x1,...,xN,y1,...,yN] is the vector of the variables
    lbd = [lbd1,...,lbdN+1] is the vector of the multipliers
    gap is a list of optimality gaps for each iteration
'''
def check_stationarity(z, lbd, gap):
    if gap[-1] < 1e-3: # solution likely to be optimal
        F = nabla_F(z, lbd)
        e, _ = np.linalg.eigh(F)
        print('Eigenvalues : ', np.min(e), np.max(e))
        if np.min(e) > 0: # all eigenvalues are positive, hessian is positive definite, so we have a local minimum
            print('A local optimizer found')
    return



##================================================================================================
### Plotting routines
##================================================================================================
'''
## Plot the chain
arguments:
    z = [x1,...,xN,y1,...,yN] is the vector of the variables
    (a,b) are the coordinates of the end points ((0,0) is the starting point)
    legend is a list of strings for the legend
    save_fig is a boolean to save the figure
    filename is the name of the file to save the figure
'''
def plot_chain(z, a, b, legend = [], save_fig = False, filename = 'Output-chain.pdf'):
    N = int(len(z)/2)
    xc = np.zeros(N+2)
    yc = np.zeros(N+2)
    xc[1:N+1] = z[0:N]
    xc[N+1] = a
    yc[1:N+1] = z[N:2*N]
    yc[N+1] = b

    plt.figure()
    plt.plot(xc,yc, 'ko-')
    plt.grid()
    plt.xlabel('x')
    plt.ylabel('y')
    plt.legend(legend)
    if save_fig:
        plt.savefig(filename)
    else:
        plt.show()

    return


'''
## Plot two chains on the same graph
arguments:
    z1 = [x1,...,xN,y1,...,yN] is the vector of the variables for the first chain
    z2 = [x1,...,xN,y1,...,yN] is the vector of the variables for the second chain
    a,b are the coordinates of the end points ((0,0) is the starting point)
    legend is a list of strings for the legend
    save_fig is a boolean to save the figure
    filename is the name of the file to save the figure
'''
def plot_n_chains(z_n, a, b, legend=[], save_fig=False, filename='Output-two_chains.pdf'):
    plt.figure()

    k = 0
    for z in z_n:
        N = len(z) // 2
        xc = np.zeros(N+2)
        yc = np.zeros(N+2)
        xc[1:N+1] = z[:N]
        xc[N+1] = a
        yc[1:N+1] = z[N:2*N]
        yc[N+1] = b

        plt.plot(xc, yc, 'o-', label=legend[k])
        k += 1
    
    plt.grid()
    plt.xlabel('x')
    plt.ylabel('y')
    plt.legend()
    
    # save or show the figure
    if save_fig:
        plt.savefig(filename)
    else:
        plt.show()


'''
## Plot the convergence of the algorithm
arguments:
    opt_gap is a list of optimality gaps for each iteration
    legend is a list of strings for the legend
    save_fig is a boolean to save the figure
    filename is the name of the file to save the figure
'''
def plot_convergence(opt_gap, legend = [], save_fig = False, filename = 'Output-convergence.pdf'):
    plt.figure()
    plt.loglog(opt_gap, 'o-') # useful since Newton's method is quadratically convergent, the error should decrease exponentially
    plt.grid()
    plt.xlabel('Iteration count')
    plt.ylabel('Optimality gap (norm residual)')
    plt.legend(legend)
    if save_fig:
        plt.savefig(filename)
    else:
        plt.show()



##================================================================================================
### Testing the code
##================================================================================================
'''
making a first test on the chain problem
'''
""" 
N = 5
L = 1.0/(N-1)
a,b = 1.,-.1
z = np.zeros(2*N)
z[0:N] = np.linspace(1./(N+1), a-1./(N+1), N)
z[N:2*N] =[b*i -.1*(i-a/2.)**2 for i in z[0:N]]
lmbda = 0.1*np.random.random(N+1)
z_sol, lmbda_sol, opt_gap = solve_chain(z, lmbda, L, a, b, Nmax = 100, tol = 1e-6, backtracking = 0)
check_stationarity(z_sol, lmbda_sol, opt_gap)
plot_convergence(opt_gap, legend=["Without Backtracking"], save_fig=True, filename="Results/First_Results/Output-convergence_back_track_0_other.pdf")
plot_chain(z_sol, a, b, legend=["Without Backtracking"], save_fig=True, filename="Results/First_Results/Output-chain_back_track_0_other.pdf")
"""


'''
function to test the code on the first example provided 
arguments:
    save_figures is a boolean to save the figures
    lambda_coef is the coefficient multiplying the random generation of the lambda values
'''
def test_chain(save_figures = False, lambda_coef = 0.1):
    N = 5
    L = 1.0/(N-1)
    a,b = 1.,-.1
    z = np.zeros(2*N)
    z[0:N] = np.linspace(1./(N+1), a-1./(N+1), N)
    z[N:2*N] =[b*i-.1*(i-a/2.)**2 for i in z[0:N]]
    lmbda = lambda_coef*np.random.random(N+1)

    # make sure the directory exists
    os.makedirs("Results/First_Results", exist_ok=True)

    backtrackings = [0, 1, 2]
    for back_track in backtrackings:
        z_sol, lmbda_sol, opt_gap = solve_chain(z, lmbda, L, a, b, Nmax = 100, tol = 1e-6, backtracking = back_track)
        print(f"Checking stationarity for backtracking option : {back_track}")
        check_stationarity(z_sol, lmbda_sol, opt_gap)
        
        legended = [f"no Backtracking : {back_track}"]
        filename_chain = f"Results/First_Results/Output-chain_back_track_{back_track}.pdf"
        filename_convergence = f"Results/First_Results/Output-convergence_back_track_{back_track}.pdf"
        plot_convergence(opt_gap, legend=legended, save_fig=save_figures, filename=filename_convergence)
        plot_chain(z_sol, a, b, legend=legended, save_fig=save_figures, filename=filename_chain)

    return

# something to test the code, but it's strange, even without backtracking, it seems to work sometimes (randomness make things work I guess)
# test_chain(save_figures=True, lambda_coef=0.1)


'''
function to test the code for different values of lambda
--> does return an average chain graph for each backtracking method
arguments:
    number_tests is the number of tests to perform
    lambda_ponderation_coefs is the list of coefficients to multiply the random generation of the lambda values
'''
def different_lambda_chain(lambda_ponderation_coefs):
    N = 5
    L = 1.0/(N-1)
    a,b = 1.,-.1
    z = np.zeros(2*N)
    z[0:N] = np.linspace(1./(N+1), a-1./(N+1), N)
    z[N:2*N] =[b*i-.1*(i-a/2.)**2 for i in z[0:N]]
    
    # make sure the directory exists
    os.makedirs("Results/Lambda_Variation_Results", exist_ok=True)

    average_z_0 = np.zeros(2*N)
    average_z_1 = np.zeros(2*N)
    average_z_2 = np.zeros(2*N)

    for lambda_coef in lambda_ponderation_coefs:
        lmbda = lambda_coef*np.ones(N+1)
        z_sol_0, _, _ = solve_chain(z, lmbda, L, a, b, Nmax = 100, tol = 1e-6, backtracking = 0)
        z_sol_1, _, _ = solve_chain(z, lmbda, L, a, b, Nmax = 100, tol = 1e-6, backtracking = 1)
        z_sol_2, _, _ = solve_chain(z, lmbda, L, a, b, Nmax = 100, tol = 1e-6, backtracking = 2)

        average_z_0 += z_sol_0
        average_z_1 += z_sol_1
        average_z_2 += z_sol_2

    average_z_0 /= len(lambda_coefs)
    average_z_1 /= len(lambda_coefs)
    average_z_2 /= len(lambda_coefs)

    plot_chain(average_z_0, a, b, legend=["Without Backtracking"], save_fig=True, filename="Results/Lambda_Variation_Results/Output-chain_back_track_0.pdf")
    plot_chain(average_z_1, a, b, legend=["Backtracking option 1"], save_fig=True, filename="Results/Lambda_Variation_Results/Output-chain_back_track_1.pdf")
    plot_chain(average_z_2, a, b, legend=["Backtracking option 2"], save_fig=True, filename="Results/Lambda_Variation_Results/Output-chain_back_track_2.pdf")

# testing the code for different lambda values, and for the same other parameters as before 
lambda_coefs = [0.001, 0.01, 0.1, 0.25, 0.5, 1, 2, 5, 10]
# different_lambda_chain(lambda_coefs)


'''
function to test for different values of lambda and that create the convergence superposition graph
arguments:
    lambda_ponderation_coefs is the list of coefficients to multiply the random generation of the lambda values
'''
def different_lambda_convergence(lambda_ponderation_coefs):
    N = 5
    L = 1.0/(N-1)
    a,b = 1.,-.1
    z = np.zeros(2*N)
    z[0:N] = np.linspace(1./(N+1), a-1./(N+1), N)
    z[N:2*N] =[b*i-.1*(i-a/2.)**2 for i in z[0:N]]
    
    # make sure the directory exists
    os.makedirs("Results/Lambda_Variation_Results", exist_ok=True)

    gaps = []
    labels = []
    for lambda_coef in lambda_ponderation_coefs:
        _, _, opt_gap = solve_chain(z, lambda_coef*np.ones(N+1), L, a, b, Nmax=100, tol=1e-6, backtracking=0)
        gaps.append(opt_gap)
        labels.append(f"lambda = {lambda_coef:.3f}")

    plt.figure()
    for gap in gaps :
        plt.loglog(gap, 'o-')
    plt.legend(labels)
    plt.grid()
    plt.xlabel('Iteration count')
    plt.ylabel('Optimality gap (norm residual)')
    plt.savefig("Results/Lambda_Variation_Results/Output-convergence_superposition.pdf")

# testing the code for different lambda values, and for the same other parameters as before
lambda_coefs = [0.001, 0.01, 0.1, 0.5, 1, 10]
# different_lambda_convergence(lambda_coefs)


'''
function to test the code for different values of L, N, or initial z
arguments:
    is_testing_z is a boolean to test the code an other initial guess for z
    is_testing_N is a boolean to test the code for different values of N
    is_testing_L is a boolean to test the code for different values of L
'''
def different_parameters(is_testing_z=False, is_testing_N=False, is_testing_L=False):
    if is_testing_z: # normally it exit by telling that the matrix is not invertible / singular
        N = 5
        L = 1.0/(N-1)
        a,b = 1.,-.1
        z = np.zeros(2*N)
        lmbda = 0.01*np.random.random(N+1)
        z_sol, lmbda_sol, opt_gap = solve_chain(z, lmbda, L, a, b, Nmax = 100, tol = 1e-6, backtracking = True)
        check_stationarity(z_sol, lmbda_sol, opt_gap)

    elif is_testing_N : 
        Ns = [5, 10, 20, 50]
        L = 0.25
        labels = [f"N = {N}" for N in Ns]
        z_sols_0 = []
        gaps_0 = []
        z_sols_1 = []
        gaps_1 = []
        z_sols_2 = []
        gaps_2 = []
        for N in Ns:
            a,b = 1.,-.1
            z = np.zeros(2*N)
            z[0:N] = np.linspace(1./(N+1), a-1./(N+1), N)
            z[N:2*N] =[b*i-.1*(i-a/2.)**2 for i in z[0:N]]
            lmbda = 0.01*np.random.random(N+1)
            z_sol_0, _, opt_gap_0 = solve_chain(z, lmbda, L, a, b, Nmax = 100, tol = 1e-6, backtracking = 0)
            z_sol_1, _, opt_gap_1 = solve_chain(z, lmbda, L, a, b, Nmax = 100, tol = 1e-6, backtracking = 1)
            z_sol_2, _, opt_gap_2 = solve_chain(z, lmbda, L, a, b, Nmax = 100, tol = 1e-6, backtracking = 2)
            z_sols_0.append(z_sol_0)
            gaps_0.append(opt_gap_0)
            z_sols_1.append(z_sol_1)
            gaps_1.append(opt_gap_1)
            z_sols_2.append(z_sol_2)
            gaps_2.append(opt_gap_2)
        
        # make sure the directory exists
        os.makedirs("Results/Parameters_Variation_Results", exist_ok=True)
        
        # only plotting the effects of the N parameter on the backtracking_2 method (chain and convergence)
        # chain (plot the first and third one on the same graph only) 
        plot_n_chains(z_sols_2, a, b, legend=labels, save_fig=True, filename="Results/Parameters_Variation_Results/Output-chain_N_effect.pdf")

        # convergence
        plt.figure()
        for gap in gaps_2 :
            plt.loglog(gap, 'o-')
        plt.legend(labels)
        plt.grid()
        plt.xlabel('Iteration count')
        plt.ylabel('Optimality gap (norm residual)')
        plt.savefig("Results/Parameters_Variation_Results/Output-convergence_N_effect.pdf")

    elif is_testing_L:
        N = 5
        Ls = [1.0/(n-1) for n in [5, 10, 20, 50]]
        labels = [f"L = {L}" for L in Ls]
        a,b = 1.,-.1
        z = np.zeros(2*N)
        z[0:N] = np.linspace(1./(N+1), a-1./(N+1), N)
        z[N:2*N] =[b*i-.1*(i-a/2.)**2 for i in z[0:N]]
        lmbda = 0.01*np.random.random(N+1)
        z_sols_0 = []
        gaps_0 = []
        z_sols_1 = []
        gaps_1 = []
        z_sols_2 = []
        gaps_2 = []
        for L in Ls:
            z_sol_0, _, opt_gap_0 = solve_chain(z, lmbda, L, a, b, Nmax = 100, tol = 1e-6, backtracking = 0)
            z_sol_1, _, opt_gap_1 = solve_chain(z, lmbda, L, a, b, Nmax = 100, tol = 1e-6, backtracking = 1)
            z_sol_2, _, opt_gap_2 = solve_chain(z, lmbda, L, a, b, Nmax = 100, tol = 1e-6, backtracking = 2)
            z_sols_0.append(z_sol_0)
            gaps_0.append(opt_gap_0)
            z_sols_1.append(z_sol_1)
            gaps_1.append(opt_gap_1)
            z_sols_2.append(z_sol_2)
            gaps_2.append(opt_gap_2)

        # make sure the directory exists
        os.makedirs("Results/Parameters_Variation_Results", exist_ok=True)

        # only plotting the effects of the L parameter on the backtracking_2 method (chain and convergence)
        # chain (plot the first and third one on the same graph only)
        plot_n_chains(z_sols_2, a, b, legend=labels, save_fig=True, filename="Results/Parameters_Variation_Results/Output-chain_L_effect.pdf")

        # convergence
        plt.figure()
        for gap in gaps_2 :
            plt.loglog(gap, 'o-')
        plt.legend(labels)
        plt.grid()
        plt.xlabel('Iteration count')
        plt.ylabel('Optimality gap (norm residual)')
        plt.savefig("Results/Parameters_Variation_Results/Output-convergence_L_effect.pdf")

# testing the code for different N, L, z0 parameters
# we test z=0, and see that the things is crashing because of singular matrix inversion 
# we need to find a feasible solution first for z0, so it works
# different_parameters(is_testing_z=True) #--> singular matrix problem
# we then test for different values of N and L
# different_parameters(is_testing_z=False, is_testing_N=True, is_testing_L=False)
# different_parameters(is_testing_z=False, is_testing_N=False, is_testing_L=True)



##================================================================================================
## Second method using scipy.optimize
##================================================================================================
'''
## function to test the code using the scipy.optimize library
there also now is a new inequality constraint that we need to add to the problem and to consider
arguments:
    N is the number of bars
    L is the length of each of the bars (supposed to be the same)
    a,b are the coordinates of the end points ((0,0) is the starting point)
    with_inequality is a boolean to activate the inequality constraints
'''
def solve_optimization_using_scipy(N, L, a, b, with_inequality=False):
    
    # inequality constraint function
    def inequality_constraints(z):
        x,y = z[:N],z[N:]
        return [0.2*x[i]+y[i]+0.1 for i in range(N)]  # g_i(z) >= 0

    # define constraints
    cons = [{'type': 'eq', 'fun': lambda z: constraint_value(z, L, a, b)}]
    if with_inequality:
        cons.extend([{'type': 'ineq', 'fun': lambda z: inequality_constraints(z)}])

    # initial guess
    z0 = np.random.rand(2*N)  

    # solve using SLSQP
    result = minimize(cost, z0, method='SLSQP', constraints=cons, options={'disp': True})

    return result


'''
## function to make all the graphs linked to the scipy optimization
--> it also print the scipy minimize parameters results
'''
def make_all_scipy_graph():
    os.makedirs("Results/Scipy_Optimization", exist_ok=True)

    def plot_solution(N, z, a, b, title, filename, is_with_inequality_constraints=False):
        """Plot the optimized chain positions."""
        x = [0]+list(z[0:N])+[a]
        y = [0]+list(z[N:2*N])+[b]
        
        plt.figure(figsize=(6, 4))
        plt.plot(x, y, 'o-', label="Optimized Chain")
        plt.scatter([0, a], [0, b], color='red', label="Endpoints", s=100)

        # plot the constraint values and violations (if any)
        if is_with_inequality_constraints:
            # compute constraint values at the optimal solution
            g_values = 0.2*z[:N] + z[N:2*N] + 0.1  # g_i = 0.2xi + yi + 0.1
            # find violations (values that are negative)
            violations = g_values[g_values < 0]
            # print violation details
            if len(violations) > 0:
                print(f"Constraint violations detected: {violations}")
            else:
                print("No constraint violations. Solution satisfies all constraints.")
            # plot constraint values g_i
            plt.scatter(z[:N], g_values, color='green', label="Constraint g_i(z)", s=50)
            # highlight violations (if any)
            if len(violations) > 0:
                plt.scatter(z[:N][g_values < 0], violations, color='black', label="Violations", s=100)

        plt.xlabel("x")
        plt.ylabel("y")
        plt.title(title)
        plt.legend()
        plt.grid()
        plt.savefig(f"Results/Scipy_Optimization/{filename}.pdf")

    # set parameters for the first test
    N = 5
    L = 1.0
    a, b = 1.,-.1 

    # solve without inequality constraints
    print("Solving optimization without inequality constraints...")
    res_no_constraints = solve_optimization_using_scipy(N, L, a, b, with_inequality=False)
    plot_solution(N, res_no_constraints.x, a, b, "Without Inequality Constraints", "no_constraints", is_with_inequality_constraints=False)
    print("Solution without inequality constraints:", res_no_constraints.x)
    print()

    # solve with inequality constraints
    print("Solving optimization with inequality constraints...")
    res_with_constraints = solve_optimization_using_scipy(N, L, a, b, with_inequality=True)
    plot_solution(N, res_with_constraints.x, a, b, "With Inequality Constraints", "with_constraints", is_with_inequality_constraints=True)
    print("Solution with inequality constraints:", res_with_constraints.x)
    print()

    # set parameters for the second test
    N = 20 
    L = 1.0/(N-1)

    # solve for N=20 without inequality constraints
    print("Solving optimization for N=20 without inequality constraints...")
    res_large_N_no_constraints = solve_optimization_using_scipy(N, L, a, b, with_inequality=False)
    plot_solution(N, res_large_N_no_constraints.x, a, b, "N=20 Without Inequality Constraints", "N20_no_constraints", is_with_inequality_constraints=False)
    print("Solution for N=20:", res_large_N_no_constraints.x)
    print()

    # solve for N=20 with inequality constraints
    print("Solving optimization for N=20 with inequality constraints...")
    res_large_N_with_constraints = solve_optimization_using_scipy(N, L, a, b, with_inequality=True)
    plot_solution(N, res_large_N_with_constraints.x, a, b, "N=20 With Inequality Constraints", "N20_constraints", is_with_inequality_constraints=True)
    print("Solution for N=20:", res_large_N_with_constraints.x)
    print()

# making the graphs for the scipy optimization
# make_all_scipy_graph()



##================================================================================================
## Third method : convex relaxation (for fun)
##================================================================================================
'''
## function to solve the chain problem using cvxpy for the convex relaxation method
arguments:
    z = [x1,...,xN,y1,...,yN] is the vector of the variables
    a,b are the coordinates of the end points ((0,0) is the starting point)
    L is the length of each of the bars (supposed to be the same)
'''
def solve_cvxpy(z, a, b, L):
    N = int(len(z)/2)

    # define variables
    u = cp.Variable((N+2,2))
    X = cp.Variable((N+2,N+2), symmetric = True)

    # define per block matrix
    I = np.eye(2)
    M = cp.bmat([[I, u.T],[u,X]])

    # define constraints
    constraints = []
    for i in range(N+1):
        constraints += [X[i][i] - 2*X[i][i+1] + X[i+1][i+1] - L**2 == 0]
    constraints += [X[0][0] == 0]
    constraints += [X[N+1][N+1] == a**2 + b**2]
    constraints += [u[0][0] == 0]
    constraints += [u[0][1] == 0]
    constraints += [u[N+1][0] == a]
    constraints += [u[N+1][1] == b]
    constraints += [M >> 0]

    # define objective function
    obj = cp.Minimize(sum(u[:,1]))

    # solve SDP problem
    prob = cp.Problem(obj, constraints)
    prob.solve()
    
    return [u.value, X.value]


'''
## function to compare the convex relaxation method with the Newton method
'''
def compare_methodes():
    N = 5
    L = 1.0/(N-1)
    a,b = 1.,-.1
    z = np.zeros(2*N)
    z[0:N] = np.linspace(1./(N+1), a-1./(N+1), N)
    z[N:2*N] =[b*i -.1*(i-a/2.)**2 for i in z[0:N]]

    u, X = solve_cvxpy(z,a,b, L)
    z_cvx_zol = np.concatenate((u.T[0],u.T[1]))
    print("Note that if the first two eigenvaues are much bigger than the rest, the rank of X is close to 2")
    print("Eigenvalues:", np.linalg.eig(X)[0])

    os.makedirs("Results/Convex_Relaxation", exist_ok=True)

    plot_chain(z_cvx_zol, a, b, legend=["Convex Relaxation"], save_fig=True, filename="Results/Convex_Relaxation/Output-chain.pdf")

    lambdas = 0.1*np.random.random(N+1)
    # without backtracking
    _, _, opt_gap_0 = solve_chain(z, lambdas, L, a, b, Nmax = 100, tol = 1e-6, backtracking = 0)
    # with backtracking
    _, _, opt_gap_2 = solve_chain(z, lambdas, L, a, b, Nmax = 100, tol = 1e-6, backtracking = 2)
    # with convex relaxation initial guess and no backtracking for the Newton method
    z_cvx_init = np.zeros(2*N)
    z_cvx_init[0:N] = u.T[0][1:N+1]
    z_cvx_init[N:2*N] = u.T[1][1:N+1] 
    _, _, opt_gap_convex_init = solve_chain(z_cvx_init, lambdas, L, a, b, Nmax = 100, tol = 1e-6, backtracking = 0)

    labels = ["without backtracking", "with backtracking", "Convex Relaxation Initial Guess without backtracking"]
    plt.figure()
    plt.loglog(opt_gap_0, 'o-')
    plt.loglog(opt_gap_2, 'o-')
    plt.loglog(opt_gap_convex_init, 'o-')
    plt.legend(labels)
    plt.grid()
    plt.xlabel('Iteration count')
    plt.ylabel('Optimality gap (norm residual)')
    plt.savefig("Results/Convex_Relaxation/Output-convergence_comparaison.pdf")

# comparing the methods
# compare_methodes()