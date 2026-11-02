using JuMP
using Gurobi
include("lecture_distances.jl")
const GRB_ENV = Gurobi.Env()


# contraintes communes aux deux formulations
function modele(n, d, f, Amin, Nr, R, regions, D)
    model = Model(() -> Gurobi.Optimizer(GRB_ENV))
    set_silent(model)
    set_time_limit_sec(model, 600) # 10 minutes max

    @variable(model, x[1:n, 1:n], Bin) # x[i,j] = 1 si on vole de i a j

    # distance totale
    @objective(model, Min, sum(D[i,j]*x[i,j] for i in 1:n, j in 1:n))

    # pas de trajet de i vers i, ni de trajet plus long que R
    @constraint(model, [i = 1:n], x[i,i] == 0)
    @constraint(model, [i = 1:n, j = 1:n; D[i,j] > R], x[i,j] == 0)

    # on part de d et on arrive a f
    @constraint(model, sum(x[d,j] for j in 1:n) == 1)
    @constraint(model, sum(x[i,d] for i in 1:n) == 0)
    @constraint(model, sum(x[i,f] for i in 1:n) == 1)
    @constraint(model, sum(x[f,j] for j in 1:n) == 0)

    # autres aerodromes : autant d'entrees que de sorties, au plus une fois
    @constraint(model, [j = 1:n; j != d && j != f], sum(x[i,j] for i in 1:n) == sum(x[j,l] for l in 1:n))
    @constraint(model, [j = 1:n; j != d && j != f], sum(x[i,j] for i in 1:n) <= 1)

    # au moins Amin aerodromes, donc au moins Amin-1 trajets
    @constraint(model, sum(x) >= Amin - 1)

    # chaque region est visitee : au moins un vol arrive dans la region (sauf la region du depart)
    @constraint(model, [k = 1:Nr; !(d in regions[k])], sum(x[i,j] for i in 1:n, j in regions[k]) >= 1)

    return model, x
end


# formulation 1 : MTZ
function resoudre_mtz(fichier)
    n,d,f,Amin,Nr,R,regions,coords,D = readInstance(fichier)
    model, x = modele(n, d, f, Amin, Nr, R, regions, D)

    @variable(model, 1 <= u[1:n] <= n) # position de l'aerodrome dans le parcours
    @constraint(model, u[d] == 1)
    @constraint(model, [i = 1:n, j = 1:n; i != j], u[j] >= u[i] + 1 - n * (1 - x[i,j]))

    # borne par relaxation continue
    undo = relax_integrality(model)
    optimize!(model)
    borne = objective_value(model)
    undo()

    # branch-and-cut
    optimize!(model)
    valeur = has_values(model) ? objective_value(model) : NaN

    # on reconstruit le parcours en partant de d
    chemin = Int[]
    if has_values(model)
        chemin = [d]
        i = d
        while i != f
            i = findfirst(j -> value(x[i,j]) > 0.5, 1:n)
            push!(chemin, i)
        end
    end
    return n, borne, valeur, solve_time(model), node_count(model), termination_status(model), chemin
end


# formulation 2 : sous-tours ajoutes au fur et a mesure
# (il y a ~2^n contraintes de sous-tours, on ne peut pas toutes les ecrire : on resout sans, et on ajoute seulement celles qui sont violees)
function resoudre_sous_tours(fichier)
    n,d,f,Amin,Nr,R,regions,coords,D = readInstance(fichier)
    model, x = modele(n, d, f, Amin, Nr, R, regions, D)
 
    temps = 0.0
    noeuds = 0
    while true
        # resolution du probleme avec les sous-tours deja interdits
        set_time_limit_sec(model, max(1.0, 600 - temps))   # 10 minutes au total sur toute la boucle
        optimize!(model)
        temps += solve_time(model)
        noeuds += node_count(model)
        if termination_status(model) != MOI.OPTIMAL   # limite de temps atteinte
            return n, NaN, NaN, temps, noeuds, termination_status(model), Int[]
        end
 
        # on lit la solution avant de modifier le modele
        xv = value.(x)
 
        # on marque le chemin d -> f
        vu = falses(n)
        i = d
        vu[i] = true
        while i != f
            i = findfirst(j -> xv[i,j] > 0.5, 1:n)
            vu[i] = true
        end

        # separation : un aerodrome visite hors du chemin est forcement dans un cycle
        nb = 0      # nombre de sous-tours trouves a ce tour
        for s in 1:n
            if !vu[s] && sum(xv[s,j] for j in 1:n) > 0.5
                # on suit le cycle depuis s jusqu'a revenir en s : c'est l'ensemble S
                S = [s]
                vu[s] = true
                j = findfirst(l -> xv[s,l] > 0.5, 1:n)
                while j != s
                    push!(S, j)
                    vu[j] = true
                    j = findfirst(l -> xv[j,l] > 0.5, 1:n)
                end
                # le cycle utilise |S| vols dans S : on en autorise au plus |S| - 1
                @constraint(model, sum(x[a,b] for a in S, b in S) <= length(S) - 1)
                nb += 1
            end
        end

        # aucun sous-tour : la solution est un vrai trajet, donc optimale
        if nb == 0
            break
        end
    end
    valeur = objective_value(model)
    statut = termination_status(model)
 
    # on reconstruit le parcours en partant de d (avant de relaxer le modele)
    chemin = [d]
    i = d
    while i != f
        i = findfirst(j -> value(x[i,j]) > 0.5, 1:n)
        push!(chemin, i)
    end
 
    # borne par relaxation continue du modele final (avec les sous-tours ajoutes)
    relax_integrality(model)
    optimize!(model)
    borne = objective_value(model)
 
    return n, borne, valeur, temps, noeuds, statut, chemin
end


# toutes les instances
println("nom & n & formulation & borne & valeur & temps (s) & noeuds \\\\")
println("\\hline")
for fichier in readdir("instances"; join = true)
    if endswith(fichier, "regions_50_2.txt")
        nom = replace(basename(fichier), ".txt" => "")
        for (formulation, resoudre) in [("MTZ", resoudre_mtz), ("Sous-tours", resoudre_sous_tours)]
            n, borne, valeur, temps, noeuds, statut, chemin = resoudre(fichier)
            ligne = string(nom, " & ", n, " & ", formulation, " & ", round(borne, digits=1), " & ", valeur, " & ", round(temps, digits=2), " & ", noeuds, " \\\\   % ", statut) # pour le tableau LaTeX
            println(ligne)
            println("% parcours : ", join(chemin, " -> "))
            open("tableau.txt", "a") do io
                println(io, ligne)
            end
            open("parcours.txt", "a") do io
                println(io, nom, " ", formulation, " ", join(chemin, " "))
            end
        end
    end
end
