# Diﬀerentiable Optimisation Projects
> This repository contains two projects exploring numerical optimization techniques applied to different problems. The first project focuses on Newton’s method for solving equilibrium conditions, while the second project addresses image deblurring using proximal gradient methods and convex optimization.

#### Tables of contents
* [Path Tree](#path-tree)
* [Direct Links to Folders](#direct-links-to-folders)  
* [Virtual Environment and Libraries](#virtual-environment-and-libraries)  
* [Running the code](#running-the-code) 
* [Project 1: Implementation of Newton's Method](#project-1-implementation-of-newtons-method)
* [Project 2: Image Deblurring](#project-2-image-deblurring)

## Path tree
```
Diﬀerentiable_Optimisation_Projects/
├── TP1/
│   ├── Results/                
│   ├── Report    
│   └── Python Code
│
└── TP2/
    ├── Results/              
    ├── Report    
    └── Python Code     
```

## Direct links to folders
* [TP1](./TP1/) : Implementation of the Newton's method for finding static equilibrium of a chain
    * [Results](./TP1/Results/) : contains folders to store the different result pictures
* [TP2](./TP2/) : Implementation of the proximal gradient methods for image deblurring  
    * [Results](./TP2/Results/) : contains folders to store the different result pictures

## Virtual Environnment and Librairies
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

I used those librairies for this project : 
```py
import os
import time
import numpy as np
import matplotlib
import matplotlib.pyplot as plt 
from scipy.optimize import minimize
import cvxpy as cp
import pylops
from scipy.sparse import csr_matrix
```

## Running the code 
* You must open your VS-Code window on each TP, otherwise there will be mistakes with repositeries and pictures creations
* Uncomment the function calls to execute what you want (I did it because it took too much time otherwise to compute)


## Project 1 : Implementation of Newton's Method

### Overview
> This project explores the application of Newton’s method for solving an optimization problem related to finding the static equilibrium of a chain composed of rigid bars in two-dimensional space. The problem is formulated as an optimization problem, initially with equality constraints. In the second part, inequality constraints are introduced, and the scipy.optimize library is used to compare results with the manually implemented Newton method.

### Contents

#### Problem Formulation:
* Mathematical model of a chain composed of rigid bars.
* Optimality conditions using the Karush-Kuhn-Tucker (KKT) conditions.
* Influence of problem parameters on solution feasibility.

#### Newton’s Method Implementation:
* Standard Newton's method for solving nonlinear equations.
* Use of backtracking line search and uniform gridding to ensure convergence.
* Investigation of convergence behavior with and without backtracking.
* Testing the influence of the different parameters such as KKT initial guess, bar's lenghts, bar's numbers, …

#### Comparison with scipy.optimize:
* Reformulation of the problem to include inequality constraints.
* Application of Sequential Quadratic Programming (SQP) using scipy.optimize.minimize.
* Analysis of the impact of constraints on convergence and solution quality.

### Key Results
* The Newton method is highly effective but can diverge without proper step-size control.
* Backtracking significantly improves convergence and stability.
* scipy.optimize provides comparable results but is more flexible in handling inequality constraints.

### More details and key pictures 
[See the PDF report](TP1/Cuel_Project1_Final.pdf)

## Project 2 : Image Deblurring 

### Overview
> This project focuses on solving an image deblurring problem using convex optimization techniques. The goal is to recover a sharp image from a blurred observation by solving an inverse problem. The optimization problem is formulated with an l1 regularization term to promote sparsity in the image representation.

### Contents

#### Problem Formulation:
* Modeling the blurring process as a linear transformation.
* Formulation of the inverse problem using regularization.
* Mathematical analysis of the convexity and conditioning of the problem.

#### Proximal Gradient Methods:
* Implementation of Iterative Shrinkage-Thresholding Algorithm (ISTA) --> classic proximal gradient method
* Implementation of Fast Iterative Shrinkage-Thresholding Algorithm (FISTA) for accelerated convergence --> Nesterov's accelerated proximal gradient method
* Comparison of ISTA and FISTA in terms of convergence rates and deblurring performances.

#### Experiments:
* Testing the influence of the regularization parameter ε and of the step size.
* Evaluating the effect of different blurring levels on the results.
* Studying the impact of image downsampling on computational complexity and accuracy.

#### Use of cvxpy:
* Solving the optimization problem using the cvxpy library.
* Discussion on computational limitations due to the interior-point method.
* Comparison with ISTA/FISTA in terms of performance and solution quality.

### Key Results:
* FISTA converges significantly faster than ISTA while maintaining solution quality.
* Increasing the blurring makes the problem more difficult to solve accurately because of matrix sizes.
* cvxpy struggles with large-scale images due to high computational complexity.
* Downsampling the image reduces computational cost but degrades the quality of the restored image.

### More details and key pictures 
[See the PDF report](TP2/CUEL_Project2_Final.pdf)