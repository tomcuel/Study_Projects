"""
Figures of the report (fig1, fig2, fig3), the timing plot of the slides (fig4) and the comparison of all the policies on one model (fig5)
    python figures.py   -> figures/*.png
"""
import os
import numpy as np
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
from scipy.optimize import brentq

from model import poisson_pmf, solve_dp
from heuristics import emsr_a
from main import (FARES5, MEANS5, BMG_MEANS, bmg_pmfs, timing, all_policies, exp_closed_form, exp_solver, counterexample_curve)

os.makedirs("figures", exist_ok=True)


def fig1_marginal_values():
    res = solve_dp(FARES5, [poisson_pmf(m) for m in MEANS5], 100)
    s = np.arange(1, 101)
    fig, ax = plt.subplots(figsize=(5, 3.6))
    for k in range(1, 5):
        c = f"C{k - 1}"
        pk, f = res["p"][k], FARES5[k]
        ax.plot(s, res["dER"][k, 1:], color=c, label=rf"$\delta ER_{k}[s]$")
        ax.axhline(f, color=c, ls=":", lw=1)
        ax.plot(pk, f, "o", color=c)
        ax.annotate(rf"$p_{k} = {pk}$", (pk, f), xytext=(5, 5), textcoords="offset points", color=c, fontsize=8)
    ax.set_xlabel("seats remaining $s$")
    ax.set_ylabel("marginal value of a seat")
    ax.legend(fontsize=8)
    ax.grid(alpha=0.3)
    fig.tight_layout()
    fig.savefig("figures/fig1_marginal_values.png", dpi=200)


def fig2_sensitivity():
    pmfs = [poisson_pmf(m) for m in MEANS5]
    fig, axs = plt.subplots(1, 3, figsize=(12, 3.4))

    # (a) capacity
    Cs = np.arange(10, 161, 2)
    P = np.array([solve_dp(FARES5, pmfs, C)["p"][1:] for C in Cs])
    for k in range(4):
        axs[0].plot(Cs, P[:, k], label=f"$p_{k + 1}$")
    axs[0].plot(Cs, Cs, "k--", lw=0.8, label="$p = C$")
    axs[0].set_xlabel("capacity $C$")
    axs[0].set_ylabel("protection level (seats)")
    axs[0].set_title("(a) capacity")

    # (b) fare spread, geometric fares with f5 = 80
    ratios = np.linspace(1.1, 10, 40)
    P = np.array([solve_dp(80 * r ** (np.arange(5)[::-1] / 4), pmfs, 200)["p"][1:] for r in ratios])
    for k in range(4):
        axs[1].plot(ratios, P[:, k])
    axs[1].set_xlabel("fare ratio $f_1/f_5$")
    axs[1].set_title("(b) fare spread")

    # (c) demand variability, Table I setting with f2 = 0.9, f3 = 0.7
    fares = [1.0, 0.9, 0.7]
    cvs = np.linspace(0.05, 0.6, 23)
    opt, emsr = [], []
    for cv in cvs:
        pm = bmg_pmfs(cv)
        opt.append(solve_dp(fares, pm, 250)["p"])
        emsr.append(emsr_a(fares, pm, 250, mode="normal", normal_params=[(m, cv * m) for m in BMG_MEANS]))
    opt, emsr = np.array(opt), np.array(emsr)
    axs[2].plot(cvs, opt[:, 2], "C0", label="$p_2$ optimal")
    axs[2].plot(cvs, emsr[:, 2], "C0--", label="$p_2$ EMSRa")
    axs[2].plot(cvs, opt[:, 1], "C1", label="$p_1$")
    axs[2].set_xlabel(r"coefficient of variation $\sigma/\mu$")
    axs[2].set_title("(c) demand variability")

    for ax in axs:
        ax.grid(alpha=0.3)
    axs[0].legend(fontsize=8)
    axs[2].legend(fontsize=8)
    fig.tight_layout()
    fig.savefig("figures/fig2_sensitivity.png", dpi=200)


def fig3_counterexample(slide=False):
    """
    Error of EMSRa on p2 with exponential demands (mean 100 seats) against rho = f2/f3
    Line: closed form / Dots: our solver (solve_dp and emsr_a on rounded exponential demands)
    slide=True: bigger version with the colors of the presentation
    """
    rho = np.linspace(1.05, 6, 200)
    err = [exp_closed_form(r) for r in rho]
    rho_star = brentq(lambda r: 1 + 2 * np.log(r) - r, 2, 6)
    rho_dp = np.array([r for r in np.arange(1.25, 6.01, 0.25) if r not in (2, 4)])   # 2 and 4: paper cases, drawn below
    err_dp = counterexample_curve(rho_dp)

    if slide:
        ink, under, over, bg = "#14202E", "#C2703D", "#2E6F6A", "#F7F5F0"
        fig, ax = plt.subplots(figsize=(6.4, 4.0), facecolor=bg)
        ax.set_facecolor(bg)
        ax.fill_between(rho, err, 0, where=np.array(err) < 0, color=under, alpha=0.18, lw=0)
        ax.fill_between(rho, err, 0, where=np.array(err) > 0, color=over, alpha=0.18, lw=0)
        ax.text(1.75, -14, "protects\ntoo few", color=under, fontsize=11, ha="center")
        ax.text(5.5, 12, "protects\ntoo many", color=over, fontsize=11, ha="center")
        for s in ["top", "right"]:
            ax.spines[s].set_visible(False)
        fs = 10.5
    else:
        ink, under, over = "black", "C3", "C2"
        fig, ax = plt.subplots(figsize=(4.5, 3))
        fs = 8
    ax.plot(rho, err, color=ink, lw=2.2 if slide else 1.5, label="closed form")
    ax.plot(rho_dp, err_dp, "o", ms=4.5 if slide else 3, mfc="white", mec=ink, label="our solver")
    ax.axhline(0, color=ink, lw=0.8)
    ax.axvline(rho_star, color="gray", ls=":", lw=1.2)
    ax.text(rho_star + 0.08, -36 if slide else 26, rf"$\rho^* = {rho_star:.3f}$", fontsize=fs, color=ink)
    # the two cases of the paper, computed with the solver
    for f2, f3, c, dy in [(0.5, 0.25, under, -14), (0.4, 0.1, over, -22)]:
        p_opt, p_a = exp_solver(f2, f3)
        e = p_a[2] - p_opt[2]
        ax.plot(f2 / f3, e, "o", ms=9 if slide else 5, color=c, mec="white", mew=1.5, zorder=5)
        ax.annotate(rf"$\rho = {f2 / f3:.0f}$: {e:+d} seats", (f2 / f3, e), xytext=(10, dy),
                    textcoords="offset points", fontsize=fs, color=c, fontweight="bold")
    ax.set_xlabel(r"fare ratio $\rho = f_2/f_3$", fontsize=fs + 0.5)
    ax.set_ylabel(r"$p_2^{EMSRa} - p_2^*$ (seats)", fontsize=fs + 0.5)
    ax.set_ylim(-42, 38)
    ax.legend(fontsize=fs - 1, loc="upper left", frameon=False)
    ax.grid(alpha=0.3)
    fig.tight_layout()
    fig.savefig("figures/fig3_counterexample_slide.png" if slide else "figures/fig3_counterexample.png", dpi=250 if slide else 200, facecolor=fig.get_facecolor())


def fig4_vi_vs_pi():
    rows = timing()
    n = [r[0] for r in rows]
    fig, ax = plt.subplots(figsize=(5, 3.5))
    ax.plot(n, [r[1] for r in rows], "o-", label="value iteration")
    ax.plot(n, [r[2] for r in rows], "o-", label="policy iteration")
    ax.set_xlabel("number of fare classes $n$")
    ax.set_ylabel("computing time (ms)")
    ax.legend()
    ax.grid(alpha=0.3)
    fig.tight_layout()
    fig.savefig("figures/fig4_vi_vs_pi.png", dpi=200)


def fig5_all_policies(dark=False, name="fig5_all_policies"):
    """
    Every policy on one graph: gap to the BMG optimum in %. Symlog scale because the gaps go
    from 0.1 % (EMSRa, EMSRb) to 70 % (no control). A bar at 0 means exactly optimal.
    """
    rows = all_policies()
    fg, bg, grid = ("#F7F5F0", "#14202E", "#3A4A5C") if dark else ("black", "white", "#CCCCCC")
    series = [("FCFS", "no control", "#C0504D"),
              ("EMSRa", "EMSRa", "#E0955F"),
              ("EMSRb", "EMSRb", "#7FB5AE"),
              ("LH mixed", "Lee-Hersh, mixed arrivals", "#8FA8CC"),
              ("LH high-low", "Lee-Hersh, expensive first", "#B39DDB")]
    x = np.arange(len(rows))
    w = 0.16
    small = 9 if dark else 6.5            # the dark version goes on a slide: bigger text
    fig, ax = plt.subplots(figsize=(7.2, 4.4), facecolor=bg)
    ax.set_facecolor(bg)
    for j, (key, label, c) in enumerate(series):
        gaps = np.array([r[key] - 100 for r in rows])
        gaps[abs(gaps) < 0.005] = 0                     # exactly optimal
        xs = x + (j - 2) * w
        ax.bar(xs, gaps, w * 0.92, color=c, label=label)
        for xi, g in zip(xs, gaps):
            txt = "0" if g == 0 else (f"{g:+.2f}" if abs(g) < 1 else f"{g:+.1f}")
            y = 0.03 if g >= 0 else -0.03
            if abs(g) > 0.1:
                y = g * 1.2
            ax.text(xi, y, txt, ha="center", va="bottom" if g >= 0 else "top", fontsize=small, color=fg)
    ax.axhline(0, color=fg, lw=1)
    ax.text(len(rows) - 0.52, -0.03, "BMG optimum", color=fg, fontsize=small + 1, ha="right", va="top")
    ax.set_yscale("symlog", linthresh=0.1)
    ax.set_ylim(-150, 25)
    ticks = [-100, -10, -1, -0.1, 0, 0.1, 1, 10]
    ax.set_yticks(ticks)
    ax.set_yticklabels([f"{t:+g} %" if t else "0" for t in ticks])
    ax.set_xticks(x)
    ax.set_xticklabels(fontsize=small + 3, labels=[f"$f$ = {tuple(r['fares'])}\n$f_1/f_3$ = {r['fares'][0] / r['fares'][2]:.1f}" for r in rows])
    ax.set_ylabel("revenue gap to the optimum (symlog)", color=fg, fontsize=small + 2)
    ax.tick_params(axis="y", labelsize=small + 2)
    ax.tick_params(colors=fg)
    for sp in ax.spines.values():
        sp.set_color(grid)
    ax.grid(axis="y", color=grid, alpha=0.5)
    ax.legend(fontsize=small + 1, ncol=3, loc="lower center", bbox_to_anchor=(0.5, 1.0), frameon=False, labelcolor=fg)
    fig.tight_layout()
    fig.savefig(f"figures/{name}.png", dpi=250, facecolor=bg)


if __name__ == "__main__":
    fig1_marginal_values()
    fig2_sensitivity()
    fig3_counterexample()
    fig3_counterexample(slide=True)
    fig4_vi_vs_pi()
    fig5_all_policies()
    print("figures saved in figures/")
