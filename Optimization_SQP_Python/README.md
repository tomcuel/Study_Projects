# Optimization Problem solving using Python and the SQP algorithm
> This is the code and LaTeX report for a small school project in which I implemented the Sequential Quadratic Programming (SQP) algorithm to solve an optimization problem, minimizing an objective function under given constraints.

#### Tables of contents
* [Path Tree](#path-tree)
* [Virtual Environnment](#virtual-environnment)
* [Libraries to derivate](#librairies)
* [Auto Solving](#auto-solving)
* [Manual Implementation of the SQP Algorithm](#manual-implementation-of-the-SQP-algorithm)

## Path Tree
```
Optimization_SQP_Python/
├── auto_SQP_classe.py                                          # creating a class that solve automatically the problem
│
├── hand_made_SQP_classe.py                                     # creating a class using the manuel SQP implementation
│
├── hand_made_SQP_classe_with_constraints_changes.py            # creating a class using the manuel SQP using simplifcation for the implementation
│
└── main.py                                                     # main of the project where everything is linked to be able to make some tests
```

## Virtual Environnment
Since the libraries are not installed on my Mac, I need to set up a virtual environment to access and use the required libraries, here is how to do :

Creating the virtual environnment
```
python3 -m venv path/to/venv
```
Activating the virtual environnment
```
source path/to/venv/bin/activate
```
Downloading the librairies you need in the virtual environnment
```
python3 -m pip install what_you_need
```
To temporarly deactivate the virtual environnment
```
deactivate 
```

## Librairies
I utilized Python libraries to automate the differentiation of mathematical expressions, eliminating the need for manual computation : 
```py
from sympy import symbols, diff, lambdify, exp
```
For example, here is a use case, where variables become symbols, then there is a derivation and the function is reevaluated so it works as intented for a function, and not as a symbolic expression you can't evaluate : 
```py
from sympy import symbols, sin, exp, log, diff, lambdify

# Define a list of variables
n = 5  # Number of variables
variables = symbols(f'x0:{n}')  # Creates x0, x1, ..., x(n-1)

# Define a more complex function involving these variables
# For example: f(x0, x1, x2, ...) = x0^2 + sin(x1*x2) + exp(x3) * log(x4)
f = variables[0]**2 + sin(variables[1] * variables[2]) + exp(variables[3]) * log(variables[4])

# Index of the variable to differentiate with respect to
i = 2  # Example: differentiate with respect to x2

# Compute the derivative
f_derivative = diff(f, variables[i])

# Convert the original function and its derivative into lambdified functions
f_lambdified = lambdify(variables, f)  # Converts f into a callable function
f_derivative_lambdified = lambdify(variables, f_derivative)  # Converts the derivative

# Example: Evaluate the function and its derivative at a specific point
point = [1, 2, 3, 4, 5]  # Replace with your desired values for x0, x1, ..., x(n-1)

f_value = f_lambdified(*point)
f_derivative_value = f_derivative_lambdified(*point)

print(f"Original Function: {f}")
print(f"Derivative with respect to variable at index {i} ({variables[i]}): {f_derivative}")
print(f"Function evaluated at {point}: {f_value}")
print(f"Derivative evaluated at {point}: {f_derivative_value}")
```
and it returns : 
```
Original Function: x0**2 + exp(x3)*log(x4) + sin(x1*x2)
Derivative with respect to variable at index 2 (x2): x1*cos(x1*x2)
Function evaluated at [1, 2, 3, 4, 5]: 88.59291711390853
Derivative evaluated at [1, 2, 3, 4, 5]: 1.920340573300732
```

## Auto Solving
First, I used this automated solving function in the scipy library that are available in Python : 
```py
from scipy.optimize import minimize
```
This is handeld in the following class in the main : 
```py
from auto_SQP_classe import Auto_SQP
```

## Manual Implementation of the SQP Algorithm
They both are in those classes in the main : 
```py
from hand_made_SQP_classe import Hand_Made_SQP
from hand_made_SQP_classe_with_constraints_changes import Hand_Made_SQP_Classe_with_Constraints_Changed
```