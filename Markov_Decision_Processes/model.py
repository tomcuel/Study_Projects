"""
Model of Brumelle & McGill (1993): demand laws, exact DP solver (value iteration),
exact evaluation of a fixed policy, and policy iteration.

Notation of the paper: class 1 = most expensive, books last. fares[k-1] = f_k,
p[k] = p_k (seats protected for classes 1..k, p[0] = p_0 = 0), ER[k, s] = ER_k[s].
"""
import numpy as np
from scipy.stats import poisson, nbinom, norm


# ---------------- demand laws (pmf arrays P[X = 0], P[X = 1], ...) ----------------
def poisson_pmf(mean, dmax=400):
    return poisson.pmf(np.arange(dmax + 1), mean)


def negbinom_pmf(mean, var, dmax=400):
    # negative binomial with given mean and variance (needs var > mean)
    q = mean / var
    r = mean * q / (1 - q)
    return nbinom.pmf(np.arange(dmax + 1), r, q)


def normal_pmf(mean, std, dmax=400):
    # normal rounded to the nearest integer, mass below 0 goes to 0 and mass above dmax to dmax
    d = np.arange(dmax + 1)
    edges = np.concatenate(([-np.inf], d[:-1] + 0.5, [np.inf]))
    pmf = np.diff(norm.cdf(edges, mean, std))
    return pmf / pmf.sum()


def exponential_pmf(mean, dmax=None):
    # exponential rounded to the nearest integer (section 4.1 of BMG), mass above dmax goes to dmax
    if dmax is None:
        dmax = int(25 * mean)
    edges = np.concatenate(([0.0], np.arange(dmax) + 0.5, [np.inf]))
    return np.diff(1 - np.exp(-edges / mean))


# ---------------- value iteration ----------------
def solve_dp(fares, demand_pmfs, C):
    """Bellman equation (3) solved backwards: class 1 first, then class 2, ..."""
    fares = np.asarray(fares, dtype=float)
    n = len(fares)
    ss = np.arange(C + 1)
    ER = np.zeros((n + 1, C + 1))       # ER[0] = ER_0 = 0
    p = np.zeros(n, dtype=int)          # p[0] = p_0 = 0
    for k in range(n):                  # ER_k -> ER_{k+1}: class k+1 is selling
        f, pmf = fares[k], demand_pmfs[k]
        g = -f * ss + ER[k]             # g(q) = ER_k[q] - f_{k+1} q
        p[k] = int(np.argmax(g))        # smallest argmax <=> condition (20)
        for s in range(C + 1):
            S = np.maximum.accumulate(g[s::-1])[::-1]   # S[j] = max g[j..s]
            total = sum(pmf[x] * S[s - x] for x in range(min(s - 1, len(pmf) - 1) + 1))
            total += pmf[s:].sum() * S[0] if s < len(pmf) else 0.0   # X_{k+1} >= s: q in [0, s]
            ER[k + 1, s] = f * s + total
    # marginal value of a seat dER[k, s] = ER_k[s] - ER_k[s-1]
    dER = np.full((n + 1, C + 1), np.inf)
    dER[:, 1:] = ER[:, 1:] - ER[:, :-1]
    return {"ER": ER, "p": p, "dER": dER, "value": ER[n, C]}


def is_concave(v, tol=1e-8):
    return bool(np.all(np.diff(v, 2) <= tol))


# ---------------- exact evaluation of a fixed policy ----------------
def evaluate_nested_policy(fares, p, demand_pmfs, C):
    """
    Exact expected revenue of the protection levels p (no simulation).
    We follow the distribution of the number of seats left, class n first, class 1 last.
    """
    n = len(fares)
    dist = np.zeros(C + 1)
    dist[C] = 1.0
    revenue = 0.0
    for k in range(n, 0, -1):
        f, pmf = fares[k - 1], demand_pmfs[k - 1]
        p_prev = min(int(p[k - 1]), C)      # class k is closed when p_{k-1} seats are left
        new_dist = np.zeros(C + 1)
        for s in range(C + 1):
            if dist[s] == 0:
                continue
            free = max(s - p_prev, 0)       # seats class k is allowed to sell
            # demand x < free: everything is sold
            for x in range(min(free, len(pmf))):
                revenue += dist[s] * pmf[x] * f * x
                new_dist[s - x] += dist[s] * pmf[x]
            # demand x >= free: sell exactly `free` seats
            tail = pmf[free:].sum()
            revenue += dist[s] * tail * f * free
            new_dist[s - free] += dist[s] * tail
        dist = new_dist
    return revenue


# ---------------- policy iteration ----------------
def evaluate_policy(fares, demand_pmfs, C, p):
    """
    Value functions ER_k^p[s] of a fixed policy p (recursion (9), no max)
    """
    n = len(fares)
    ER = np.zeros((n + 1, C + 1))
    for k in range(n):                  # class k+1 sells u = min((s - p_k)^+, X_{k+1})
        pmf = demand_pmfs[k]
        d = np.arange(len(pmf))
        for s in range(C + 1):
            u = np.minimum(max(s - p[k], 0), d)
            ER[k + 1, s] = np.dot(pmf, fares[k] * u + ER[k][s - u])
    return ER


def policy_iteration(fares, demand_pmfs, C, p0=None, sequential=False, max_iter=50):
    """
    Evaluate p, improve every p_k greedily: p_k <- argmax_q ER_k^p[q] - f_{k+1} q, repeat
    With sequential=True the levels are improved one after the other (p_1, then p_2 with the new ER_2, ...): this is exactly value iteration and converges in one sweep
    """
    n = len(fares)
    q = np.arange(C + 1)
    p = np.zeros(n, dtype=int) if p0 is None else np.array(p0, dtype=int)
    ER = evaluate_policy(fares, demand_pmfs, C, p)
    for it in range(1, max_iter + 1):
        new_p = p.copy()
        for k in range(1, n):
            if sequential:
                ER = evaluate_policy(fares, demand_pmfs, C, new_p)
            new_p[k] = int(np.argmax(ER[k] - fares[k] * q))
        ER = evaluate_policy(fares, demand_pmfs, C, new_p)
        if np.array_equal(new_p, p):
            return {"p": p, "value": ER[n, C], "n_iter": it}
        p = new_p
    raise RuntimeError("policy iteration did not converge")
