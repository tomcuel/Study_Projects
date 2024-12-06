import numpy as np
from scipy.optimize import minimize

class Auto_SQP:
    def __init__(self):
        # Initialize with default options
        self.options = {'disp': False, 'maxiter': 500}

    @staticmethod
    def objective(x):
        """Objective function: f(x) = exp(x1 * x2 * x3 * x4 * x5) - 1/2 * (x1^3 + x2^3 + 1)^2"""
        x1, x2, x3, x4, x5 = x
        return np.exp(x1 * x2 * x3 * x4 * x5) - 0.5 * (x1**3 + x2**3 + 1)**2

    @staticmethod
    def objective_grad(x):
        """Gradient of the objective function."""
        x1, x2, x3, x4, x5 = x
        grad = np.zeros(5)
        exp_term = np.exp(x1 * x2 * x3 * x4 * x5)
        grad[0] = exp_term * (x2 * x3 * x4 * x5) - 1.5 * (x1**2)
        grad[1] = exp_term * (x1 * x3 * x4 * x5) - 1.5 * (x2**2)
        grad[2] = exp_term * (x1 * x2 * x4 * x5)
        grad[3] = exp_term * (x1 * x2 * x3 * x5)
        grad[4] = exp_term * (x1 * x2 * x3 * x4)
        return grad

    @staticmethod
    def constraints(x):
        """Constraint functions."""
        x1, x2, x3, x4, x5 = x
        g1 = sum([xi**2 for xi in x]) - 10
        g2 = x2 * x3 - 5 * x4 * x5
        g3 = x1**3 + x2**3 + 1
        return [g1, g2, g3]

    @staticmethod
    def constraint_eq_grad(x):
        """Gradient of the constraint functions."""
        x1, x2, x3, x4, x5 = x
        grad = np.zeros((3, 5))  # 3 constraints, 5 variables
        grad[0, :] = 2 * np.array(x)  # Gradient of g1
        grad[1, 1] = x3  # Gradient of g2
        grad[1, 2] = x2
        grad[1, 3] = -5 * x5
        grad[1, 4] = -5 * x4
        grad[2, 0] = 3 * x1**2  # Gradient of g3
        grad[2, 1] = 3 * x2**2
        return grad
    
    def callback(self, xk):
        """Callback function to display solutions at each step."""
        print(f"Current solution: {xk}")

    def solve(self, x0, use_callback):

        # Define constraints in SciPy's format
        constraints_dict = [
            {'type': 'eq', 'fun': lambda x: self.constraints(x)[0], 'jac': lambda x: self.constraint_eq_grad(x)[0]},
            {'type': 'eq', 'fun': lambda x: self.constraints(x)[1], 'jac': lambda x: self.constraint_eq_grad(x)[1]},
            {'type': 'eq', 'fun': lambda x: self.constraints(x)[2], 'jac': lambda x: self.constraint_eq_grad(x)[2]},
        ]

        # Run optimization
        result = minimize(
            self.objective,
            x0,
            jac=self.objective_grad,
            constraints=constraints_dict,
            method='SLSQP',
            options=self.options,
            callback=self.callback if use_callback else None
        )

        # Return the optimal solution, objective value, and number of iterations
        return result.x, result.fun, result.nit
        