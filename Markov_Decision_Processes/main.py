"""
Runs all the experiments of the report and the slides and prints the results
    python main.py
(figures: python figures.py)
"""
import time
import numpy as np
from scipy.optimize import brentq
from scipy.stats import poisson

from model import poisson_pmf, negbinom_pmf, normal_pmf, exponential_pmf, solve_dp, is_concave, evaluate_nested_policy, policy_iteration
from heuristics import emsr_a, emsr_b
from extensions import simulate_policy, solve_lee_hersh, arrival_matrix

# 5-class example used everywhere (section 5.1)
FARES5 = [300, 210, 160, 120, 80]
MEANS5 = [10, 15, 20, 25, 30]

# setting of BMG section 4 (Table I)
BMG_MEANS = [40, 60, 80]
BMG_STDS = [16, 24, 32]


def bmg_pmfs(cv=0.4):
    return [normal_pmf(m, cv * m) for m in BMG_MEANS]


def loss(fares, p, pmfs, C, opt_value):
    """revenue lost by policy p compared to the optimum, in %"""
    return 100 * (1 - evaluate_nested_policy(fares, p, pmfs, C) / opt_value)


# test cases of appendix A (EMSRb, no control, Monte Carlo, policy iteration)
TEST_CASES = [
    # name, fares, pmfs, C
    ("2 classes (Littlewood)", [250, 100], [poisson_pmf(15), poisson_pmf(25)], 40),
    ("4 classes (Belobaba)", [1000, 700, 500, 350],
     [normal_pmf(10, 3), normal_pmf(15, 5), normal_pmf(20, 7), normal_pmf(30, 10)], 80),
    ("5 classes, C=100", FARES5, [poisson_pmf(m) for m in MEANS5], 100),
    ("5 classes, C=50", FARES5, [poisson_pmf(m) for m in MEANS5], 50),
    ("5 classes, C=160", FARES5, [poisson_pmf(m) for m in MEANS5], 160),
    ("5 classes, wide fares", [1105, 573, 297, 154, 80], [poisson_pmf(m) for m in MEANS5], 100),
    ("5 classes, var = 4 mean", FARES5, [negbinom_pmf(m, 4 * m) for m in MEANS5], 100),
    ("5 classes, close fares", [115, 110, 105, 100, 95], [poisson_pmf(m) for m in MEANS5], 100),
    ("8 classes", [307, 305, 303, 301, 299, 297, 295, 80], [poisson_pmf(15)] * 7 + [poisson_pmf(40)], 130),
    ("BMG Table I ex. 1", [1.0, 0.7, 0.6], bmg_pmfs(), 100),
    ("BMG Table I ex. 6", [1.0, 0.9, 0.8], bmg_pmfs(), 100),
]


def checks():
    print("=== Checks of the solver ===")
    # 2 classes: Littlewood, p1 = smallest p with f1 P[X1 > p] <= f2
    f1, f2, C = 250, 100, 40
    res = solve_dp([f1, f2], [poisson_pmf(15), poisson_pmf(25)], C)
    p1 = min(p for p in range(C + 1) if f1 * poisson.sf(p, 15) <= f2)
    print(f"Littlewood (n=2): DP p1 = {res['p'][1]}, formula p1 = {p1}")
    for fa, fb, ma, mb in [(250, 100, 15, 25), (300, 80, 10, 30), (60, 50, 20, 20)]:
        pmfs = [poisson_pmf(ma), poisson_pmf(mb)]
        print(f"  n=2, f=({fa},{fb}): DP p1 = {solve_dp([fa, fb], pmfs, 40)['p'][1]}, EMSRa p1 = {emsr_a([fa, fb], pmfs, 40)[1]}")

    # 5-class example
    pmfs = [poisson_pmf(m) for m in MEANS5]
    res = solve_dp(FARES5, pmfs, 100)
    ER, dER, p = res["ER"], res["dER"], res["p"]
    print("ER_k concave for all k:", all(is_concave(ER[k]) for k in range(6)))
    print("levels p_1..p_4 =", p[1:].tolist(), "nested:", all(np.diff(p[1:]) >= 0))
    print("dER_k <= dER_k+1 (ex. 3.9):", all(np.all(dER[k, 1:] <= dER[k + 1, 1:] + 1e-8) for k in range(5)))
    print(f"value ER_5[100] = {res['value']:.4f}, exact evaluation of p* = "
          f"{evaluate_nested_policy(FARES5, p, pmfs, 100):.4f}")
    print()


def table_1():
    print("=== Table I (BMG section 4) ===")
    pmfs = bmg_pmfs()
    sf1 = 1 - np.cumsum(pmfs[0])        # P[X1 > a]
    sf2 = 1 - np.cumsum(pmfs[1])
    published = [(0.6, 0.7, 70, 80, 0.37), (0.6, 0.8, 80, 87, 0.32), (0.6, 0.9, 86, 91, 0.19),
                 (0.7, 0.8, 64, 75, 0.41), (0.7, 0.9, 73, 82, 0.45), (0.8, 0.9, 57, 70, 0.50)]
    print("ex  f3   f2  | p1 | p2 EMSRa (pub) | p2 opt (pub) | loss % (pub) | P[X1>p1]  P[X1>p1,X1+X2>p2]")
    for i, (f3, f2, pa_pub, po_pub, loss_pub) in enumerate(published, 1):
        fares = [1.0, f2, f3]
        res = solve_dp(fares, pmfs, 100)
        pa = emsr_a(fares, pmfs, 100, mode="normal", normal_params=list(zip(BMG_MEANS, BMG_STDS)))
        p1, p2 = res["p"][1], res["p"][2]
        # joint probability of eq. (2): sum over X1 = a > p1 of P[X1 = a] P[X2 > p2 - a]
        joint = sum(pmfs[0][a] * (sf2[p2 - a] if p2 >= a else 1.0) for a in range(p1 + 1, len(pmfs[0])))
        print(f"{i:2d}  {f3}  {f2} | {p1:2d} | {pa[2]:3d} ({pa_pub})     | {p2:3d} ({po_pub})   | {loss(fares, pa, pmfs, 100, res['value']):.2f} ({loss_pub:.2f})  | {sf1[p1]:.3f}     {joint:.3f}")
    print()


def table_2():
    print("=== Table II (f2 = 0.9, f3 = 0.7) ===")
    pmfs = bmg_pmfs()
    fares = [1.0, 0.9, 0.7]
    for C, pub in [(82, 0.54), (100, 0.45), (120, 0.35), (140, 0.24), (160, 0.14)]:
        res = solve_dp(fares, pmfs, C)
        pa = emsr_a(fares, pmfs, C, mode="normal", normal_params=list(zip(BMG_MEANS, BMG_STDS)))
        print(f"C = {C}: EMSRa loss = {loss(fares, pa, pmfs, C, res['value']):.2f} %  (published {pub} %)")
    print()


def exp_closed_form(rho):
    """
    EMSRa error on p2 in seats (unit = 100 seats): optimum (1 + d) e^-d = 1/rho, EMSRa d = 2 ln(rho)
    """
    d_opt = brentq(lambda d: (1 + d) * np.exp(-d) - 1 / rho, 0, 50)
    return 100 * (2 * np.log(rho) - d_opt)


def exp_solver(f2, f3, mean=100, C=600):
    """
    Same thing with our solver: exponential demands rounded to integers, p2 of the DP and of EMSRa
    """
    pmfs = [exponential_pmf(mean)] * 3
    fares = [1.0, f2, f3]
    p_opt = solve_dp(fares, pmfs, C)["p"]
    p_a = emsr_a(fares, pmfs, C)
    return p_opt, p_a


def counterexample():
    print("=== Section 4.1: exponential demands (mean 100 seats) ===")
    rho_star = brentq(lambda r: 1 + 2 * np.log(r) - r, 2, 6)
    print(f"closed form: rho* = {rho_star:.4f}")
    print("f2    f3   | rho  | closed form | solver: p1  p2 opt  p2 EMSRa  error")
    for f2, f3 in [(0.5, 0.25), (0.4, 0.1)]:          # the two cases of the paper
        p_opt, p_a = exp_solver(f2, f3)
        print(f"{f2:.2f}  {f3:.2f} | {f2 / f3:.2f} | {exp_closed_form(f2 / f3):+6.1f} | {p_opt[1]:3d}  {p_opt[2]:4d}    {p_a[2]:4d}    {p_a[2] - p_opt[2]:+4d}")
    print()


def counterexample_curve(rhos, f3=0.15):
    """
    error of EMSRa from the solver for several rho = f2/f3 (f3 fixed), used for fig. 3
    """
    return [int(np.subtract(*exp_solver(f3 * r, f3)[::-1])[2]) for r in rhos]


def sensitivity():
    print("=== Sensitivity of the levels (fig. 2) ===")
    pmfs = [poisson_pmf(m) for m in MEANS5]
    big = solve_dp(FARES5, pmfs, 200)["p"]
    print("(a) levels for C = 200:", big[1:].tolist(), "(and p_k(C) = min(p_k, C))")
    for C in [30, 60]:
        print(f"    C = {C}:", solve_dp(FARES5, pmfs, C)["p"][1:].tolist())
    for ratio in [1.1, 10]:
        fares = 80 * ratio ** (np.arange(5)[::-1] / 4)      # geometric fares, f5 = 80
        print(f"(b) f1/f5 = {ratio}:", solve_dp(fares, pmfs, 200)["p"][1:].tolist())
    fares = [1.0, 0.9, 0.7]
    for cv in [0.05, 0.6]:
        pm = bmg_pmfs(cv)
        po = solve_dp(fares, pm, 250)["p"]
        pa = emsr_a(fares, pm, 250, mode="normal", normal_params=[(m, cv * m) for m in BMG_MEANS])
        print(f"(c) cv = {cv}: p2 opt = {po[2]}, p2 EMSRa = {pa[2]}, gap = {po[2] - pa[2]}")
    print()


def flatness():
    print("=== Cost of a wrong p2 (Table I ex. 1) ===")
    pmfs = bmg_pmfs()
    fares = [1.0, 0.7, 0.6]
    res = solve_dp(fares, pmfs, 100)
    p1, p2 = res["p"][1], res["p"][2]
    for delta in [5, 10, 20]:
        print(f"p2 = p2* - {delta}: loss = {loss(fares, [0, p1, p2 - delta], pmfs, 100, res['value']):.2f} %")
    print()


def test_cases():
    print("=== Test cases: EMSRa, EMSRb, no control, Monte Carlo ===")
    losses_a, losses_b = [], []
    for name, fares, pmfs, C in TEST_CASES:
        res = solve_dp(fares, pmfs, C)
        la = loss(fares, emsr_a(fares, pmfs, C), pmfs, C, res["value"])
        lb = loss(fares, emsr_b(fares, pmfs, C), pmfs, C, res["value"])
        l0 = loss(fares, np.zeros(len(fares), dtype=int), pmfs, C, res["value"])   # first come first served
        mc, se = simulate_policy(fares, res["p"], pmfs, C)
        gap_mc = 100 * abs(mc - res["value"]) / res["value"]
        print(f"{name:24s} EMSRa {la:5.2f} %  EMSRb {lb:5.2f} %  FCFS {l0:6.2f} %  MC {mc:9.2f} +- {se:.2f} (exact {res['value']:.2f}, gap {gap_mc:.3f} %)")
        if C != 160:                    # C=160 is too big, nothing to protect
            losses_a.append(la)
            losses_b.append(lb)
    print(f"mean loss on {len(losses_a)} cases: EMSRa {np.mean(losses_a):.2f} %, EMSRb {np.mean(losses_b):.2f} %")
    print()


def value_vs_policy_iteration():
    print("=== Value iteration vs policy iteration ===")
    n_same, n_runs = 0, 0
    for name, fares, pmfs, C in TEST_CASES:
        vi = solve_dp(fares, pmfs, C)
        starts = [None, emsr_a(fares, pmfs, C, mode="normal"), [0] + [C] * (len(fares) - 1)]
        sweeps = []
        for p0 in starts:
            pi = policy_iteration(fares, pmfs, C, p0=p0)
            sweeps.append(pi["n_iter"])
            n_runs += 1
            n_same += np.array_equal(pi["p"], vi["p"]) and abs(pi["value"] - vi["value"]) < 1e-6 * vi["value"]
        print(f"{name:24s} p* = {vi['p'][1:].tolist()}, PI sweeps (start p=0 / EMSRa / p=C): {sweeps}")
    print(f"same levels and value in {n_same}/{n_runs} runs")
    _, fares, pmfs, C = TEST_CASES[2]
    print("sequential improvement, sweeps:", policy_iteration(fares, pmfs, C, sequential=True)["n_iter"] - 1)

    # computing time against the number of classes (slide 9)
    print("n   VI (ms)  PI (ms)  PI sweeps")
    for n, t_vi, t_pi, sw in timing():
        print(f"{n:2d}  {t_vi:7.1f}  {t_pi:7.1f}  {sw}")
    print()


def timing(n_max=10):
    rows = []
    for n in range(2, n_max + 1):
        fares = [80 * (300 / 80) ** (k / (n - 1)) for k in range(n)][::-1]
        pmfs = [poisson_pmf(45 / n)] * n
        t0 = time.perf_counter()
        solve_dp(fares, pmfs, 60)
        t1 = time.perf_counter()
        pi = policy_iteration(fares, pmfs, 60)
        t2 = time.perf_counter()
        rows.append((n, 1000 * (t1 - t0), 1000 * (t2 - t1), pi["n_iter"]))
    return rows


def arrival_order():
    print("=== Order of arrivals (Lee & Hersh) ===")
    cases = [([300, 150, 80], 30), ([300, 150, 80], 20), ([1600, 400, 80], 30), ([110, 100, 90], 30)]
    means = [10, 15, 20]
    for fares, C in cases:
        v_dp = solve_dp(fares, [poisson_pmf(m) for m in means], C)["value"]
        v = {o: solve_lee_hersh(fares, arrival_matrix(means, 2000, o), C) for o in ["low-high", "mixed", "high-low"]}
        print(f"f = {fares}, C = {C}: BMG {v_dp:.2f}, Lee-Hersh low-high {v['low-high']:.2f} | mixed {100 * (v['mixed'] / v['low-high'] - 1):+.1f} %, high-low {100 * (v['high-low'] / v['low-high'] - 1):+.1f} %")
    print()


def all_policies():
    """
    All the policies on one model, for 3 fare spreads (3 classes, Poisson demands, means 10, 15, 20, C = 30)
    Poisson demand is used so that Lee & Hersh (Poisson arrivals) is the same problem as BMG: with the low-before-high order it must give back the optimum
    Revenues in % of the BMG optimum
    """
    means, C = [10, 15, 20], 30
    pmfs = [poisson_pmf(m) for m in means]
    rows = []
    for fares in [[110, 100, 90], [300, 150, 80], [1600, 400, 80]]:
        res = solve_dp(fares, pmfs, C)
        row = {"fares": fares, "optimal": res["value"], "p": res["p"][1:].tolist()}
        for name, p in [("FCFS", np.zeros(3, dtype=int)), ("EMSRa", emsr_a(fares, pmfs, C)), ("EMSRb", emsr_b(fares, pmfs, C))]:
            row[name] = 100 * evaluate_nested_policy(fares, p, pmfs, C) / res["value"]
        for order in ["low-high", "mixed", "high-low"]:
            row["LH " + order] = 100 * solve_lee_hersh(fares, arrival_matrix(means, 2000, order), C) / res["value"]
        rows.append(row)
    return rows


def print_all_policies():
    print("=== All policies, 3 classes, C = 30 (revenue in % of the optimum) ===")
    print("fares            p*        | FCFS    EMSRa   EMSRb  | LH low-high  mixed   high-low")
    for r in all_policies():
        print(f"{str(r['fares']):16s} {str(r['p']):9s} | {r['FCFS']:6.2f}  {r['EMSRa']:6.2f}  {r['EMSRb']:6.2f} | {r['LH low-high']:7.2f}    {r['LH mixed']:6.2f}  {r['LH high-low']:6.2f}")
    print()


if __name__ == "__main__":
    checks()
    table_1()
    table_2()
    counterexample()
    sensitivity()
    flatness()
    test_cases()
    value_vs_policy_iteration()
    arrival_order()
    print_all_policies()
