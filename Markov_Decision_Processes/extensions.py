"""
Things that go beyond the article (appendix A of the report):
 - Monte Carlo simulation of a policy, to check the exact evaluation
 - Lee & Hersh (1993) model, where requests can arrive in any order
"""
import numpy as np


def simulate_policy(fares, p, demand_pmfs, C, n_sims=20_000, seed=0):
    """
    Simulate n_sims flights with protection levels p 
    Returns mean revenue and its standard error
    """
    rng = np.random.default_rng(seed)
    n = len(fares)
    s = np.full(n_sims, C, dtype=float)
    revenue = np.zeros(n_sims)
    for k in range(n, 0, -1):           # class n books first
        pmf = demand_pmfs[k - 1]
        x = rng.choice(np.arange(len(pmf)), size=n_sims, p=pmf / pmf.sum())
        u = np.minimum(np.clip(s - p[k - 1], 0, None), x)
        revenue += fares[k - 1] * u
        s -= u
    return revenue.mean(), revenue.std(ddof=1) / np.sqrt(n_sims)


# Lee & Hersh
# T small periods, at most one request per period: class j with probability lam[t, j]
# V(t, s) = V(t-1, s) + sum_j lam_j(t) * (f_j - (V(t-1, s) - V(t-1, s-1)))^+

def solve_lee_hersh(fares, lam, C):
    T, n = lam.shape
    V = np.zeros(C + 1)                 # no period left -> 0
    for t in range(T):                  # lam[0] is the last period before departure
        dV = np.full(C + 1, np.inf)     # cannot sell with 0 seat
        dV[1:] = V[1:] - V[:-1]
        V = V + sum(lam[t, j] * np.maximum(fares[j] - dV, 0) for j in range(n))
    return V[C]


def arrival_matrix(means, T_per_class, order):
    """
    order = "low-high": class n first, ..., class 1 last (the BMG assumption)
            "high-low": class 1 first (reversed)
            "mixed": every class can arrive at any time
    Row 0 is the last period before departure
    """
    n = len(means)
    T = T_per_class * n
    lam = np.zeros((T, n))
    if order == "mixed":
        for j in range(n):
            lam[:, j] = means[j] / T
        return lam
    # classes in the order they arrive in time
    time_order = list(range(n))[::-1] if order == "low-high" else list(range(n))
    for slot, j in enumerate(time_order):
        hi = T - slot * T_per_class     # first in time = high row index
        lam[hi - T_per_class:hi, j] = means[j] / T_per_class
    return lam
