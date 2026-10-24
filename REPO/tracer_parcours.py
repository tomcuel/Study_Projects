# Trace les parcours trouves par course_avions.jl
# Usage : python3 tracer_parcours.py
#   lit parcours.txt (une ligne par parcours : nom formulation a1 a2 ... ak) et instances/<nom>.txt, ecrit cartes/<nom>_<formulation>.png
import os, math
import matplotlib.pyplot as plt

def couleurs_regions(nr):
    ordre = [k for k in list(range(0, 20, 2)) + list(range(1, 20, 2)) if k not in (14, 15)]
    if nr <= len(ordre):
        palette = plt.get_cmap("tab20")
        return [palette(ordre[k]) for k in range(nr)]
    palette = plt.get_cmap("turbo")
    return [palette(k / (nr - 1)) for k in range(nr)]
GRIS = "#b4b2a9"       # aerodromes sans region
TEXTE = "#52514e"


def lire_instance(fichier):
    # meme format que lecture_distances.jl : on lit tous les nombres dans l'ordre
    v = [int(t) for t in open(fichier).read().split()]
    n, dep, arr, amin, nr = v[:5]
    region = v[5:5 + n]
    rayon = v[5 + n]
    c = v[6 + n:6 + 3 * n]
    coords = [(c[2 * i], c[2 * i + 1]) for i in range(n)]
    return n, dep, arr, amin, nr, region, rayon, coords


def distance(a, b):
    return math.floor(math.hypot(a[0] - b[0], a[1] - b[1]))


os.makedirs("cartes", exist_ok=True)
for ligne in open("parcours.txt"):
    mots = ligne.split()
    if len(mots) < 3:          # pas de parcours (limite de temps)
        continue
    nom, formulation = mots[0], mots[1]
    chemin = [int(t) for t in mots[2:]]          # numeros 1..n
    n, dep, arr, amin, nr, region, rayon, coords = lire_instance(f"instances/{nom}.txt")

    fig, ax = plt.subplots(figsize=(7, 6))

    # vols possibles (distance <= rayon) en pointilles
    for i in range(n):
        for j in range(i + 1, n):
            if distance(coords[i], coords[j]) <= rayon:
                ax.plot([coords[i][0], coords[j][0]], [coords[i][1], coords[j][1]], color=GRIS, linewidth=0.5, linestyle=":", zorder=0)

    # aerodromes sans region
    hors = [coords[i] for i in range(n) if region[i] == 0]
    if hors:
        ax.scatter(*zip(*hors), s=50, color=GRIS, zorder=1, label="sans région")

    # aerodromes de chaque region : couleur + numero au centre
    couleurs = couleurs_regions(nr)
    for k in range(1, nr + 1):
        pts = [coords[i] for i in range(n) if region[i] == k]
        if not pts:
            continue
        ax.scatter(*zip(*pts), s=70, color=couleurs[k - 1], edgecolors="white", linewidths=0.8, zorder=2, label=f"R{k}")

    if n <= 20:   # petites instances : numero de chaque aerodrome
        for i, (x, y) in enumerate(coords):
            ax.annotate(str(i + 1), (x, y), xytext=(5, -10), textcoords="offset points", fontsize=8, color=TEXTE)

    # trajet
    px = [coords[i - 1][0] for i in chemin]
    py = [coords[i - 1][1] for i in chemin]
    ax.plot([], [], color=GRIS, linewidth=0.8, linestyle=":", label="vols possibles")
    ax.plot(px, py, color="black", linewidth=2, zorder=3, label="trajet")
    ax.scatter(*coords[dep - 1], marker="^", s=220, color="black", edgecolors="white", zorder=5, label="départ")
    ax.scatter(*coords[arr - 1], marker="s", s=170, color="black", edgecolors="white", zorder=5, label="arrivée")

    total = sum(distance(coords[chemin[t] - 1], coords[chemin[t + 1] - 1]) for t in range(len(chemin) - 1))
    ax.set_title(f"{nom} ({formulation}) : {len(chemin)} aérodromes, distance {total}", fontsize=11)
    ax.set_aspect("equal")
    ax.legend(loc="center left", bbox_to_anchor=(1.02, 0.5), fontsize=8, frameon=False)
    for cote in ["top", "right"]:
        ax.spines[cote].set_visible(False)

    fig.tight_layout()
    fig.savefig(f"cartes/{nom}_{formulation}.png", dpi=200, bbox_inches="tight")
    plt.close(fig)
    print(nom, formulation, ": carte écrite, distance =", total)