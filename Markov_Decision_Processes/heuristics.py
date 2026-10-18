"""
EMSRa (Belobaba 1987, eqs. (2)-(5) of BMG) and EMSRb (Belobaba 1992, extension)
They return protection levels in the same format as solve_dp: p[k] = p_k, p[0] = 0
"""
import numpy as np
from scipy.stats import norm


def littlewood(ratio, pmf):
    """
    Discrete Littlewood rule: protect the p-th seat while P[X >= p] > ratio (ratio = f_low / f_high)
    """
    sf = 1.0 - np.cumsum(pmf)           # sf[p] = P[X > p]
    ok = np.where(sf > ratio)[0]
    return int(ok.max()) + 1 if len(ok) else 0


def mean_std(pmf):
    d = np.arange(len(pmf))
    m = np.dot(d, pmf)
    return m, np.sqrt(np.dot((d - m) ** 2, pmf))


def emsr_a(fares, demand_pmfs, C, mode="exact", normal_params=None):
    """
    p_k = sum over the higher classes i <= k of pi_k^i, with f_{k+1} = f_i P[X_i > pi_k^i]
    mode="exact": discrete pmfs. mode="normal": normal quantiles (as in the paper), with normal_params = [(mean, std), ...] if given, otherwise the moments of the pmfs
    """
    n = len(fares)
    p = np.zeros(n, dtype=int)
    params = normal_params if normal_params is not None else [mean_std(q) for q in demand_pmfs]
    for k in range(1, n):
        total = 0.0
        for i in range(1, k + 1):
            ratio = fares[k] / fares[i - 1]          # f_{k+1} / f_i
            if mode == "normal":
                mu, sd = params[i - 1]
                total += max(mu + norm.ppf(1 - ratio) * sd, 0.0)
            else:
                total += littlewood(ratio, demand_pmfs[i - 1])
        p[k] = min(int(round(total)), C)
    return p


def emsr_b(fares, demand_pmfs, C):
    """
    Classes 1..k pooled into one class (demand = sum, fare = demand-weighted mean fare)
    """
    n = len(fares)
    p = np.zeros(n, dtype=int)
    means = [mean_std(q)[0] for q in demand_pmfs]
    for k in range(1, n):
        f_bar = np.dot(fares[:k], means[:k]) / sum(means[:k])
        pooled = demand_pmfs[k - 1]
        for i in range(k - 2, -1, -1):
            pooled = np.convolve(pooled, demand_pmfs[i])
        p[k] = min(littlewood(fares[k] / f_bar, pooled), C)
    return p
