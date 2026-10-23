# Genere une instance "course d'avions" avec des regions geographiquement separees
# Format identique aux instances du sujet (lisible par lecture_distances.jl)
# Usage : python3 generer_instance.py n K Amin graine
#   ex :  python3 generer_instance.py 30 6 10 1   ->  instances/aerodrome_regions_30_1.txt
#   ex :  python generer_instance.py 50 9 15 2    ->  instances/aerodrome_regions_50_1.txt
import sys, os, math, random

n = int(sys.argv[1]) if len(sys.argv) > 1 else 40        # nombre d'aerodromes
K = int(sys.argv[2]) if len(sys.argv) > 2 else 6         # nombre de regions
Amin = int(sys.argv[3]) if len(sys.argv) > 3 else n // 3     # nombre minimum d'aerodromes
graine = int(sys.argv[4]) if len(sys.argv) > 4 else 1
random.seed(graine)

TAILLE = 100        # carte de 100 x 100
ETALEMENT = 6       # rayon d'une region autour de son centre
HORS = 0.15         # proportion d'aerodromes sans region

# centres des regions sur une grille de cases carrees, un peu decales pour ne pas etre trop reguliers
cols = math.ceil(math.sqrt(K))
lignes = math.ceil(K / cols)
pas = TAILLE / cols                 # distance entre deux centres voisins
centres = []
for k in range(K):
    c, l = k % cols, k // cols
    centres.append((pas * (c + 0.5) + random.uniform(-pas / 8, pas / 8), pas * (l + 0.5) + random.uniform(-pas / 8, pas / 8)))

# aerodromes : la plupart autour d'un centre de region, quelques-uns sans region
region, coords = [], []
for i in range(n):
    if i < K:                      # au moins un aerodrome par region
        k = i + 1
    elif random.random() < HORS:
        k = 0
    else:
        k = random.randint(1, K)
    if k == 0:
        x, y = random.uniform(0, TAILLE), random.uniform(0, pas * lignes)
    else:
        cx, cy = centres[k - 1]
        x, y = cx + random.uniform(-ETALEMENT, ETALEMENT), cy + random.uniform(-ETALEMENT, ETALEMENT)
    region.append(k)
    coords.append((round(x), round(y)))

# on melange pour que les numeros ne soient pas tries par region
ordre = list(range(n))
random.shuffle(ordre)
region = [region[i] for i in ordre]
coords = [coords[i] for i in ordre]

# depart et arrivee : deux aerodromes de regions differentes, eloignes
dep = 1 + min(range(n), key=lambda i: coords[i][0] + coords[i][1])       # coin bas gauche
arr = 1 + max(range(n), key=lambda i: coords[i][0] + coords[i][1])       # coin haut droit

# rayon : assez grand pour passer d'une region a sa voisine, mais pas pour traverser la carte
R = round(1.5 * pas)

os.makedirs("instances", exist_ok=True)
nom = f"instances/aerodrome_regions_{n}_{graine}.txt"
with open(nom, "w") as fichier:
    fichier.write(f"{n}\n{dep}\n{arr}\n{Amin}\n{K}\n\n")
    fichier.write(" ".join(map(str, region)) + "\n\n")
    fichier.write(f"{R}\n\n")
    for x, y in coords:
        fichier.write(f"{x} {y}\n")
print(nom, ": n =", n, "K =", K, "Amin =", Amin, "R =", R, "depart =", dep, "arrivee =", arr)