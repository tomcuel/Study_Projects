import numpy as np
from sympy import symbols, diff, lambdify, exp

class Hand_Made_SQP:
    def __init__(self):
        # Define symbolic variables
        x1, x2, x3, x4, x5 = symbols('x1 x2 x3 x4 x5')
        self.variables = [x1, x2, x3, x4, x5]

        # Define the symbolic objective function
        self.f_symbols = exp(x1 * x2 * x3 * x4 * x5) - 0.5 * (x1**3 + x2**3 + 1)**2

        # Gradient and Hessian of the objective function
        self.grad_f_symbols = [diff(self.f_symbols, var) for var in self.variables]
        self.hessian_f_symbols = [[diff(grad, var) for var in self.variables] for grad in self.grad_f_symbols]

        # Convert symbolic objective, gradient, and Hessian to numerical functions
        self.f = lambdify(self.variables, self.f_symbols, 'numpy')
        self.grad_f = lambdify(self.variables, self.grad_f_symbols, 'numpy')
        self.hessian_f = lambdify(self.variables, self.hessian_f_symbols, 'numpy')

        # Define constraints
        g1 = x1**2 + x2**2 + x3**2 + x4**2 + x5**2 - 10
        g2 = x2 * x3 - 5 * x4 * x5
        g3 = x1**3 + x2**3 + 1
        self.g_symbols = [g1, g2, g3]

        # Gradient and Hessians of constraints
        self.grad_g_symbols = [[diff(constraint, var) for var in self.variables] for constraint in self.g_symbols]
        self.hessian_g_symbols = [[[diff(diff(constraint, var1), var2) for var2 in self.variables] for var1 in self.variables] for constraint in self.g_symbols]

        # Convert symbolic constraints to numerical functions
        self.g = lambdify(self.variables, self.g_symbols, 'numpy')
        self.grad_g = lambdify(self.variables, self.grad_g_symbols, 'numpy')
        self.hessian_g = lambdify(self.variables, self.hessian_g_symbols, 'numpy')

    def optimize(self, x_k, lambda_k, use_callback, tol=1e-6, max_iter=500):
        n = np.size(x_k)
        m = np.size(lambda_k)
        nb_iter = 0

        while nb_iter < max_iter:
            # Evaluate objective and constraints
            grad_f = np.array(self.grad_f(*x_k))
            hessian_f = np.array(self.hessian_f(*x_k))
            g = np.array(self.g(*x_k))
            grad_g = np.array(self.grad_g(*x_k))
            hessian_g = np.array(self.hessian_g(*x_k))

            # KKT conditions
            # we're now looking if x_k, lambda_k is a KKT-Pair : gradf(x_k) + Jacg(x_k)lambda_k = 0n, if that's the case, we stop our search 
            kkt_lhs = grad_f + np.dot(np.transpose(grad_g), lambda_k)
            if np.linalg.norm(kkt_lhs) < tol and np.linalg.norm(g) < tol:
                break

            # otherwise we solve the following problem 
            # find x_solve local optimal solution of the following equation : 
            #  Hess_x_lagrangien(x,lambda)x_solve + gradf(x) + Jacg(x)(lambda + lambda_solve) = 0n 
            # and g(x) + Jacg(x)(x_solve) = 0m
            # where x_solve, lambda_vals + lambda_solve is a KKT-Pair : gradf(x_solve) + Jacg(x_solve)(lambda_vals + lambda_solve) = 0n

            # Construct Lagrangian Hessian
            lagrangian_hessian = hessian_f.copy()
            for i, lambda_i in enumerate(lambda_k):
                lagrangian_hessian += lambda_i * hessian_g[i]

            # Solve linear system for x_solve and lambda_solve
            A = np.block([
                [lagrangian_hessian, np.transpose(grad_g)],
                [grad_g, np.zeros((m, m))]
            ])
            b = np.hstack([-grad_f - np.dot(np.transpose(grad_g), lambda_k), -g])

            solution = np.linalg.solve(A, b)
            x_solve = solution[:n]
            lambda_solve = solution[n:]

            # Update x_k and lambda_k
            x_k = x_k + x_solve
            lambda_k = lambda_k + lambda_solve
            nb_iter += 1

            # printing the solution at each step if use_callback is True
            if use_callback:
                print(f"Current solution at the iteration n°{nb_iter}: {x_k} and f(x_k) = {self.f(*x_k)}")

            # Check for convergence
            if np.linalg.norm(x_solve) < tol:
                break

        return x_k, self.f(*x_k), nb_iter
