####################################
####################################
## STA203 - Projet - CUEL CHRETIENNE
####################################
####################################



####################################
####################################
## Introduction
####################################
####################################
## Charger les libraries nécessaires (ou vues en cours)
rm(list=objects());
graphics.off()
library(openxlsx)
library(ggplot2)
library(patchwork)
library(cowplot)
library(corrplot)
library(FactoMineR)
library(factoextra)
library(GGally)
library(reshape2)
library(car)
library(cluster)
library(mclust)
library(Rmixmod)
library(alluvial)
library(ROCR)
library(MASS)
library(zoo)
library(forecast)
library(glmnet)
library(leaps)
library(ggrepel)
library(e1071)
library(randomForest)
library(nnet)
# library(xgboost)

## Charger les données
df <- read.xlsx("Raisin.xlsx", sheet = 1)
save(df, file = "Raisin.RData")
rm(df)
load("Raisin.RData")



####################################
####################################
## Partie I : Analyse non supervisée
####################################
####################################
##################
## 1 : Analyses préliminaires des données 
##################
directory <- "Preliminary_Analysis"
dir.create(directory, showWarnings = FALSE)

## Analyse univariée
dim(df)
# 900   8
head(df)
# Area MajorAxisLength MinorAxisLength Eccentricity ConvexArea    Extent Perimeter   Class
# 1 87524        442.2460        253.2912    0.8197384      90546 0.7586506  1184.040 Kecimen
# 2 75166        406.6907        243.0324    0.8018052      78789 0.6841296  1121.786 Kecimen
# 3 90856        442.2670        266.3283    0.7983536      93717 0.6376128  1208.575 Kecimen
# 4 45928        286.5406        208.7600    0.6849892      47336 0.6995994   844.162 Kecimen
# 5 79408        352.1908        290.8275    0.5640113      81463 0.7927719  1073.251 Kecimen
# 6 49242        318.1254        200.1221    0.7773513      51368 0.6584564   881.836 Kecimen
summary(df)
# Area        MajorAxisLength MinorAxisLength  Eccentricity      ConvexArea         Extent         Perimeter         Class          
# Min.   : 25387   Min.   :225.6   Min.   :143.7   Min.   :0.3487   Min.   : 26139   Min.   :0.3799   Min.   : 619.1   Length:900        
# 1st Qu.: 59348   1st Qu.:345.4   1st Qu.:219.1   1st Qu.:0.7418   1st Qu.: 61513   1st Qu.:0.6709   1st Qu.: 966.4   Class :character  
# Median : 78902   Median :407.8   Median :247.8   Median :0.7988   Median : 81651   Median :0.7074   Median :1119.5   Mode  :character  
# Mean   : 87804   Mean   :430.9   Mean   :254.5   Mean   :0.7815   Mean   : 91186   Mean   :0.6995   Mean   :1165.9                     
# 3rd Qu.:105028   3rd Qu.:494.2   3rd Qu.:279.9   3rd Qu.:0.8426   3rd Qu.:108376   3rd Qu.:0.7350   3rd Qu.:1308.4                     
# Max.   :235047   Max.   :997.3   Max.   :492.3   Max.   :0.9621   Max.   :278217   Max.   :0.8355   Max.   :2697.8 
str(df)
# 'data.frame':	900 obs. of  8 variables:
# $ Area           : num  87524 75166 90856 45928 79408 ...
# $ MajorAxisLength: num  442 407 442 287 352 ...
# $ MinorAxisLength: num  253 243 266 209 291 ...
# $ Eccentricity   : num  0.82 0.802 0.798 0.685 0.564 ...
# $ ConvexArea     : num  90546 78789 93717 47336 81463 ...
# $ Extent         : num  0.759 0.684 0.638 0.7 0.793 ...
# $ Perimeter      : num  1184 1122 1209 844 1073 ...
# $ Class          : chr  "Kecimen" "Kecimen" "Kecimen" "Kecimen" ...
summary(as.factor(df$Class))
# Besni Kecimen 
#   450     450
n <- nrow(df)
p <- ncol(df)

# vérification des valeurs manquantes
cat("nombre de NA :", sum(is.na(df)), "\n")
colSums(is.na(df)) # NA par variable
# Area MajorAxisLength MinorAxisLength    Eccentricity      ConvexArea          Extent       Perimeter           Class 
# 0               0               0               0               0               0               0               0 

## Analyse bivariée/multivariée
cor_matrix <- cor(df[,-p])
round(cor_matrix,2)
# Area MajorAxisLength MinorAxisLength Eccentricity ConvexArea Extent Perimeter
# Area             1.00            0.93            0.91         0.34       1.00  -0.01      0.96
# MajorAxisLength  0.93            1.00            0.73         0.58       0.95  -0.20      0.98
# MinorAxisLength  0.91            0.73            1.00        -0.03       0.90   0.15      0.83
# Eccentricity     0.34            0.58           -0.03         1.00       0.35  -0.36      0.45
# ConvexArea       1.00            0.95            0.90         0.35       1.00  -0.05      0.98
# Extent          -0.01           -0.20            0.15        -0.36      -0.05   1.00     -0.17
# Perimeter        0.96            0.98            0.83         0.45       0.98  -0.17      1.00

# Matrice de corrélations
corrplot(cor_matrix, method = "circle", 
        addCoef.col = "black", tl.col = "black", tl.srt = 45,
        number.cex = 0.7, col = colorRampPalette(c("red", "white", "blue"))(200))
png(file.path(directory, "corrplot_matrix.png"), width = 1000, height = 1000, res = 150)
corrplot(cor_matrix, method = "circle", 
        addCoef.col = "black", tl.col = "black", tl.srt = 45,
        number.cex = 0.7, col = colorRampPalette(c("red", "white", "blue"))(200))
dev.off()

# Matrice de scatterplots
plot_pairs <- ggpairs(
    df,
    columns = 1:(p-1),  # exclure la variable Class
    aes(colour = as.factor(Class), alpha = 0.6),
    upper = list(continuous = wrap("cor", size = 3)),
    lower = list(continuous = wrap("points", size = 0.8)),
    diag = list(continuous = wrap("densityDiag", alpha = 0.5)),
    title = "Matrice de scatterplots colorée par classe"
) + theme_minimal(base_size = 12) + theme(
    plot.title = element_text(hjust = 0.5, face = "bold"),
    strip.text = element_text(size = 10),
    axis.text.x = element_text(size = 6),  # taille texte abscisses
    axis.text.y = element_text(size = 6),  # taille texte ordonnées
    legend.position = "bottom"
)
plot_pairs
ggsave(file.path(directory, "scatterplot_matrix.png"), plot_pairs, width = 12, height = 10)

scatterplotMatrix(df[,-p], smooth = FALSE,
                  groups = df$Class, col = c("tomato", "skyblue", "seagreen"), 
                  main = "Scatterplot Matrix par classe")
png(file.path(directory, "scatterplot_matrix_car.png"), width = 1800, height = 1500, res = 200)
scatterplotMatrix(df[,-p], smooth = FALSE,
                  groups = df$Class, col = c("tomato", "skyblue", "seagreen"), 
                  main = "Scatterplot Matrix par classe")
dev.off()

# Variance de chaque variable
round(apply(df[,-p], 2, var), 2) 
# Area            MajorAxisLength MinorAxisLength Eccentricity    ConvexArea      Extent          Perimeter 
# 1.521165e+09    1.346415e+04    2.498890e+03    1.000000e-02    1.662135e+09    0.000000e+00    7.494690e+04

# Boxplots globaux pour chaque variable
data_mod <- melt(df, id.vars = "Class", measure.vars = 1:(p-1))
plot <- ggplot(data_mod, aes(y = value)) +
  geom_boxplot(fill = "skyblue", color = "black") +
  facet_wrap(~ variable, scales = "free", ncol = 3) +
  theme_minimal() +
  labs(title = "Boxplots des variables", y = "Valeur", x = "") +
  theme(strip.text = element_text(face = "bold"))
plot
ggsave(file.path(directory, "boxplots.pdf"), plot, width = 6, height = 5)

# Boxplots par classe
plot <- ggplot(data_mod, aes(x = Class, y = value, fill = Class)) +
  geom_boxplot() +
  facet_wrap(~ variable, scales = "free", ncol = 3) +
  theme_minimal() +
  labs(title = "Boxplots des variables par classe", y = "Valeur") +
  theme(legend.position = "none")
plot
ggsave(file.path(directory, "boxplots_by_class.pdf"), plot, width = 6, height = 5)


##################
## 2 : Méthododologie ACP
##################
directory <- "PCA"
dir.create(directory, showWarnings = FALSE)

# Lancement de l'ACP avec centrage et réduction automatique
res_pca <- PCA(df[,-p], scale.unit = TRUE, ncp = p - 1, graph = FALSE)
# Valeurs propres (valprop) et vecteurs propres (vecprop)
valprop <- res_pca$eig[, 1]
valprop
# comp 1      comp 2      comp 3      comp 4      comp 5      comp 6      comp 7 
# 4.832288611 1.453188439 0.628449468 0.056824512 0.021808269 0.006430191 0.001010510 
vecprop <- res_pca$var$coord
vecprop
#                  Dim.1      Dim.2       Dim.3        Dim.4       Dim.5        Dim.6        Dim.7
# Area             0.9854393  0.13995643 -0.004347259  0.02649321 -0.090237212 -0.008005567 -1.984770e-02
# MajorAxisLength  0.9743504 -0.16465355  0.079709211 -0.11804635  0.012932055 -0.054975382  7.239155e-03
# MinorAxisLength  0.8559559  0.45196252 -0.187123054  0.15634718  0.056792992 -0.019167708  4.131008e-03
# Eccentricity     0.4461803 -0.73633679  0.498259634  0.10162061  0.011091094  0.004294906  6.498855e-04
# ConvexArea       0.9912737  0.10561996 -0.029071976 -0.01330433 -0.057949740  0.037784892  2.031735e-02
# Extent          -0.1239116  0.80447208  0.580276454 -0.02599583  0.008396698  0.001880579 -5.138263e-05
# Perimeter        0.9910218 -0.04119408 -0.035119346 -0.08101668  0.081982577  0.039073361 -1.157101e-02

# Inertie
res_pca$eig[, 2]
# comp 1      comp 2      comp 3      comp 4      comp 5      comp 6      comp 7 
# 69.03269444 20.75983485  8.97784954  0.81177875  0.31154669  0.09185987  0.01443585 
# Inertie cumulée
res_pca$eig[, 3]
# comp 1    comp 2    comp 3    comp 4    comp 5    comp 6   comp 7
# 69.03269  89.79253  98.77038  99.58216  99.89370  99.98556 100.00000
# Visualisation de l'inertie (en %)
inertie_moyenne <- 100 / nrow(res_pca$eig)
fviz_eig(res_pca, addlabels = TRUE, barfill = "#1F77B4", barcolor = "black", linecolor = "darkred",     
         main = "Eboulis des valeurs propres", xlab = "Axes principaux", ylab = "Pourcentage d'inertie (%)") +
  geom_hline(yintercept = inertie_moyenne, linetype = "dashed", color = "red") +
  annotate("text", x = 1.5, y = inertie_moyenne + 1.5, 
           label = paste0("Inertie moyenne (", round(inertie_moyenne, 1), "%)"), 
           color = "red", size = 3.5, hjust = 0) +
  theme_minimal(base_size = 13) +
  theme(plot.title = element_text(hjust = 0.5, face = "bold"),axis.text.x = element_text(angle = 45, hjust = 1)
)
ggsave(file.path(directory, "inertie.pdf"), width = 6, height = 5)
# Règle du coude, seulement les 3 premiers axes sont significatifs et importants pour l'analyse PCA suivante

# Coordonnées des individus
head(res_pca$ind$coord)
#    Dim.1       Dim.2      Dim.3      Dim.4       Dim.5      Dim.6       Dim.7
# 1  0.07699386  0.4533281  1.0892142 -0.02678873  0.1413865  0.01305772 -0.003707640
# 2 -0.47537590 -0.4453684 -0.0163725  0.11594460  0.1219955  0.01380902 -0.005672104
# 3  0.37210892 -0.8020081 -0.7864871  0.26496260  0.0621901 -0.04341853 -0.007208510
# 4 -2.62244499  0.3025636 -0.4827210 -0.09959682 -0.1153308  0.04228420 -0.013386525
# 5 -0.96205385  2.9677630 -0.4521543 -0.29988296  0.1757713 -0.05246846 -0.006949173
# 6 -2.17316315 -0.9244119 -0.3451824  0.12941432 -0.1392421  0.03887126  0.008374202
# Projection des individus sur les deux premiers axes
ind12 <- fviz_pca_ind(res_pca,
             geom.ind = "point",
             col.ind = as.factor(df$Class),
             palette = "Dark2",
             addEllipses = TRUE,
             legend.title = "Classe",
             repel = TRUE,
             title = "Projection des individus (Dim 1 et 2)")
ind12
ggsave(file.path(directory, "ind12.pdf"), ind12, width = 6, height = 5)
# Projection des individus sur les axes 2 et 3
ind23 <- fviz_pca_ind(res_pca,
             axes = c(2, 3),
             geom.ind = "point",
             col.ind = as.factor(df$Class),
             palette = "Dark2",
             addEllipses = TRUE,
             legend.title = "Classe",
             repel = TRUE,
             title = "Projection des individus (Dim 2 et 3)")
ind23
ggsave(file.path(directory, "ind23.pdf"), ind23, width = 6, height = 5)

# Coordonnées des variables
head(res_pca$var$coord)
#                  Dim.1      Dim.2      Dim.3        Dim.4       Dim.5        Dim.6        Dim.7
# Area             0.9854393  0.1399564 -0.004347259  0.02649321 -0.090237212 -0.008005567 -1.984770e-02
# MajorAxisLength  0.9743504 -0.1646536  0.079709211 -0.11804635  0.012932055 -0.054975382  7.239155e-03
# MinorAxisLength  0.8559559  0.4519625 -0.187123054  0.15634718  0.056792992 -0.019167708  4.131008e-03
# Eccentricity     0.4461803 -0.7363368  0.498259634  0.10162061  0.011091094  0.004294906  6.498855e-04
# ConvexArea       0.9912737  0.1056200 -0.029071976 -0.01330433 -0.057949740  0.037784892  2.031735e-02
# Extent          -0.1239116  0.8044721  0.580276454 -0.02599583  0.008396698  0.001880579 -5.138263e-05
# Cercle des corrélations (axes 1 et 2) avec mise en évidence de la représentation des variables (cos2)
var12 <- fviz_pca_var(res_pca,
             col.var = "cos2", 
             gradient.cols = c("#00AFBB", "#E7B800", "#FC4E07"),
             repel = TRUE,
             title = "Cercle des corrélations (Dim 1 et 2)")
var12
ggsave(file.path(directory, "var12.pdf"), var12, width = 6, height = 5)
# Cercle des corrélations (axes 2 et 3)
var23 <- fviz_pca_var(res_pca,
             axes = c(2,3),
             col.var = "cos2",
             gradient.cols = c("#00AFBB", "#E7B800", "#FC4E07"),
             repel = TRUE,
             title = "Cercle des corrélations (Dim 2 et 3)")
var23
ggsave(file.path(directory, "var23.pdf"), var23, width = 6, height = 5)

# Affichage côte à côte (2 graphiques), assigné à des variables
cow_plots_12 <- plot_grid(ind12, var12, ncol = 2, align = "h")
cow_plots_23 <- plot_grid(ind23, var23, ncol = 2, align = "h")
cow_plots_ind <- plot_grid(ind12, ind23, ncol = 2, align = "h")
cow_plots_var <- plot_grid(var12, var23, ncol = 2, align = "h")
# Affichage en 2x2 (4 graphiques)
cow_plots_12_23 <- plot_grid(ind12, ind23, var12, var23, ncol = 2, align = "hv")
cow_plots_12
ggsave(file.path(directory, "cow_plots_12.pdf"), cow_plots_12, width = 12, height = 10)
cow_plots_23
ggsave(file.path(directory, "cow_plots_23.pdf"), cow_plots_23, width = 12, height = 10)
cow_plots_ind
ggsave(file.path(directory, "cow_plots_ind.pdf"), cow_plots_ind, width = 12, height = 10)
cow_plots_var
ggsave(file.path(directory, "cow_plots_var.pdf"), cow_plots_var, width = 12, height = 10)
cow_plots_12_23
ggsave(file.path(directory, "cow_plots_12_23.pdf"), cow_plots_12_23, width = 12, height = 10)

# Contribution aux axes
round(res_pca$var$contrib, 5)
#                  Dim.1    Dim.2    Dim.3    Dim.4    Dim.5    Dim.6    Dim.7
# Area            20.09587  1.34792  0.00301  1.23519 37.33792  0.99669 38.98340
# MajorAxisLength 19.64615  1.86561  1.01099 24.52276  0.76686 47.00160  5.18603
# MinorAxisLength 15.16177 14.05668  5.57166 43.01742 14.79000  5.71369  1.68877
# Eccentricity     4.11972 37.31050 39.50400 18.17305  0.56406  0.28687  0.04180
# ConvexArea      20.33454  0.76766  0.13449  0.31149 15.39862 22.20304 40.85016
# Extent           0.31774 44.53485 53.57961  1.18925  0.32329  0.05500  0.00026
# Perimeter       20.32420  0.11677  0.19626 11.55083 30.81924 23.74311 13.24958

# Qualité de la représentation des variables
round(res_pca$var$cos2, 5)
#                 Dim.1   Dim.2   Dim.3   Dim.4   Dim.5   Dim.6   Dim.7
# Area            0.97109 0.01959 0.00002 0.00070 0.00814 0.00006 0.00039
# MajorAxisLength 0.94936 0.02711 0.00635 0.01393 0.00017 0.00302 0.00005
# MinorAxisLength 0.73266 0.20427 0.03502 0.02444 0.00323 0.00037 0.00002
# Eccentricity    0.19908 0.54219 0.24826 0.01033 0.00012 0.00002 0.00000
# ConvexArea      0.98262 0.01116 0.00085 0.00018 0.00336 0.00143 0.00041
# Extent          0.01535 0.64718 0.33672 0.00068 0.00007 0.00000 0.00000
# Perimeter       0.98212 0.00170 0.00123 0.00656 0.00672 0.00153 0.00013

# Interprétation : 
# Individu le plus contributif sur chaque axe : 
apply(res_pca$ind$contrib,2,which.max)
# Dim.1 Dim.2 Dim.3 Dim.4 Dim.5 Dim.6 Dim.7 
# 488   507    24   507   291   488   488
# Les plus contributifs de l'axe 1 : 
round(head(sort(res_pca$ind$contrib[, 1],decreasing=TRUE)),5)
# 488     837     507     813      86     695 
# 2.09013 1.28753 1.27470 1.16977 1.12550 1.12439 
# Les plus contributifs de l'axe 2 : 
round(head(sort(res_pca$ind$contrib[, 2],decreasing=TRUE)),5)
# 507     837     881     803     537     198 
# 2.17312 1.62564 1.52478 1.27343 1.27295 1.22146
# Les plus contributifs de l'axe 3 : 
round(head(sort(res_pca$ind$contrib[, 3],decreasing=TRUE)),5)
# 24      35     507     837     881      86 
# 2.07854 1.64431 1.61999 1.37464 1.32147 1.23491

# Moyennes
moy_cos2 <- apply(res_pca$ind$cos2, 2, mean)
round(moy_cos2,5)
# Dim.1   Dim.2   Dim.3   Dim.4   Dim.5   Dim.6   Dim.7 
# 0.56775 0.26374 0.14732 0.01223 0.00692 0.00176 0.00029
moy_contrib <- apply(res_pca$ind$contrib, 2, mean)
# Dim.1   Dim.2   Dim.3   Dim.4   Dim.5   Dim.6   Dim.7 
# 0.11111 0.11111 0.11111 0.11111 0.11111 0.11111 0.11111
round(moy_contrib,5)

# Individus avec cos2 < moyenne et contribution > moyenne (par axe)
ind_p1 <- sapply(1:3, function(i) {
  head(which(res_pca$ind$cos2[,i] < moy_cos2[i] & res_pca$ind$contrib[,i] > moy_contrib[i]))
})
colnames(ind_p1) <- paste0("Dim.", 1:3)
ind_p1
#     Dim.1 Dim.2 Dim.3
# 35     35     7     9
# 107   107    24    14
# 114   114    35    36
# 128   128    36    37
# 157   157    51    86
# 193   193    86   103

# Individus avec cos2 > moyenne et contribution < moyenne (par axe)
ind_p2 <- sapply(1:3, function(i) {
  head(which(res_pca$ind$cos2[,i] > moy_cos2[i] & res_pca$ind$contrib[,i] < moy_contrib[i]))
})
colnames(ind_p2) <- paste0("Dim.", 1:3)
ind_p2
#    Dim.1 Dim.2 Dim.3
# 6      6     2     3
# 8      8     3    15
# 10    10    11    23
# 15    15    21    30
# 18    18    26    31
# 21    21    31    39

# Identifiants des individus contributifs
axe1_contrib <- c(488, 837, 507, 813, 86, 695)
axe2_contrib <- c(507, 837, 881, 803, 537, 198)
axe3_contrib <- c(24, 35, 507, 837, 881, 86)

# Création d'un vecteur de tailles (par défaut taille moyenne = 2)
point_size <- rep(2, nrow(df))
point_size[axe1_contrib] <- 4  # Plus gros pour Axe 1
point_size[setdiff(axe2_contrib, axe1_contrib)] <- 2.5  # Taille moyenne pour Axe 2
point_size[setdiff(axe3_contrib, union(axe1_contrib, axe2_contrib))] <- 1.5  # Plus petit pour Axe 3 seul
# Data frame avec coordonnées et taille
coord_df <- as.data.frame(res_pca$ind$coord)
coord_df$Class <- as.factor(df$Class)
coord_df$Size <- point_size
label_df <- rbind(
  data.frame(coord_df[axe1_contrib, ], Label = as.character(axe1_contrib), Axe = "Axe 1"),
  data.frame(coord_df[axe2_contrib, ], Label = as.character(axe2_contrib), Axe = "Axe 2"),
  data.frame(coord_df[axe3_contrib, ], Label = as.character(axe3_contrib), Axe = "Axe 3")
)
# Création du graphique
ind123 <- ggplot(coord_df, aes(x = Dim.1, y = Dim.2)) +
  # Points non contributifs (colorés par classe)
  geom_point(data = coord_df[-union(union(axe1_contrib, axe2_contrib), axe3_contrib), ], aes(color = Class, size = Size), alpha = 0.7) +
  # Points contributifs (en noir) si apparition dans plusieurs axes
  geom_point(data = coord_df[union(union(axe1_contrib, axe2_contrib), axe3_contrib), ], aes(size = Size), color = "black", alpha = 0.9) +
  # Textes duplicata selon l'axe
  geom_text_repel(data = label_df, aes(label = Label, color = Axe), size = 3, show.legend = TRUE) +
    stat_ellipse(data = coord_df, aes(x = Dim.1, y = Dim.2, group = Class, color = Class), linetype = "dashed") +
    scale_size_identity() +
    scale_color_manual(values = c("Axe 1" = "red", "Axe 2" = "blue", "Axe 3" = "darkgreen", RColorBrewer::brewer.pal(8, "Dark2")), name = "Classe ou axe") + 
    theme_minimal(base_size = 12) + labs(title = "Projection des individus (Dim 1 et 2)", size = "Taille", color = "Classe ou axe")
ind123
ggsave(file.path(directory, "ind123_contrib.pdf"), ind123, width = 6, height = 5)


##################
## 3 : Classification hiérarchique ascendante
##################
directory <- "Agglomerative_Hierarchical_Clustering"
dir.create(directory, showWarnings = FALSE)

# Distance et classification hiérarchique
dist_mat <- dist(df[,-p], method = "euclidean")
CHA <- hclust(dist_mat)

# Barplot des 20 plus grandes hauteurs (sauts)
barplot(rev(CHA$height)[1:20], main = "Diagramme des hauteurs")
pdf(file.path(directory, "barplot_height.pdf"), width = 6, height = 5)
barplot(rev(CHA$height)[1:20], main = "Diagramme des hauteurs")
dev.off()

# Essai automatique pour k = 2 à 10 : on maximise l'indice de silhouette
silhouettes <- sapply(2:10, function(k) {
  cluster_temp <- cutree(CHA, k = k)
  sil_temp <- silhouette(cluster_temp, dist_mat)
  mean(sil_temp[, 3])
})

# Meilleur k selon la silhouette
best_k <- which.max(silhouettes) + 1  # +1 car index commence à 2
cat("Nombre optimal de groupes (max silhouette) :", best_k, "\n") # on a bien 2 car deux groupes de raisins 

# Visualisation de la courbe silhouette
plot(2:10, silhouettes, type = "b", pch = 19, col = "blue",
     xlab = "Nombre de groupes", ylab = "Indice moyen de silhouette",
     main = "Choix optimal du nombre de clusters")
pdf(file.path(directory, "silhouette_curve.pdf"), width = 6, height = 5)
plot(2:10, silhouettes, type = "b", pch = 19, col = "blue",
     xlab = "Nombre de groupes", ylab = "Indice moyen de silhouette",
     main = "Choix optimal du nombre de clusters")
dev.off()

# Appliquer la classification avec le bon k
final_clustering <- cutree(CHA, k = best_k)
# Dendrogramme + groupes retenus
plot(CHA, main = paste("Dendrogramme (k =", best_k, ")"), xlab = "", sub = "", cex = 0.6)
rect.hclust(CHA, k = best_k, border = 2:(best_k + 1))
pdf(file.path(directory, "dendrogram.pdf"), width = 6, height = 5)
plot(CHA, main = paste("Dendrogramme (k =", best_k, ")"), xlab = "", sub = "", cex = 0.6)
rect.hclust(CHA, k = best_k, border = 2:(best_k + 1))
dev.off()

# Silhouette finale
final_sil <- silhouette(final_clustering, dist_mat)
fviz_silhouette(final_sil) + ggtitle(paste("Diagramme de silhouette - CAH (k =", best_k, ")"))
ggsave(file.path(directory, "silhouette_final.pdf"), width = 6, height = 5)
# cluster size ave.sil.width
# 1       1  813          0.64
# 2       2   87          0.74
# Moyenne de l'indice de silhouette
mean_sil <- mean(final_sil[, 3])
cat("Indice moyen de silhouette :", round(mean_sil, 3), "\n") # 0.651

# Erreur de classification 
tab <- table(Vraie_Class = df$Class, Pred_Class = final_clustering)
tab 
#            Pred_Class
# Vraie_Class   1   2
#     Besni   365  85
#     Kecimen 448   2
cat("Erreur de classification :", 1 - sum(diag(tab)) / sum(tab), "\n") # 0.5922

## Après normalisation
df_scaled <- scale(df[, -p], center = TRUE, scale = TRUE)/sqrt((n-1)/n)
apply(df_scaled^2, 2, mean) # pour vérifier que les variances sont bien normées
dist_norm <- dist(df_scaled, method = "euclidean")
CHA_norm <- hclust(dist_norm)
cl_norm <- cutree(CHA_norm, k = best_k)
err_norm <- 1 - sum(diag(table(cl_norm, df[,p]))) / nrow(df)
cat("Erreur avec normalisation :", round(err_norm,3), "\n") # 0.627


##################
## 4 : Clustering hiérarchique sur les composantes principales
##################
max_k <- 7
errors <- numeric(max_k)
# Pour chaque k = 1 à 7
for (k in 1:max_k){
    pcs <- res_pca$ind$coord[, 1:k]   # coordonnées des individus sur les k axes
    dist_k <- dist(pcs)               # distance euclidienne
    cah_k <- hclust(dist_k)           # classification hiérarchique
    clust_k <- cutree(cah_k, k = 2)   # on connaît 2 vraies classes
    tab <- table(clust_k, df[, p])
    errors[k] <- 1 - sum(diag(tab)) / sum(tab)
}

# Affichage du résultat
plot(1:max_k, errors, type = "b", pch = 19, col = "darkred",
     xlab = "Nombre de composantes principales", ylab = "Erreur de classification", main = "Erreur vs nombre de composantes principales")
pdf(file.path(directory, "error_vs_k.pdf"), width = 6, height = 5)
plot(1:max_k, errors, type = "b", pch = 19, col = "darkred",
     xlab = "Nombre de composantes principales", ylab = "Erreur de classification", main = "Erreur vs nombre de composantes principales")
dev.off()
# Meilleur k
best_k <- which.min(errors)
cat("Meilleur nombre de composantes :", best_k, "avec erreur =", round(errors[best_k], 3), "\n") # 4 avec 0.584


####################################
####################################
## Partie II : Choix d'un modèle
####################################
####################################
directory <- "Model_Choice"
dir.create(directory, showWarnings = FALSE)
##################
## 1 : Modèle logistique et discussions
##################
# cf Rapport LaTeX pour l'écriture du modèle
# Centrer et réduire les variables explicatives est recommandé en pratique, surtout quand :
# - les variables sont de nature hétérogène (aire, périmètre, densité, etc.)
# - on souhaite comparer l'importance relative des variables
# - on utilise des méthodes à pénalisation ou sélection automatique de variables (gmmnet, lasso, ridge, etc.)


##################
## 2 : Échantillon d'apprentissage
##################
## définition de l'échantillon d'apprentissage
set.seed(1)
train = sample(c(TRUE,FALSE),n,rep=TRUE,prob=c(2/3,1/3))
df_app <- df[train, ]
df_test <- df[!train, ]

## détermination des projections des observations du jeu d'apprentissage et du jeu de test 
#sur le premier plan principal par PCA
res_pca_app <- PCA(df_app[,-p], scale.unit=TRUE, ncp =p-1, graph=FALSE)
res_pca_test <- PCA(df_test[,-p], scale.unit=TRUE, ncp =p-1, graph=FALSE)
# projection des individus du test sur les axes de l'ACP d'apprentissage
projection_test <- predict(res_pca_app, newdata = df_test[,-p])
round(head(projection_test$coord),5)
#     Dim.1    Dim.2    Dim.3    Dim.4    Dim.5    Dim.6    Dim.7
# 4  -2.56019  0.33745 -0.46242 -0.10946 -0.11030  0.03930 -0.01265
# 6  -2.11945 -0.86949 -0.31247  0.12864 -0.13192  0.03748  0.01061
# 7  -2.49335 -1.28415  0.22614  0.10473 -0.21466  0.05943  0.01230
# 13 -2.76243  0.19110 -0.55342 -0.09759 -0.20131  0.03592  0.01010
# 15 -0.63880 -0.17096 -0.30356  0.16265  0.07575 -0.00557 -0.00264
# 17 -1.09272 -0.21082  1.56299 -0.15020  0.05972  0.00005  0.00234
round(head(projection_test$cos2),5)
#    Dim.1   Dim.2   Dim.3   Dim.4   Dim.5   Dim.6   Dim.7
# 4  0.94882 0.01648 0.03095 0.00173 0.00176 0.00022 2e-05
# 6  0.83477 0.14049 0.01814 0.00308 0.00323 0.00026 2e-05
# 7  0.77927 0.20671 0.00641 0.00137 0.00578 0.00044 2e-05
# 13 0.95088 0.00455 0.03816 0.00119 0.00505 0.00016 1e-05
# 15 0.72652 0.05204 0.16406 0.04710 0.01022 0.00006 1e-05
# 17 0.32205 0.01199 0.65891 0.00608 0.00096 0.00000 0e+00
round(head(projection_test$dist),5)
# 4       6       7       13      15      17 
# 2.62834 2.31974 2.82448 2.83289 0.74945 1.92550 

# Graphiques 
inertie_dim1 <- round(res_pca_app$eig[1, 2], 1)
inertie_dim2 <- round(res_pca_app$eig[2, 2], 1)
xlabel <- paste0("Composante principale 1 (", inertie_dim1, " %)")
ylabel <- paste0("Composante principale 2 (", inertie_dim2, " %)")
coord_app <- as.data.frame(res_pca_app$ind$coord[, 1:2])
coord_app$Set <- "Apprentissage"
coord_test <- as.data.frame(projection_test$coord[, 1:2])
coord_test$Set <- "Test"
coord_total <- rbind(coord_app, coord_test)
plot <- ggplot(coord_total, aes(x = Dim.1, y = Dim.2, color = Set)) +
  geom_point(size = 2, alpha = 0.8) +
  theme_minimal() +
  labs(title = "Projection ACP : test vs apprentissage",
       x = xlabel, y = ylabel) +
  scale_color_manual(values = c("Apprentissage" = "#1f77b4", "Test" = "#ff7f0e")) +
  theme(legend.position = "bottom", legend.title = element_blank())
plot
ggsave(file.path(directory, "projection_acp_app_test.pdf"), plot, width = 6, height = 5)


##################
## 3 : Estimation de modèles logistiques
##################
df_app$y <- as.factor(df_app[,p])
df_test$y <- as.factor(df_test[,p])
acp_coords <- as.data.frame(res_pca_app$ind$coord[, 1:2])  # PC1 et PC2 pour les tracés


# Modèle complet 
model_full <- glm(y ~ ., data = df_app[,-p], family = binomial)
summary(model_full)
# Call:
# glm(formula = y ~ ., family = binomial, data = df_app[, -p])
# Coefficients:
#                    Estimate Std. Error z value Pr(>|z|)    
# (Intercept)      9.113e+00  8.258e+00   1.103  0.26983    
# Area            -5.661e-04  1.072e-04  -5.283 1.27e-07
# MajorAxisLength  5.951e-02  1.854e-02   3.209  0.00133
# MinorAxisLength  9.261e-02  3.207e-02   2.887  0.00388
# Eccentricity    -6.151e-01  6.274e+00  -0.098  0.92190    
# ConvexArea       4.865e-04  8.878e-05   5.480 4.26e-08 
# Extent          -3.094e+00  3.260e+00  -0.949  0.34255    
# Perimeter       -4.361e-02  7.997e-03  -5.453 4.95e-08 
# ---
# Signif. codes:  0 ‘***' 0.001 ‘**' 0.01 ‘*' 0.05 ‘.' 0.1 ‘ ' 1
# (Dispersion parameter for binomial family taken to be 1)
# Null deviance: 831.45  on 599  degrees of freedom
# Residual deviance: 409.85  on 592  degrees of freedom
# AIC: 425.85
# Number of Fisher Scoring iterations: 7
AIC_full <- AIC(model_full)
AIC_full # 425.8527
BIC_full <- BIC(model_full)
BIC_full # 461.0281
model_full$null.deviance # modèle sans variance : 831.4499
SCR_full <- model_full$deviance  # modèle avec variance
SCR_full # 409.8527
anova(model_full)
# Analysis of Deviance Table
# Model: binomial, link: logit
# Response: y
# 
# Terms added sequentially (first to last)
#                  Df Deviance Resid. Df Resid. Dev  Pr(>Chi)    
# NULL                              599     831.45              
# Area             1   329.11       598     502.34 < 2.2e-16 
# MajorAxisLength  1    56.83       597     445.52 4.762e-14 
# MinorAxisLength  1     1.86       596     443.65    0.1722    
# Eccentricity     1     0.47       595     443.19    0.4944    
# ConvexArea       1     0.00       594     443.19    0.9690    
# Extent           1     0.40       593     442.79    0.5273    
# Perimeter        1    32.93       592     409.85 9.538e-09 
# ---
# Signif. codes:  0 ‘***' 0.001 ‘**' 0.01 ‘*' 0.05 ‘.' 0.1 ‘ ' 1
# Graphiques pour la prédiction du modèle
pred_proba <- predict(model_full, type = "response")  # proba prédite pour Kecimen
classe_pred <- ifelse(pred_proba > 0.5, "Kecimen", "Besni")
df_plot <- data.frame(
  PC1 = acp_coords[, 1],
  PC2 = acp_coords[, 2],
  ClasseReelle = df_app$y,
  ProbaKecimen = pred_proba,
  ClassePredite = classe_pred
)
plot_model_full <- ggplot(df_plot, aes(x = PC1, y = PC2)) +
  geom_point(aes(color = df_app$y, shape = ClassePredite, alpha = ProbaKecimen), size = 3) +
  scale_color_manual(values = c("Besni" = "blue", "Kecimen" = "red")) +
  scale_shape_manual(values = c("Besni" = 3, "Kecimen" = 16)) +
  scale_alpha_continuous(range = c(0.4, 1)) +
  labs(title = "Projection des individus sur les 2 premiers axes ACP", subtitle = "Couleur : classe réelle | Forme : classe prédite | Transparence : proba prédite", x = "PC1", y = "PC2") +
  theme_minimal()
plot_model_full
ggsave(file.path(directory, "model_full_projection_app.pdf"), plot_model_full, width = 6, height = 5)


# Modèle avec seulement les deux premières composantes principales
df_pca_app <- data.frame(res_pca_app$ind$coord[, 1:2], y = df_app$y)
model_pca <- glm(y ~ ., data = df_pca_app, family = binomial)
summary(model_pca)
# Call:
# glm(formula = y ~ ., family = binomial, data = df_pca_app)
# Coefficients:
#               Estimate Std. Error z value Pr(>|z|)    
# (Intercept)  -0.2981     0.1272  -2.343   0.0191   
# Dim.1        -1.3752     0.1143 -12.028   <2e-16
# Dim.2         0.4907     0.1176   4.174    3e-05
# ---
# Signif. codes:  0 ‘***' 0.001 ‘**' 0.01 ‘*' 0.05 ‘.' 0.1 ‘ ' 1
# (Dispersion parameter for binomial family taken to be 1)
# Null deviance: 831.45  on 599  degrees of freedom
# Residual deviance: 447.38  on 597  degrees of freedom
# AIC: 453.38
# Number of Fisher Scoring iterations: 6
AIC_pca <- AIC(model_pca)
AIC_pca # 453.3773
BIC_pca <- BIC(model_pca)
BIC_pca # 466.5681
model_pca$null.deviance # modèle sans variance : 831.4499
SCR_pca <- model_pca$deviance  # modèle avec variance
SCR_pca # 447.3773
anova(model_pca)
# Analysis of Deviance Table
# Model: binomial, link: logit
# Response: y
# Terms added sequentially (first to last)
#       Df Deviance Resid. Df Resid. Dev  Pr(>Chi)    
# NULL                    599     831.45              
# Dim.1  1   364.90       598     466.55 < 2.2e-16
# Dim.2  1    19.17       597     447.38 1.196e-05
# ---
# Signif. codes:  0 ‘***' 0.001 ‘**' 0.01 ‘*' 0.05 ‘.' 0.1 ‘ ' 1
# Graphiques pour la prédiction du modèle
pred_proba <- predict(model_pca, type = "response")  # proba prédite pour Kecimen
classe_pred <- ifelse(pred_proba > 0.5, "Kecimen", "Besni")
df_plot <- data.frame(
  PC1 = acp_coords[, 1],
  PC2 = acp_coords[, 2],
  ClasseReelle = df_app$y,
  ProbaKecimen = pred_proba,
  ClassePredite = classe_pred
)
plot_model_pca <- ggplot(df_plot, aes(x = PC1, y = PC2)) +
  geom_point(aes(color = df_app$y, shape = ClassePredite, alpha = ProbaKecimen), size = 3) +
  scale_color_manual(values = c("Besni" = "blue", "Kecimen" = "red")) +
  scale_shape_manual(values = c("Besni" = 3, "Kecimen" = 16)) +
  scale_alpha_continuous(range = c(0.4, 1)) +
  labs(title = "Projection des individus sur les 2 premiers axes ACP", subtitle = "Couleur : classe réelle | Forme : classe prédite | Transparence : proba prédite", x = "PC1", y = "PC2") +
  theme_minimal()
plot_model_pca
ggsave(file.path(directory, "model_pca_projection_app.pdf"), plot_model_pca, width = 6, height = 5)


# Par sélection de variables avec critère AIC
model_aic <- stepAIC(model_full)
# Start:  AIC=425.85
# y ~ Area + MajorAxisLength + MinorAxisLength + Eccentricity + ConvexArea + Extent + Perimeter
#                   Df Deviance    AIC
# - Eccentricity     1   409.86 423.86
# - Extent           1   410.75 424.75
# <none>                 409.85 425.85
# - MinorAxisLength  1   419.11 433.11
# - MajorAxisLength  1   420.88 434.88
# - ConvexArea       1   425.96 439.96
# - Area             1   429.59 443.59
# - Perimeter        1   442.79 456.79
# 
# Step:  AIC=423.86
# y ~ Area + MajorAxisLength + MinorAxisLength + Eccentricity + ConvexArea + Perimeter
#                   Df Deviance    AIC
# - Extent           1   410.76 422.76
# <none>                 409.86 423.86
# - MajorAxisLength  1   421.14 433.14
# - ConvexArea       1   426.29 438.29
# - MinorAxisLength  1   426.63 438.63
# - Area             1   430.64 442.64
# - Perimeter        1   443.25 455.25
# 
# Step:  AIC=422.76
# y ~ Area + MajorAxisLength + MinorAxisLength + ConvexArea + Perimeter
#                   Df Deviance    AIC
# <none>                 410.76 422.76
# - MajorAxisLength  1   421.43 431.43
# - MinorAxisLength  1   426.74 436.74
# - ConvexArea       1   427.17 437.17
# - Area             1   431.88 441.88
# - Perimeter        1   443.65 453.65
summary(model_aic)
# Call:
# glm(formula = y ~ Area + MajorAxisLength + MinorAxisLength + ConvexArea + Perimeter, family = binomial, data = df_app[, -p])
# Coefficients:
#                    Estimate Std. Error z value Pr(>|z|)    
# (Intercept)      5.941e+00  5.054e+00   1.175 0.239809    
# Area            -5.716e-04  9.348e-05  -6.115 9.67e-10 
# MajorAxisLength  5.742e-02  1.834e-02   3.131 0.001741
# MinorAxisLength  9.179e-02  2.514e-02   3.652 0.000261 
# ConvexArea       4.841e-04  7.924e-05   6.109 1.00e-09 
# Perimeter       -4.163e-02  7.472e-03  -5.572 2.52e-08 
# ---
# Signif. codes:  0 ‘***' 0.001 ‘**' 0.01 ‘*' 0.05 ‘.' 0.1 ‘ ' 1
# (Dispersion parameter for binomial family taken to be 1)
# Null deviance: 831.45  on 599  degrees of freedom
# Residual deviance:  410.76  on 594  degrees of freedom
# AIC: 422.76
# Number of Fisher Scoring iterations: 7
AIC_aic <- AIC(model_aic)
AIC_aic # 422.7615
BIC_aic <- BIC(model_aic)
BIC_aic # 449.1431
model_aic$null.deviance # modèle sans variance : 831.4499
SCR_aic <- model_aic$deviance  # modèle avec variance
SCR_aic # 410.7615
anova(model_aic)
# Analysis of Deviance Table
# Model: binomial, link: logit
# Response: y
# Terms added sequentially (first to last)
#                  Df Deviance Resid. Df Resid. Dev  Pr(>Chi)    
# NULL                              599     831.45              
# Area             1   329.11       598     502.34 < 2.2e-16
# MajorAxisLength  1    56.83       597     445.52 4.762e-14
# MinorAxisLength  1     1.86       596     443.65    0.1722    
# ConvexArea       1     0.00       595     443.65    0.9925    
# Perimeter        1    32.89       594     410.76 9.740e-09
# ---
# Signif. codes:  0 ‘***' 0.001 ‘**' 0.01 ‘*' 0.05 ‘.' 0.1 ‘ ' 1
# Graphiques pour la prédiction du modèle
pred_proba <- predict(model_aic, type = "response")  # proba prédite pour Kecimen
classe_pred <- ifelse(pred_proba > 0.5, "Kecimen", "Besni")
df_plot <- data.frame(
  PC1 = acp_coords[, 1],
  PC2 = acp_coords[, 2],
  ClasseReelle = df_app$y,
  ProbaKecimen = pred_proba,
  ClassePredite = classe_pred
)
plot_model_aic <- ggplot(df_plot, aes(x = PC1, y = PC2)) +
  geom_point(aes(color = df_app$y, shape = ClassePredite, alpha = ProbaKecimen), size = 3) +
  scale_color_manual(values = c("Besni" = "blue", "Kecimen" = "red")) +
  scale_shape_manual(values = c("Besni" = 3, "Kecimen" = 16)) +
  scale_alpha_continuous(range = c(0.4, 1)) +
  labs(title = "Projection des individus sur les 2 premiers axes ACP", subtitle = "Couleur : classe réelle | Forme : classe prédite | Transparence : proba prédite", x = "PC1", y = "PC2") +
  theme_minimal()
plot_model_aic
ggsave(file.path(directory, "model_aic_projection_app.pdf"), plot_model_aic, width = 6, height = 5)


# Par régression Lasso (pénalisation L1)
x <- model.matrix(y ~ ., data = df_app[,-p])
cv_lasso <- cv.glmnet(x, df_app$y, family = "binomial", alpha = 1)
cv_lasso$lambda.min # 0.0005896299
coef_lasso <- coef(cv_lasso, s = "lambda.min")
coef_lasso
# 9 x 1 sparse Matrix of class "dgCMatrix"
# s1
# (Intercept)      1.589004e+01
# (Intercept)      .           
# Area            -2.181639e-06
# MajorAxisLength  5.222432e-03
# MinorAxisLength  1.520593e-02
# Eccentricity    -4.692710e+00
# ConvexArea       .           
# Extent          -1.982167e+00
# Perimeter       -1.463472e-02
# Liste des variables sélectionnées (coefficients non nuls sauf intercept)
selected_vars_lasso <- rownames(coef_lasso)[coef_lasso[, 1] != 0]
selected_vars_lasso <- selected_vars_lasso[selected_vars_lasso != "(Intercept)"]  # on enlève l'intercept
selected_vars_lasso
# "Area"    "MajorAxisLength" "MinorAxisLength" "Eccentricity" "Extent"     "Perimeter"
# Modèle glm final avec juste les variables sélectionnées 
formula_lasso <- as.formula(paste("y ~", paste(selected_vars_lasso, collapse = " + ")))
model_lasso <- glm(formula_lasso, data = df_app[,-p], family = binomial)
summary(model_lasso)
# Call:
# glm(formula = formula_lasso, family = binomial, data = df_app)
# Coefficients:
#                    Estimate Std. Error z value Pr(>|z|)    
# (Intercept)      6.872e+00  8.397e+00   0.818   0.4131    
# Area            -1.210e-04  6.607e-05  -1.832   0.0670  
# MajorAxisLength  4.204e-02  1.792e-02   2.345   0.0190  
# MinorAxisLength  6.940e-02  3.058e-02   2.269   0.0233  
# Eccentricity    -3.687e+00  6.580e+00  -0.560   0.5753    
# Extent          -2.978e+00  3.179e+00  -0.937   0.3488    
# Perimeter       -2.374e-02  6.036e-03  -3.934 8.37e-05 
# ---
# Signif. codes:  0 ‘***' 0.001 ‘**' 0.01 ‘*' 0.05 ‘.' 0.1 ‘ ' 1
# (Dispersion parameter for binomial family taken to be 1)
# Null deviance: 831.45  on 599  degrees of freedom
# Residual deviance:  425.96  on 593  degrees of freedom
# AIC: 439.96
# Number of Fisher Scoring iterations: 7
AIC_lasso <- AIC(model_lasso)
AIC_lasso # 439.9599
BIC_lasso <- BIC(model_lasso)
BIC_lasso # 470.7384
model_lasso$null.deviance # modèle sans variance : 831.4499
SCR_lasso <- model_lasso$deviance  # modèle avec variance
SCR_lasso # 425.9599
anova(model_lasso)
# Analysis of Deviance Table
# Model: binomial, link: logit
# Response: y
# Terms added sequentially (first to last)
#                 Df Deviance Resid. Df Resid. Dev  Pr(>Chi)    
# NULL                              599     831.45              
# Area             1   329.11       598     502.34 < 2.2e-16 
# MajorAxisLength  1    56.83       597     445.52 4.762e-14 
# MinorAxisLength  1     1.86       596     443.65    0.1722    
# Eccentricity     1     0.47       595     443.19    0.4944    
# Extent           1     0.35       594     442.83    0.5525    
# Perimeter        1    16.87       593     425.96 3.994e-05 
# ---
# Signif. codes:  0 ‘***' 0.001 ‘**' 0.01 ‘*' 0.05 ‘.' 0.1 ‘ ' 1
# Graphiques pour la prédiction du modèle
pred_proba <- predict(model_lasso, type = "response")  # proba prédite pour Kecimen
classe_pred <- ifelse(pred_proba > 0.5, "Kecimen", "Besni")
df_plot <- data.frame(
  PC1 = acp_coords[, 1],
  PC2 = acp_coords[, 2],
  ClasseReelle = df_app$y,
  ProbaKecimen = pred_proba,
  ClassePredite = classe_pred
)
plot_model_lasso <- ggplot(df_plot, aes(x = PC1, y = PC2)) +
  geom_point(aes(color = df_app$y, shape = ClassePredite, alpha = ProbaKecimen), size = 3) +
  scale_color_manual(values = c("Besni" = "blue", "Kecimen" = "red")) +
  scale_shape_manual(values = c("Besni" = 3, "Kecimen" = 16)) +
  scale_alpha_continuous(range = c(0.4, 1)) +
  labs(title = "Projection des individus sur les 2 premiers axes ACP", subtitle = "Couleur : classe réelle | Forme : classe prédite | Transparence : proba prédite", x = "PC1", y = "PC2") +
  theme_minimal()
plot_model_lasso
ggsave(file.path(directory, "model_lasso_projection_app.pdf"), plot_model_lasso, width = 6, height = 5)


# Par régression Ridge (pénalisation L2)
x <- model.matrix(y ~ ., data = df_app[,-p])
cv_ridge <- cv.glmnet(x, df_app$y, family = "binomial", alpha = 0)  
cv_ridge$lambda.min # 0.03296509
coef_ridge <- coef(cv_ridge, s = "lambda.min")
coef_ridge
# 9 x 1 sparse Matrix of class "dgCMatrix"
# s1
# (Intercept)      1.142420e+01
# (Intercept)      .           
# Area            -1.102973e-05
# MajorAxisLength -4.796859e-03
# MinorAxisLength -4.370674e-03
# Eccentricity    -6.554335e+00
# ConvexArea      -1.015860e-05
# Extent           1.554541e+00
# Perimeter       -2.160816e-03
# Liste des variables sélectionnées (coefficients non nuls sauf intercept)
selected_vars_ridge <- rownames(coef_ridge)[coef_ridge[, 1] != 0]
selected_vars_ridge <- selected_vars_ridge[selected_vars_ridge != "(Intercept)"]
selected_vars_ridge
# "Area"    "MajorAxisLength" "MinorAxisLength" "Eccentricity" "ConvexArea" "Extent"    "Perimeter"
# Modèle glm final avec juste les variables sélectionnées 
formula_ridge <- as.formula(paste("y ~", paste(selected_vars_ridge, collapse = " + ")))
model_ridge <- glm(formula_ridge, data = df_app[,-p], family = binomial)
summary(model_ridge)
# Call:
# glm(formula = formula_ridge, family = binomial, data = df_app)
# Coefficients:
#                   Estimate Std. Error z value Pr(>|z|)    
# (Intercept)      9.113e+00  8.258e+00   1.103  0.26983    
# Area            -5.661e-04  1.072e-04  -5.283 1.27e-07 
# MajorAxisLength  5.951e-02  1.854e-02   3.209  0.00133  
# MinorAxisLength  9.261e-02  3.207e-02   2.887  0.00388 
# Eccentricity    -6.151e-01  6.274e+00  -0.098  0.92190    
# ConvexArea       4.865e-04  8.878e-05   5.480 4.26e-08 
# Extent          -3.094e+00  3.260e+00  -0.949  0.34255    
# Perimeter       -4.361e-02  7.997e-03  -5.453 4.95e-08 
# ---
# Signif. codes:  0 ‘***' 0.001 ‘**' 0.01 ‘*' 0.05 ‘.' 0.1 ‘ ' 1
# (Dispersion parameter for binomial family taken to be 1)
# Null deviance: 831.45  on 599  degrees of freedom
# Residual deviance: 409.85  on 592  degrees of freedom
# AIC: 425.85
# Number of Fisher Scoring iterations: 7
AIC_ridge <- AIC(model_ridge)
AIC_ridge # 425.8527
BIC_ridge <- BIC(model_ridge)
BIC_ridge # 461.0281
model_ridge$null.deviance # modèle sans variance : 831.4499
SCR_ridge <- model_ridge$deviance  # modèle avec variance
SCR_ridge # 409.8527
anova(model_ridge)
# Analysis of Deviance Table
# Model: binomial, link: logit
# Response: y
# Terms added sequentially (first to last)
#                 Df Deviance Resid. Df Resid. Dev  Pr(>Chi)    
# NULL                              599     831.45              
# Area             1   329.11       598     502.34 < 2.2e-16 
# MajorAxisLength  1    56.83       597     445.52 4.762e-14 
# MinorAxisLength  1     1.86       596     443.65    0.1722    
# Eccentricity     1     0.47       595     443.19    0.4944    
# ConvexArea       1     0.00       594     443.19    0.9690    
# Extent           1     0.40       593     442.79    0.5273    
# Perimeter        1    32.93       592     409.85 9.538e-09 
# ---
# Signif. codes:  0 ‘***' 0.001 ‘**' 0.01 ‘*' 0.05 ‘.' 0.1 ‘ ' 1
# Graphiques pour la prédiction du modèle
pred_proba <- predict(model_ridge, type = "response")  # proba prédite pour Kecimen
classe_pred <- ifelse(pred_proba > 0.5, "Kecimen", "Besni")
df_plot <- data.frame(
  PC1 = acp_coords[, 1],
  PC2 = acp_coords[, 2],
  ClasseReelle = df_app$y,
  ProbaKecimen = pred_proba,
  ClassePredite = classe_pred
)
plot_model_ridge <- ggplot(df_plot, aes(x = PC1, y = PC2)) +
  geom_point(aes(color = df_app$y, shape = ClassePredite, alpha = ProbaKecimen), size = 3) +
  scale_color_manual(values = c("Besni" = "blue", "Kecimen" = "red")) +
  scale_shape_manual(values = c("Besni" = 3, "Kecimen" = 16)) +
  scale_alpha_continuous(range = c(0.4, 1)) +
  labs(title = "Projection des individus sur les 2 premiers axes ACP", subtitle = "Couleur : classe réelle | Forme : classe prédite | Transparence : proba prédite", x = "PC1", y = "PC2") +
  theme_minimal()
plot_model_ridge
ggsave(file.path(directory, "model_ridge_projection_app.pdf"), plot_model_ridge, width = 6, height = 5)


# coloration = classe réelle, forme = prédiction, transparence = proba


##################
## 4 : Modèle SVM linéaire, noyau polynomial 
##################
test_cost <- c(0.01, 0.1, 1, 5, 10, 100)

df_pca_app_plot <- data.frame(
  x1 = res_pca_app$ind$coord[, 1],
  x2 = res_pca_app$ind$coord[, 2],
  y = df_app$y
)
# (données normalisée, car normalisation pas prise en compte dans tune)
X <- scale(df_app[ , -which(names(df_app) %in% c("y", "Class"))])
df_app_scaled <- as.data.frame(X)
df_app_scaled$y <- df_app$y


# Modèle SVM linéaire
# Validation croisée pour choisir le meilleur cost 
tune_results <- tune(svm, y ~ ., data = df_app_scaled, kernel = 'linear', ranges = list(cost = test_cost), probability = TRUE)
summary(tune_results)
# Parameter tuning of ‘svm':
# - sampling method: 10-fold cross validation 
# - best parameters:
# cost
# 100
# - best performance: 0.135
# - Detailed performance results:
#    cost     error dispersion
# 1 1e-02 0.1433333 0.03258417
# 2 1e-01 0.1416667 0.03356402
# 3 1e+00 0.1383333 0.03047970
# 4 5e+00 0.1416667 0.03621779
# 5 1e+01 0.1400000 0.03784308
# 6 1e+02 0.1350000 0.03374743
best_cost_lin <- tune_results$best.parameters$cost
cat("Meilleur coût sélectionné : ", best_cost_lin, "\n") # 100
model_svm_lin <- tune_results$best.model
summary(model_svm_lin)
# Call:
# best.tune(METHOD = svm, train.x = y ~ ., data = df_app_scaled, ranges = list(cost = test_cost), kernel = "linear", probability = TRUE)
# Parameters:
# SVM-Type:  C-classification 
# SVM-Kernel:  linear 
# cost:  100 
# Number of Support Vectors:  216
# ( 108 108 )
# Number of Classes:  2 
# Levels: 
# Besni Kecimen
pred_lin <- predict(model_svm_lin, df_app_scaled, probability = TRUE)
proba_lin <- attr(pred_lin, "probabilities")[, "Kecimen"]
# Entraînement SVM juste sur le plan PCA pour tracer la frontière
svm_pca_lin <- svm(y ~ ., data = df_pca_app_plot, kernel = "linear", cost = best_cost_lin, scale = TRUE)
# Identifier les vecteurs supports dans le plan PCA
sv_indices_lin <- svm_pca_lin$index
df_pca_app_plot$ClasseReelle <- df_app$y
df_pca_app_plot$ClassePredite <- pred_lin
df_pca_app_plot$ProbaKecimen <- proba_lin
df_pca_app_plot$IsSupportVector <- FALSE
df_pca_app_plot$IsSupportVector[sv_indices_lin] <- TRUE
# Calcul des coefficients (w, b) à partir du SVM PCA
X_sv <- as.matrix(df_pca_app_plot[sv_indices_lin, c("x1", "x2")])
w <- t(svm_pca_lin$coefs) %*% X_sv
b <- -svm_pca_lin$rho
# Tracé
x_range <- range(df_pca_app_plot$x1)
x_margin <- diff(x_range) * 0.1
x_seq <- seq(x_range[1] - x_margin, x_range[2] + x_margin, length.out = 200)
x_min <- min(df_pca_app_plot$x1)/10
x_max <- max(df_pca_app_plot$x1)/10
plot_svm_lin <- ggplot(df_pca_app_plot, aes(x = x1, y = x2)) +
  # Frontière de décision
  stat_function(fun = function(x) (-w[1,1] * x - b) / w[1,2], color = "black", linewidth = 1, xlim = c(x_min, x_max)) +
  # Marges
  stat_function(fun = function(x) (-w[1,1] * x - b + 1) / w[1,2], linetype = "dashed", color = "gray40", xlim = c(x_min, x_max)) +
  stat_function(fun = function(x) (-w[1,1] * x - b - 1) / w[1,2], linetype = "dashed", color = "gray40", xlim = c(x_min, x_max)) +
  # Points colorés selon la classe réelle
  geom_point(aes(color = ClasseReelle, shape = ClassePredite, alpha = ProbaKecimen, size = IsSupportVector)) +
  # Triangles noirs sur les vecteurs de support
  geom_point(data = df_pca_app_plot[df_pca_app_plot$IsSupportVector == TRUE, ], aes(x = x1, y = x2), shape = 17, color = "black", size = 2) +
  # Échelles esthétiques
  scale_color_manual(values = c("Besni" = "blue", "Kecimen" = "red")) +
  scale_shape_manual(values = c("Besni" = 3, "Kecimen" = 16)) +
  scale_alpha_continuous(range = c(0.4, 1)) +
  scale_size_manual(values = c(`FALSE` = 3, `TRUE` = 5)) +
  # Légende et thème
  labs(title = "SVM entraîné sur données originales, visualisation dans le plan ACP",
    subtitle = "Couleur = classe réelle | Forme = classe prédite | Transparence = proba | Taille & triangle = vecteurs support (ACP)",
    x = "Composante principale 1", y = "Composante principale 2",
    color = "Classe réelle", shape = "Classe prédite", alpha = "Proba Kecimen", size = "Vecteur support"
  ) +
  theme_minimal()
plot_svm_lin
ggsave(file.path(directory, "svm_linear_projection_app.pdf"), plot_svm_lin, width = 12, height = 10)


# Modèle SVM avec noyau polynomial
# Validation croisée pour choisir le meilleur cost 
tune_results <- tune(svm, y ~ ., data = df_app_scaled, kernel = 'polynomial', ranges = list(cost = test_cost), probability = TRUE)
summary(tune_results)
# Parameter tuning of ‘svm':
# - sampling method: 10-fold cross validation 
# - best parameters:
# cost
# 100
# - best performance: 0.1516667
# - Detailed performance results:
#   cost     error dispersion
# 1 1e-02 0.3316667 0.05178898
# 2 1e-01 0.2333333 0.06620208
# 3 1e+00 0.1666667 0.04581228
# 4 5e+00 0.1683333 0.02415229
# 5 1e+01 0.1583333 0.03788384
# 6 1e+02 0.1516667 0.04611446
best_cost_poly <- tune_results$best.parameters$cost
cat("Meilleur coût sélectionné : ", best_cost_poly, "\n") # 100
model_svm_poly <- tune_results$best.model
summary(model_svm_poly)
# Call:
# svm(formula = y ~ ., data = df_app, kernel = "polynomial", cost = best_cost_poly, probability = TRUE, scale = TRUE)
# Parameters:
# SVM-Type:  C-classification 
# SVM-Kernel:  polynomial 
# cost:  100 
# degree:  3 
# coef.0:  0 
# Number of Support Vectors:  261
# ( 131 130 )
# Number of Classes:  2 
# Levels: 
# Besni Kecimen
pred_poly <- predict(model_svm_poly, df_app_scaled, probability = TRUE)
proba_poly <- attr(pred_poly, "probabilities")[, "Kecimen"]
# Entraînement du modèle SVM sur les composantes principales pour tracer la frontière
svm_pca_poly <- svm(y ~ x1 + x2, data = df_pca_app_plot, kernel = "polynomial", cost = best_cost_poly, scale = TRUE)
# Ajout des informations dans le dataframe PCA
df_pca_app_plot$ClasseReelle <- df_app$y
df_pca_app_plot$ClassePredite <- pred_poly
df_pca_app_plot$IsSupportVector <- FALSE
df_pca_app_plot$IsSupportVector[svm_pca_poly$index] <- TRUE
# Création de la grille pour estimer la frontière
x1_seq <- seq(min(df_pca_app_plot$x1), max(df_pca_app_plot$x1), length.out = 300)
x2_seq <- seq(min(df_pca_app_plot$x2), max(df_pca_app_plot$x2), length.out = 300)
grid_df <- expand.grid(x1 = x1_seq, x2 = x2_seq)
grid_df$Predicted <- predict(svm_pca_poly, newdata = grid_df)
# Tracé combiné
plot_svm_poly <- ggplot(df_pca_app_plot, aes(x = x1, y = x2)) +
  # Frontière non linéaire estimée par SVM PCA
  geom_contour(data = cbind(grid_df, z = as.numeric(grid_df$Predicted == "Kecimen")), aes(x = x1, y = x2, z = z), breaks = 0.5, color = "black", linewidth = 1) +
  # Points des données projetées (classes réelles & prédictions)
  geom_point(aes(color = ClasseReelle, shape = ClassePredite, size = IsSupportVector)) +
  # Marqueurs supplémentaires pour les vecteurs de support
  geom_point(data = subset(df_pca_app_plot, IsSupportVector), aes(x = x1, y = x2), shape = 17, color = "black", size = 2) +
  # Échelles esthétiques
  scale_color_manual(values = c("Besni" = "blue", "Kecimen" = "red")) +
  scale_shape_manual(values = c("Besni" = 3, "Kecimen" = 16)) +
  scale_alpha_continuous(range = c(0.4, 1)) +
  scale_size_manual(values = c(`FALSE` = 3, `TRUE` = 5)) +
  # Légendes et thème
  labs(title = "SVM polynomial : prédictions (données originales) et frontière (plan ACP)",
       subtitle = "Couleur = classe réelle | Forme = prédite | Alpha = proba Kecimen | Taille & triangle = vecteurs support",
       x = "Composante principale 1", y = "Composante principale 2",
       color = "Classe réelle", shape = "Classe prédite", alpha = "Proba Kecimen", size = "Vecteur support") +
  theme_minimal()
plot_svm_poly
ggsave(file.path(directory, "svm_polynomial_projection_app.pdf"), plot_svm_poly, width = 12, height = 10)



##################
## 5 : Courbes ROC
##################
directory <- "ROC"
dir.create(directory, showWarnings = FALSE)

# Fonctions qui trace les différents graphiques pour chaque modèle
analyse_modele_ggplot <- function(model, data, p, filename = NULL) {

  # Prédictions : Gestion spéciale pour SVM
  if ("svm" %in% class(model)) {
    pred <- predict(model, data, probability = TRUE)
    predproba <- attr(pred, "probabilities")[, "Kecimen"]
    predproba <- as.numeric(predproba)
  } else if ("lda" %in% class(model)) {
    pred <- predict(model, newdata = data)
    predproba <- pred$posterior[, "Kecimen"]
  } else if ("qda" %in% class(model)) {
    pred <- predict(model, newdata = data)
    predproba <- pred$posterior[, "Kecimen"]
  } else {
    predproba <- predict(model, newdata = data, type = "response")
  }
  # Calcul de l'erreur d'apprentissage
  seuil_bayes <- 0.5
  Y_pred_bayes <- as.numeric(predproba > seuil_bayes)
  if ("lda" %in% class(model)) {
    data$y_num <- as.numeric(data[,3] == "Kecimen")
  } else if ("qda" %in% class(model)) {
    data$y_num <- as.numeric(data[,3] == "Kecimen")
  } else {
    data$y_num <- as.numeric(data[,p] == "Kecimen")
  }
  conf_bayes <- table(Pred = Y_pred_bayes, True = data$y_num)
  print(conf_bayes)
  err_bayes <- mean(Y_pred_bayes != data$y_num)
  cat("Erreur d'apprentissage avec seuil de Bayes (0.5) :", err_bayes, "\n")

  # Seuils et initialisation
  seuils <- seq(0, 1, length.out = 1000)
  # Appliquer la fonction à chaque seuil
  metrics <- sapply(seuils, function(s) {
    Y_pred <- as.numeric(predproba > s)
    FP <- sum(Y_pred == 1 & data$y_num == 0)
    FN <- sum(Y_pred == 0 & data$y_num == 1)
    VP <- sum(Y_pred == 1 & data$y_num == 1)
    VN <- sum(Y_pred == 0 & data$y_num == 0)
    err <- mean(Y_pred != data$y_num)
    c(FP = FP, FN = FN, FPN = FP + FN, VP = VP, VN = VN, err = err)
  })
  # Transposer pour avoir une matrice avec une colonne par variable
  metrics <- t(metrics)
  # Construire df_plot à partir de cette matrice
  df_plot <- data.frame(
    seuil = seuils,
    FP = metrics[, "FP"],
    FN = metrics[, "FN"],
    FPN = metrics[, "FPN"],
    VP = metrics[, "VP"],
    VN = metrics[, "VN"],
    err = metrics[, "err"],
    sens = metrics[, "VP"] / (metrics[, "VP"] + metrics[, "FN"]),
    spec = metrics[, "VN"] / (metrics[, "VN"] + metrics[, "FP"])
  )
  # Taux de faux positifs, faux négatifs et erreur
  seuil_optimal <- seuils[which.min(df_plot$err)]
  cat("Seuil minimisant l'erreur :", seuil_optimal, "\n")
  
  # Graphique FP, FN, FPN
  plot_fp_fn_err <- ggplot(df_plot, aes(x = seuil)) +
    geom_line(aes(y = FP), color = "red") +
    geom_line(aes(y = FN), color = "blue") +
    geom_line(aes(y = FPN), color = "darkgreen", linetype = "dashed") +
    annotate("text", x = 0.98, y = max(df_plot$FPN)-70, label = "Faux positifs", color = "red", hjust = 1) +
    annotate("text", x = 0.98, y = max(df_plot$FPN)-35, label = "Faux négatifs", color = "blue", hjust = 1) +
    annotate("text", x = 0.98, y = max(df_plot$FPN), label = "Faux positifs + négatifs", color = "darkgreen", hjust = 1) +
    labs(x = "Seuil", y = "Nombre d'erreurs") +
    theme_minimal()
  print(plot_fp_fn_err)

  # Graphique de l'erreur
  plot_err <- ggplot(df_plot) +
    geom_line(aes(x = seuil, y = err), color = "darkgreen") +
    geom_point(x = seuil_optimal, y = min(df_plot$err), color = "red", size = 2) +
    annotate("text", x = seuil_optimal, y = min(df_plot$err), label = paste("min à", round(seuil_optimal, 3)), hjust = -0.1, vjust = 1, color = "red") +
    labs(x = "Seuil", y = "Erreur de classification", title = "Erreur selon Seuil") +
    theme_minimal()
  print(plot_err)

  # Courbe ROC
  pred_rocr <- prediction(predproba, data$y_num)
  perf_rocr <- performance(pred_rocr, "tpr", "fpr")
  # Calcul du seuil pour sensibilité ≥ 0.95
  i95 <- which(rev(df_plot$sens) >= 0.95)[1]
  i95_real <- length(seuils) - i95 + 1
  seuil_95 <- seuils[i95_real]
  x_95 <- 1 - df_plot$spec[i95_real]
  y_95 <- df_plot$sens[i95_real]
  cat("Seuil 95% :", seuil_95, "\n")
  
  # AUC
  perf_auc <- performance(pred_rocr, "auc")
  AUC <- unlist(perf_auc@y.values)
  cat("AUC :", AUC, "\n")

  # Construction du graphique ROC avec marquage du point
  plot_roc <- ggplot() +
    geom_line(data = df_plot, aes(x = 1 - spec, y = sens), color = "blue", size = 1.5) + 
    geom_line(aes(x = unlist(perf_rocr@x.values), y = unlist(perf_rocr@y.values)), color = "darkorange", size = 0.75) +
    geom_abline(slope = 1, intercept = 0, linetype = "dashed", color = "gray") +
    geom_point(aes(x = x_95, y = y_95), color = "red", size = 3) +
    annotate("text", x = x_95, y = y_95, label = paste0("seuil 95% = ", round(seuil_95, 2)), hjust = 0, vjust = 1, color = "red") +
    annotate("text", x = 0.6, y = 0.1, label = paste0("AUC = ", round(AUC, 3)), hjust = 0, vjust = 0, size = 5, color = "black") +
    labs(x = "Taux de faux positifs (1 - spécificité)", y = "Sensibilité (rappel)", title = "Courbe ROC") +
    theme_minimal()
  print(plot_roc)

  # Combine et afficher les graphiques
  g_final <- plot_fp_fn_err / plot_err / plot_roc + plot_layout(guides = "collect")
  print(g_final)

  # Sauvegarde si demandée
  if (!is.null(filename)) {
    ggsave(file.path(directory, filename), plot = g_final, width = 5, height = 10)
    cat("Sauvegardé dans", filename, "\n")
  }

  return(list(perf_rocr = perf_rocr, x95 = x_95, y95 = y_95, seuil95 = seuil_95, auc = AUC))
}

# Liste des modèles à analyser
models <- list(
  model_full = model_full,
  model_pca = model_pca,
  model_aic = model_aic,
  model_lasso = model_lasso,
  model_ridge = model_ridge,
  model_svm_lin = model_svm_lin,
  model_svm_poly = model_svm_poly
)
# Analyser chaque modèle
resultats <- list()
for (model_name in names(models)) {
  model <- models[[model_name]]

  # Choix des données selon le modèle
  data_for_analysis <- df_app
  n_va <- ncol(df_app)
  if (model_name == "model_pca") {
    data_for_analysis <- df_pca_app
    n_va <- ncol(df_pca_app)
  } else if ("svm" %in% class(model)) {
    data_for_analysis <- df_app_scaled
    n_va <- ncol(df_app_scaled)
  }
  cat("Analyse du modèle :", model_name, "\n")
  partial_result <- analyse_modele_ggplot(
    model = model,
    data = data_for_analysis,
    p = n_va,
    filename = paste0(model_name, "_ROC.pdf")
  )
  resultats[[model_name]] <- partial_result
}
# Analyse du modèle : model_full 
#     True
# Pred   0   1
#    0 247  39
#    1  46 268
# Erreur d'apprentissage avec seuil de Bayes (0.5) : 0.1416667 
# Seuil minimisant l'erreur : 0.3623624 
# Seuil 95% : 0.2972973 
# AUC : 0.9259152 
# Sauvegardé dans model_full_ROC.pdf 
# Analyse du modèle : model_pca 
#     True
# Pred   0   1
#    0 250  38
#    1  43 269
# Erreur d'apprentissage avec seuil de Bayes (0.5) : 0.135 
# Seuil minimisant l'erreur : 0.4894895 
# Seuil 95% : 0.3073073 
# AUC : 0.919823 
# Sauvegardé dans model_pca_ROC.pdf 
# Analyse du modèle : model_aic 
#     True
# Pred   0   1
#    0 245  38
#    1  48 269
# Erreur d'apprentissage avec seuil de Bayes (0.5) : 0.1433333 
# Seuil minimisant l'erreur : 0.4424424 
# Seuil 95% : 0.2882883 
# AUC : 0.9254817 
# Sauvegardé dans model_aic_ROC.pdf 
# Analyse du modèle : model_lasso 
#     True
# Pred   0   1
#    0 245  34
#    1  48 273
# Erreur d'apprentissage avec seuil de Bayes (0.5) : 0.1366667 
# Seuil minimisant l'erreur : 0.4644645 
# Seuil 95% : 0.3683684 
# AUC : 0.9330636 
# Sauvegardé dans model_lasso_ROC.pdf 
# Analyse du modèle : model_ridge 
#     True
# Pred   0   1
#    0 247  39
#    1  46 268
# Erreur d'apprentissage avec seuil de Bayes (0.5) : 0.1416667 
# Seuil minimisant l'erreur : 0.3623624 
# Seuil 95% : 0.2972973 
# AUC : 0.9259152 
# Sauvegardé dans model_ridge_ROC.pdf 
# Analyse du modèle : model_svm_lin 
#     True
# Pred   0   1
#    0 235  24
#    1  58 283
# Erreur d'apprentissage avec seuil de Bayes (0.5) : 0.1366667 
# Seuil minimisant l'erreur : 0.5485485
# Seuil 95% : 0.4534535 
# AUC : 0.9329635 
# Sauvegardé dans model_svm_lin_ROC.pdf 
# Analyse du modèle : model_svm_poly 
#     True
# Pred   0   1
#    0 201   7
#    1  92 300
# Erreur d'apprentissage avec seuil de Bayes (0.5) : 0.165 
# Seuil minimisant l'erreur : 0.5305305 
# Seuil 95% : 0.5205205 
# AUC : 0.941079 
# Sauvegardé dans model_svm_poly_ROC.pdf 
resultats
# $model_full
# $model_full$perf_rocr
# A performance instance
# 'False positive rate' vs. 'True positive rate' (alpha: 'Cutoff')
# with 601 data points
# $model_full$x95
# [1] 0.2935154
# $model_full$y95
# [1] 0.9511401
# $model_full$seuil95
# [1] 0.2972973
# $model_full$auc
# [1] 0.9259152

# $model_pca
# $model_pca$perf_rocr
# A performance instance
# 'False positive rate' vs. 'True positive rate' (alpha: 'Cutoff')
# with 601 data points
# $model_pca$x95
# [1] 0.3071672
# $model_pca$y95
# [1] 0.9511401
# $model_pca$seuil95
# [1] 0.3073073
# $model_pca$auc
# [1] 0.919823

# $model_aic
# $model_aic$perf_rocr
# A performance instance
# 'False positive rate' vs. 'True positive rate' (alpha: 'Cutoff')
# with 601 data points
# $model_aic$x95
# [1] 0.2832765
# $model_aic$y95
# [1] 0.9511401
# $model_aic$seuil95
# [1] 0.2882883
# $model_aic$auc
# [1] 0.9254817

# $model_lasso
# $model_lasso$perf_rocr
# A performance instance
# 'False positive rate' vs. 'True positive rate' (alpha: 'Cutoff')
# with 601 data points
# $model_lasso$x95
# [1] 0.2389078
# $model_lasso$y95
# [1] 0.9511401
# $model_lasso$seuil95
# [1] 0.3683684
# $model_lasso$auc
# [1] 0.9330636

# $model_ridge
# $model_ridge$perf_rocr
# A performance instance
# 'False positive rate' vs. 'True positive rate' (alpha: 'Cutoff')
# with 601 data points
# $model_ridge$x95
# [1] 0.2935154
# $model_ridge$y95
# [1] 0.9511401
# $model_ridge$seuil95
# [1] 0.2972973
# $model_ridge$auc
# [1] 0.9259152

# $model_svm_lin
# $model_svm_lin$perf_rocr
# A performance instance
# 'False positive rate' vs. 'True positive rate' (alpha: 'Cutoff')
# with 601 data points
# $model_svm_lin$x95
# [1] 0.225256
# $model_svm_lin$y95
# [1] 0.9511401
# $model_svm_lin$seuil95
# [1] 0.5205205
# $model_svm_lin$auc
# [1] 0.9329635

# $model_svm_poly
# $model_svm_poly$perf_rocr
# A performance instance
# 'False positive rate' vs. 'True positive rate' (alpha: 'Cutoff')
# with 601 data points
# $model_svm_poly$x95
# [1] 0.225256
# $model_svm_poly$y95
# [1] 0.9511401
# $model_svm_poly$seuil95
# [1] 0.5205205
# $model_svm_poly$auc
# [1] 0.941079

# Regrouper toutes les courbes ROC pour un seul plot
roc_data_list <- lapply(names(resultats), function(mn) {
  perf_rocr <- resultats[[mn]]$perf_rocr
  df <- data.frame(
    fpr = unlist(perf_rocr@x.values),
    tpr = unlist(perf_rocr@y.values),
    model = mn
  )
  return(df)
})
roc_data_all <- do.call(rbind, roc_data_list)
seuil_95_df <- data.frame(
  x = unlist(lapply(resultats, function(res) res$x95)),
  y = unlist(lapply(resultats, function(res) res$y95)),
  model = names(resultats)
)
# Construire un label de modèle avec seuil 95%
model_labels <- sapply(names(resultats), function(mn) {
  seuil <- resultats[[mn]]$seuil95
  auc <- resultats[[mn]]$auc
  paste0(mn, "\n- seuil 95% = ", round(seuil, 2), "\n- AUC = ", round(auc, 3))
})
# On remplace le nom du modèle par ce label dans les données
roc_data_all$model_label <- factor(roc_data_all$model, levels = names(resultats), labels = model_labels)
seuil_95_df$model_label <- factor(seuil_95_df$model, levels = names(resultats), labels = model_labels)
# Graphique ROC combiné sans annotations de texte sur le plot
roc_combined_plot <- ggplot(roc_data_all, aes(x = fpr, y = tpr, color = model_label)) +
  geom_line(size = 1) +
  geom_abline(slope = 1, intercept = 0, linetype = "dashed", color = "gray") +
  geom_point(data = seuil_95_df, aes(x = x, y = y, color = model_label), size = 3) +
  labs(
    x = "Taux de faux positifs (1 - spécificité)",
    y = "Sensibilité (rappel)",
    title = "Courbes ROC comparées",
    color = "Modèles"
  ) +
  theme_minimal()
roc_combined_plot
ggsave(file.path(directory, "roc_combined.pdf"), plot = roc_combined_plot, width = 8, height = 6)



##################
## 6 : Erreurs échantillons d'apprentissage et de test, choix du modèle
##################
# Écrire les modèles pour les données test (pas utilisés mais ça donne d'autres modèles sur d'autres données)
# modèle full pour les données test
model_full_test <- glm(y ~ ., data = df_test[,-p], family = binomial)
summary(model_full_test)
# Call:
# glm(formula = y ~ ., family = binomial, data = df_test[, -p])
# Coefficients:
#                     Estimate Std. Error z value Pr(>|z|)  
# (Intercept)     -1.160e+01  1.211e+01  -0.958   0.3379  
# Area             6.372e-04  3.514e-04   1.813   0.0698 .
# MajorAxisLength -4.597e-02  3.631e-02  -1.266   0.2055  
# MinorAxisLength  5.007e-02  4.935e-02   1.015   0.3103  
# Eccentricity     1.644e+01  6.996e+00   2.351   0.0187 *
# ConvexArea      -7.117e-04  3.367e-04  -2.114   0.0345 *
# Extent           9.023e+00  5.694e+00   1.585   0.1130  
# Perimeter        5.837e-03  1.309e-02   0.446   0.6557  
# ---
# Signif. codes:  0 ‘***' 0.001 ‘**' 0.01 ‘*' 0.05 ‘.' 0.1 ‘ ' 1
# (Dispersion parameter for binomial family taken to be 1)
# Null deviance: 415.23  on 299  degrees of freedom
# Residual deviance: 176.03  on 292  degrees of freedom
# AIC: 192.03
# Number of Fisher Scoring iterations: 8

# modèle PCA pour les données test
df_pca_test <- data.frame(res_pca_test$ind$coord[, 1:2], y = df_test$y)
model_pca_test <- glm(y ~ ., data = df_pca_test[,-p], family = binomial)
summary(model_pca_test)
# Call:
# glm(formula = y ~ ., family = binomial, data = df_pca_test[,-p])
# Coefficients:
#             Estimate Std. Error z value Pr(>|z|)    
# (Intercept)  -0.7160     0.2168  -3.303 0.000957 ***
# Dim.1        -1.5921     0.1955  -8.145  3.8e-16 ***
# Dim.2         0.5943     0.1859   3.197 0.001389 ** 
# ---
# Signif. codes:  0 ‘***' 0.001 ‘**' 0.01 ‘*' 0.05 ‘.' 0.1 ‘ ' 1
# (Dispersion parameter for binomial family taken to be 1)
# Null deviance: 415.23  on 299  degrees of freedom
# Residual deviance: 193.43  on 297  degrees of freedom
# AIC: 199.43
# Number of Fisher Scoring iterations: 6

# modèle AIC pour les données test
model_aic_test <- stepAIC(model_full_test)
# Start:  AIC=192.03
# y ~ Area + MajorAxisLength + MinorAxisLength + Eccentricity + ConvexArea + Extent + Perimeter
#                   Df Deviance    AIC
# - Perimeter        1   176.23 190.23
# - MinorAxisLength  1   177.13 191.13
# - MajorAxisLength  1   177.63 191.63
# <none>                 176.03 192.03
# - Extent           1   178.63 192.63
# - Area             1   179.52 193.52
# - Eccentricity     1   180.21 194.21
# - ConvexArea       1   180.85 194.85
# Step:  AIC=190.23
# y ~ Area + MajorAxisLength + MinorAxisLength + Eccentricity + ConvexArea + Extent
#                   Df Deviance    AIC
# - MajorAxisLength  1   178.03 190.03
# <none>                 176.23 190.23
# - MinorAxisLength  1   178.32 190.32
# - Extent           1   178.69 190.69
# - Eccentricity     1   180.33 192.33
# - Area             1   183.37 195.37
# - ConvexArea       1   186.25 198.25
# Step:  AIC=190.03
# y ~ Area + MinorAxisLength + Eccentricity + ConvexArea + Extent
#                   Df Deviance    AIC
# <none>                 178.03 190.03
# - Extent           1   180.87 190.87
# - Eccentricity     1   181.03 191.03
# - Area             1   183.74 193.74
# - MinorAxisLength  1   184.77 194.77
# - ConvexArea       1   192.10 202.10
summary(model_aic_test)
# Call:
# glm(formula = y ~ Area + MinorAxisLength + Eccentricity + ConvexArea + Extent, family = binomial, data = df_test[, -p])
# Coefficients:
#                   Estimate Std. Error z value Pr(>|z|)    
# (Intercept)     -2.143e+01  9.946e+00  -2.154 0.031203 *  
# Area             4.379e-04  1.964e-04   2.229 0.025802 *  
# MinorAxisLength  9.948e-02  3.533e-02   2.815 0.004871 ** 
# Eccentricity     1.364e+01  6.946e+00   1.964 0.049552 *  
# ConvexArea      -6.725e-04  1.945e-04  -3.457 0.000546 ***
# Extent           9.109e+00  5.528e+00   1.648 0.099355 .  
# ---
# Signif. codes:  0 ‘***' 0.001 ‘**' 0.01 ‘*' 0.05 ‘.' 0.1 ‘ ' 1
# (Dispersion parameter for binomial family taken to be 1)
# Null deviance: 415.23  on 299  degrees of freedom
# Residual deviance: 178.03  on 294  degrees of freedom
# AIC: 190.03
# Number of Fisher Scoring iterations: 7

# modèle Lasso pour les données test
x <- model.matrix(y ~ ., data = df_test[,-p])
cv_lasso <- cv.glmnet(x, df_test$y, family = "binomial", alpha = 1)
selected_vars_lasso <- rownames(coef_lasso)[coef_lasso[, 1] != 0]
selected_vars_lasso <- selected_vars_lasso[selected_vars_lasso != "(Intercept)"]  # on enlève l'intercept
formula_lasso <- as.formula(paste("y ~", paste(selected_vars_lasso, collapse = " + ")))
model_lasso_test <- glm(formula_lasso, data = df_test[,-p], family = binomial)
summary(model_lasso_test)
# Call:
# glm(formula = formula_lasso, family = binomial, data = df_test[,-p])
# Coefficients:
#                     Estimate Std. Error z value Pr(>|z|)  
# (Intercept)     -8.555e+00  1.176e+01  -0.727   0.4669  
# Area            -5.523e-05  1.208e-04  -0.457   0.6477  
# MajorAxisLength -1.100e-02  3.195e-02  -0.344   0.7306  
# MinorAxisLength  7.338e-02  4.755e-02   1.543   0.1228  
# Eccentricity     1.516e+01  6.840e+00   2.216   0.0267 *
# Extent           9.281e+00  5.562e+00   1.669   0.0952 .
# Perimeter       -1.726e-02  7.567e-03  -2.280   0.0226 *
# ---
# Signif. codes:  0 ‘***' 0.001 ‘**' 0.01 ‘*' 0.05 ‘.' 0.1 ‘ ' 1
# (Dispersion parameter for binomial family taken to be 1)
# Null deviance: 415.23  on 299  degrees of freedom
# Residual deviance: 180.85  on 293  degrees of freedom
# AIC: 194.85
# Number of Fisher Scoring iterations: 8

# modèle Ridge pour les données test
x <- model.matrix(y ~ ., data = df_test[,-p])
cv_ridge <- cv.glmnet(x, df_test$y, family = "binomial", alpha = 0)  
selected_vars_ridge <- rownames(coef_ridge)[coef_ridge[, 1] != 0]
selected_vars_ridge <- selected_vars_ridge[selected_vars_ridge != "(Intercept)"]
formula_ridge <- as.formula(paste("y ~", paste(selected_vars_ridge, collapse = " + ")))
model_ridge_test <- glm(formula_ridge, data = df_test[,-p], family = binomial)
summary(model_ridge_test)
# Call:
# glm(formula = formula_ridge, family = binomial, data = df_test[,-p])
# Coefficients:
#                     Estimate Std. Error z value Pr(>|z|)  
# (Intercept)     -1.160e+01  1.211e+01  -0.958   0.3379  
# Area             6.372e-04  3.514e-04   1.813   0.0698 .
# MajorAxisLength -4.597e-02  3.631e-02  -1.266   0.2055  
# MinorAxisLength  5.007e-02  4.935e-02   1.015   0.3103  
# Eccentricity     1.644e+01  6.996e+00   2.351   0.0187 *
# ConvexArea      -7.117e-04  3.367e-04  -2.114   0.0345 *
# Extent           9.023e+00  5.694e+00   1.585   0.1130  
# Perimeter        5.837e-03  1.309e-02   0.446   0.6557  
# ---
# Signif. codes:  0 ‘***' 0.001 ‘**' 0.01 ‘*' 0.05 ‘.' 0.1 ‘ ' 1
# (Dispersion parameter for binomial family taken to be 1)
# Null deviance: 415.23  on 299  degrees of freedom
# Residual deviance: 176.03  on 292  degrees of freedom
# AIC: 192.03
# Number of Fisher Scoring iterations: 8


# (données normalisée, car normalisation pas prise en compte dans tune)
X <- scale(df_test[ , -which(names(df_test) %in% c("y", "Class"))])
df_test_scaled <- as.data.frame(X)
df_test_scaled$y <- df_test$y

# Modèle SVM linéaire pour les données de test
# Validation croisée pour choisir le meilleur cost 
tune_results <- tune(svm, y ~ ., data = df_test_scaled, kernel = 'linear', ranges = list(cost = test_cost), probability = TRUE)
summary(tune_results)
# Parameter tuning of ‘svm':
# - sampling method: 10-fold cross validation 
# - best parameters:
# cost
# 0.01
# - best performance: 0.11
# - Detailed performance results:
#    cost     error dispersion
# 1 1e-02 0.1100000 0.07036062
# 2 1e-01 0.1200000 0.07403703
# 3 1e+00 0.1300000 0.06929985
# 4 5e+00 0.1333333 0.06666667
# 5 1e+01 0.1433333 0.06675920
# 6 1e+02 0.1500000 0.06712803
best_cost_lin <- tune_results$best.parameters$cost
cat("Meilleur coût sélectionné : ", best_cost_lin, "\n") # 0.01
model_svm_lin_test <- tune_results$best.model
summary(model_svm_lin_test)
# Call:
# best.tune(METHOD = svm, train.x = y ~ ., data = df_test_scaled, ranges = list(cost = test_cost), kernel = "linear", probability = TRUE)
# Parameters:
# SVM-Type:  C-classification 
# SVM-Kernel:  linear 
# cost:  0.01 
# Number of Support Vectors:  163
# ( 81 82 )
# Number of Classes:  2 
# Levels: 
# Besni Kecimen

# Modèle SVM polynomial pour les données de test
# Validation croisée pour choisir le meilleur cost
tune_results <- tune(svm, y ~ ., data = df_test_scaled, kernel = 'polynomial', ranges = list(cost = test_cost), probability = TRUE)
summary(tune_results)
# Parameter tuning of ‘svm':
# - sampling method: 10-fold cross validation 
# - best parameters:
# cost
# 100
# - best performance: 0.1516667
# - Detailed performance results:
#   cost     error dispersion
# 1 1e-02 0.2933333 0.13407203
# 2 1e-01 0.2166667 0.13810892
# 3 1e+00 0.2000000 0.10423146
# 4 5e+00 0.1733333 0.08999314
# 5 1e+01 0.1733333 0.08720630
# 6 1e+02 0.1566667 0.08895831
best_cost_poly <- tune_results$best.parameters$cost
cat("Meilleur coût sélectionné : ", best_cost_poly, "\n") # 100
model_svm_poly_test <- tune_results$best.model
summary(model_svm_poly_test)
# Call:
# best.tune(METHOD = svm, train.x = y ~ ., data = df_test_scaled, ranges = list(cost = test_cost), kernel = "polynomial", probability = TRUE)
# Parameters:
# SVM-Type:  C-classification 
# SVM-Kernel:  polynomial 
# cost:  100 
# degree:  3 
# coef.0:  0 
# Number of Support Vectors:  134
# ( 67 67 )
# Number of Classes:  2 
# Levels: 
# Besni Kecimen


# Fonctions qui trace les différents graphiques pour chaque modèle
erreur_app_test_modele <- function(model_app, data_app, model_test, data_test, p) {
  seuil_bayes <- 0.5

  # Prédictions pour le modèle d'apprentissage : Gestion spéciale pour SVM
  if ("svm" %in% class(model_app)) {
    pred <- predict(model_app, data_app, probability = TRUE)
    predproba_app <- attr(pred, "probabilities")[, "Kecimen"]    # Cas binaire : il faut centrer pour avoir des valeurs compatibles ROC
    predproba_app <- as.numeric(predproba_app)
  } else {
    predproba_app <- predict(model_app, newdata = data_app, type = "response")
  }
  # Calcul de l'erreur d'apprentissage
  Y_pred_bayes_app <- as.numeric(predproba_app > seuil_bayes)
  data_app$y_num <- as.numeric(data_app[,p] == "Kecimen")
  conf_bayes_app <- table(Pred = Y_pred_bayes_app, True = data_app$y_num)
  print(conf_bayes_app)
  err_bayes_app <- mean(Y_pred_bayes_app != data_app$y_num)
  cat("Erreur d'apprentissage avec seuil de Bayes (0.5) :", err_bayes_app, "\n")

  # Prédictions pour le modèle de test : Gestion spéciale pour SVM
  if ("svm" %in% class(model_test)) {
    pred_test <- predict(model_test, data_test, probability = TRUE)
    predproba_test <- attr(pred_test, "probabilities")[, "Kecimen"]    # Cas binaire : il faut centrer pour avoir des valeurs compatibles ROC
    predproba_test <- as.numeric(predproba_test)
  } else {
    predproba_test <- predict(model_test, newdata = data_test, type = "response")
  }
  # Calcul de l'erreur de test
  Y_pred_bayes_test <- as.numeric(predproba_test > seuil_bayes)
  data_test$y_num <- as.numeric(data_test[,p] == "Kecimen")
  conf_bayes_test <- table(Pred = Y_pred_bayes_test, True = data_test$y_num)
  print(conf_bayes_test)
  err_bayes_test <- mean(Y_pred_bayes_test != data_test$y_num)
  cat("Erreur de test avec seuil de Bayes (0.5) :", err_bayes_test, "\n")
}

# On calcul les erreurs d'apprentissage et de test pour chaque modèle
for (model_name in names(models)) {
  model_app <- models[[model_name]]
  model_test <- models[[model_name]]
  # model_test <- get(paste0(model_name, "_test"))

  # Choix des données selon le modèle
  data_app <- df_app
  data_test <- df_test
  n_va <- ncol(df_app)
  if (model_name == "model_pca") {
    data_app <- df_pca_app
    data_test <- df_pca_test
    n_va <- ncol(df_pca_app)
  } else if ("svm" %in% class(model_app)) {
    data_app <- df_app_scaled
    data_test <- df_test_scaled
    n_va <- ncol(df_app_scaled)
  }
  cat("Analyse du modèle :", model_name, "\n")
  erreur_app_test_modele(
    model_app = model_app,
    data_app = data_app,
    model_test = model_test,
    data_test = data_test,
    p = n_va
  )
}
# Analyse du modèle : model_full 
#     True
# Pred   0   1
#    0 247  39
#    1  46 268
# Erreur d'apprentissage avec seuil de Bayes (0.5) : 0.1416667 
#     True
# Pred   0   1
#    0 132  17
#    1  25 126
# Erreur de test avec seuil de Bayes (0.5) : 0.14
# Analyse du modèle : model_pca 
#     True
# Pred   0   1
#    0 250  38
#    1  43 269
# Erreur d'apprentissage avec seuil de Bayes (0.5) : 0.135 
#     True
# Pred   0   1
#    0 128   6
#    1  29 137
# Erreur de test avec seuil de Bayes (0.5) : 0.1166667
# Analyse du modèle : model_aic 
#     True
# Pred   0   1
#    0 245  38
#    1  48 269
# Erreur d'apprentissage avec seuil de Bayes (0.5) : 0.1433333 
#     True
# Pred   0   1
#    0 131  18
#   1  26 125
# Erreur de test avec seuil de Bayes (0.5) : 0.1466667 
# Analyse du modèle : model_lasso 
#     True
# Pred   0   1
#    0 245  34
#    1  48 273
# Erreur d'apprentissage avec seuil de Bayes (0.5) : 0.1366667 
#      True
# Pred   0   1
#    0 130  14
#    1  27 129
# Erreur de test avec seuil de Bayes (0.5) : 0.1366667 
# Analyse du modèle : model_ridge 
#     True
# Pred   0   1
#    0 247  39
#    1  46 268
# Erreur d'apprentissage avec seuil de Bayes (0.5) : 0.1416667 
#     True
# Pred   0   1
#    0 132  17
#    1  25 126
# Erreur de test avec seuil de Bayes (0.5) : 0.14 
# Analyse du modèle : model_svm_lin 
#     True
# Pred   0   1
#    0 293   0
#    1   0 307
# Analyse du modèle : model_svm_lin 
#     True
# Pred   0   1
#    0 235  24
#    1  58 283
# Erreur d'apprentissage avec seuil de Bayes (0.5) : 0.1366667 
#     True
# Pred   0   1
#    0 124   7
#    1  33 136
# Erreur de test avec seuil de Bayes (0.5) : 0.1333333 
# Analyse du modèle : model_svm_poly 
#     True
# Pred   0   1
#    0 201   7
#    1  92 300
# Erreur d'apprentissage avec seuil de Bayes (0.5) : 0.165 
#     True
# Pred   0   1
#    0 106   2
#    1  51 141
# Erreur de test avec seuil de Bayes (0.5) : 0.1766667 

# Choix du meilleur modèle selon les paramètres de performance : erreur d'apprentissage et de test, AIC, SCR (null deviance) : 
# model ridge le mieux (plus petite erreurs et quasiment le meilleur ROC et seuil de confiance à 95%)
# Modèle PCA : seuil 95% bas (pas bcp de faux positifs) et des erreurs plus faibles que le reste 
# SVM polynomial avec des erreurs plus fortes que les autres d'où le choix douteux de l'énoncé
# quasiment toujours des erreurs de tests < aux erreurs d'app : bizarre mais surement du aux manques de données 


####################################
####################################
## Partie III : Focus sur l'analyse discriminante
####################################
####################################
##################
## 1 : Analyse discriminante des deux premières composantes principales des données d'apprentissage
##################
directory <- "Model_Choice"
dir.create(directory, showWarnings = FALSE)


## --a : Modèle et frontière de décision
# Modèle LDA : 
# On suppose que X|Y=k ~ N(μ_k, Σ) avec Σ commun à toutes les classes.
# La frontière de décision est linéaire, et s'écrit entre deux classes k1 et k2 :
# f(x) = xᵗ Σ⁻¹ (μ₁ - μ₂) - 0.5 (μ₁ᵗ Σ⁻¹ μ₁ - μ₂ᵗ Σ⁻¹ μ₂) + log(π₁ / π₂)

X <- as.matrix(df_pca_app[, 1:2])
y <- df_pca_app[,3]
classes <- levels(y)
# Moyennes de chaque classe
mu1 <- colMeans(X[y == classes[1], ])
mu2 <- colMeans(X[y == classes[2], ])
# Matrice de covariance commune
Sigma <- cov(X)
# Inversion
Sigma_inv <- solve(Sigma)
# Coefficients linéaires
a <- Sigma_inv %*% (mu1 - mu2)
b <- -0.5 * t(mu1 + mu2) %*% a
cat("Coefficients de la droite de séparation :\n")
print(a)
# Dim.1  0.5907528
# Dim.2 -0.2066080
cat("Ordonnée à l'origine :\n")
print(b) # -0.02037847


## --b : Ajout théorique
# Diagonalisation de Σ : Σ = QΛQᵗ
eig <- eigen(Sigma)
Q <- eig$vectors
Lambda <- eig$values
# Inversion via diagonalisation
Sigma_inv_theo <- Q %*% diag(1 / Lambda) %*% t(Q)
a_theo <- Sigma_inv_theo %*% (mu1 - mu2)
b_theo <- as.numeric(-0.5 * t(mu1 + mu2) %*% a)
# Coefficients linéaires
cat("Coefficients de la droite de séparation (sans inversion de matrice) :\n")
print(a)
# Dim.1  0.5907528
# Dim.2 -0.2066080
cat("Ordonnée à l'origine (sans inversion de matrice) :\n")
print(b) # -0.02037847
# on obtient bien les mêmes résultats 


## --c : Points d'apprentissage et frontière de décision 
# Calcul de la frontière
slope <- -a[1] / a[2]
intercept <- -b / a[2]
x_vals <- seq(min(X[,1]), max(X[,1]), length.out = 200)
decision_line <- data.frame(
  x = x_vals,
  y = slope * x_vals + c(intercept)
)
x_min <- 1.3 * min(df_pca_app_plot$x2)
x_max <- 1.3 * max(df_pca_app_plot$x2)
decision_line <- decision_line[decision_line$y >= x_min & decision_line$y <= x_max, ]

lda_pca_plot <- ggplot(df_pca_app_plot, aes(x = x1, y = x2, color = y)) +
  geom_point(size = 2) +
  geom_line(data = decision_line, aes(x = x, y = y), color = "black", size = 1) +
  labs(title = "Projection des individus sur les 2 premiers axes ACP", x = "PC1", y = "PC2", color = "Classe") +
  theme_minimal()
lda_pca_plot
ggsave(file.path(directory, "hand_lda_pca_projection_app.pdf"), plot = lda_pca_plot, width = 8, height = 6)


## --d : Erreur de classification 
# Prédiction manuelle via discriminant linéaire
X_test <- as.matrix(df_pca_test[, 1:2])
y_test <- df_pca_test[, 3]
# Fonction discriminante
disc_f <- function(x) as.numeric(t(a) %*% x + b)
# Prédictions : > 0 -> classe 1, sinon classe 2
y_pred_test <- ifelse(apply(X_test, 1, disc_f) > 0, classes[1], classes[2])
y_pred_test <- factor(y_pred_test, levels = levels(y_test))
# Matrice de confusion et erreur
conf_matrix <- table(Pred = y_pred_test, True = y_test)
err_test <- mean(y_pred_test != y_test)
cat("Matrice de confusion sur test :\n")
print(conf_matrix)
#          True
# Pred      Besni Kecimen
#   Besni     120       6
#   Kecimen    37     137
cat("Erreur de classification test : ", round(err_test, 4), "\n") # 0.1433


##################
## 2 : Courbe ROC et analyse discriminante fonctions R
##################
lda_model_pca <- lda(y ~ ., data = df_pca_app[,-4])
lda_model_pca
# Call:
# lda(y ~ ., data = df_pca_app[,-4])
# Prior probabilities of groups:
#   Besni   Kecimen 
# 0.4883333 0.5116667 
# Group means:
#             Dim.1      Dim.2
# Besni    1.458213 -0.1563245
# Kecimen -1.391715  0.1491957
# Coefficients of linear discriminants:
# LD1
# Dim.1 -0.5953096
# Dim.2  0.2082017

directory <- "Courbes_ROC"
dir.create(directory, showWarnings = FALSE)

cat("Analyse du modèle lda sur les deux premières composantes principales \n")
partial_result <- analyse_modele_ggplot(
  model = lda_model_pca,
  data = df_pca_app,
  p = ncol(df_pca_app),
  filename = "model_lda_pca_ROC.pdf"
)
#     True
# Pred   0   1
#.   0 230  27
#.   1  63 280
# Erreur d'apprentissage avec seuil de Bayes (0.5) : 0.15 
# Seuil minimisant l'erreur : 0.5635636 
# Seuil 95% : 0.4234234 
# AUC : 0.9196896
# Sauvegardé dans model_lda_pca_ROC.pdf 

seuil_bayes <- 0.5
# Prédictions sur les données d'apprentissage
pred_app <- predict(lda_model_pca, newdata = df_pca_app)
predproba_app <- pred_app$posterior[, "Kecimen"]  # Proba d'appartenir à la classe "Kecimen"
Y_pred_bayes_app <- as.numeric(predproba_app > seuil_bayes)
df_pca_app$y_num <- as.numeric(df_pca_app[,3] == "Kecimen")
conf_bayes_app <- table(Pred = Y_pred_bayes_app, True = df_pca_app$y_num)
err_bayes_app <- mean(Y_pred_bayes_app != df_pca_app$y_num)

# AIC et BIC : informations supplémentaires sur la qualité du modèle
n <- nrow(df_pca_app)
k <- length(unique(df_pca_app$y)) # nombre de classes
p_lda <- ncol(df_pca_app) - 1 # nb variables explicatives
nb_param <- k * p_lda + (k - 1) # approx : moyennes + proportions
logLik_lda <- sum(log(pred_app$posterior[cbind(1:n, match(df_pca_app$y, colnames(pred_app$posterior)))]))
AIC_lda <- -2 * logLik_lda + 2 * nb_param
cat("AIC :", AIC_lda, "\n") # 477.1779
BIC_lda <- -2 * logLik_lda + log(n) * nb_param
cat("BIC :", BIC_lda, "\n") # 507.9564

# Modèle sur les données de test 
lda_model_pca_test <- lda(y ~ ., data = df_pca_test[,-4])
lda_model_pca_test
# Call:
# lda(y ~ ., data = df_pca_test[,-4])
# Prior probabilities of groups:
#     Besni   Kecimen 
# 0.5233333 0.4766667 
# Group means:
#             Dim.1     Dim.2
# Besni    1.450527 -0.201702
# Kecimen -1.592537  0.221449
# Coefficients of linear discriminants:
# LD1
# Dim.1 -0.6219562
# Dim.2  0.3008066
pred_test <- predict(lda_model_pca, newdata = df_pca_test)
predproba_test <- pred_test$posterior[, "Kecimen"]  # Proba d'appartenir à la classe "Kecimen"
Y_pred_bayes_test <- as.numeric(predproba_test > seuil_bayes)
df_pca_test$y_num <- as.numeric(df_pca_test[,3] == "Kecimen")
conf_bayes_test <- table(Pred = Y_pred_bayes_test, True = df_pca_test$y_num)
err_bayes_test <- mean(Y_pred_bayes_test != df_pca_test$y_num)

# Affichage des résultats 
cat("Analyse du modèle LDA :\n")
print(conf_bayes_app)
#     True
# Pred   0   1
#    0 230  27
#    1  63 280
cat("Erreur d'apprentissage (seuil 0.5) :", err_bayes_app, "\n") # 0.15
print(conf_bayes_test)
#     True
# Pred   0   1
#    0 119   6
#    1  38 137
cat("Erreur de test (seuil 0.5) :", err_bayes_test, "\n") # 0.1466667 


# LDA moins flexible (donc potentiellement plus biaisée) que QDA
# mais moins de variance (donc peut améliorer la prédiction si on n'a peu d'observations)
# en modèle d'analyse discriminante quadratique
qda_model_pca <- qda(y ~ ., data = df_pca_app[,-4])
qda_model_pca
# Call:
# qda(y ~ ., data = df_pca_app[, -4])
# Prior probabilities of groups:
#     Besni   Kecimen 
# 0.4883333 0.5116667 
# Group means:
#             Dim.1      Dim.2
# Besni    1.458213 -0.1563245
# Kecimen -1.391715  0.1491957

cat("Analyse du modèle qda sur les deux premières composantes principales \n")
partial_result <- analyse_modele_ggplot(
  model = qda_model_pca,
  data = df_pca_app,
  p = ncol(df_pca_app),
  filename = "model_qda_pca_ROC.pdf"
)
#     True
# Pred   0   1
#    0 215  21
#    1  78 286
# Erreur d'apprentissage avec seuil de Bayes (0.5) : 0.165 
# Seuil minimisant l'erreur : 0.5705706
# Seuil 95% : 0.4324324 
# AUC : 0.9125302 
# Sauvegardé dans model_lda_lin_pca_ROC.pdf 

seuil_bayes <- 0.5
# Prédictions sur les données d'apprentissage
pred_app <- predict(qda_model_pca, newdata = df_pca_app)
predproba_app <- pred_app$posterior[, "Kecimen"]  # Proba d'appartenir à la classe "Kecimen"
Y_pred_bayes_app <- as.numeric(predproba_app > seuil_bayes)
df_pca_app$y_num <- as.numeric(df_pca_app[,3] == "Kecimen")
conf_bayes_app <- table(Pred = Y_pred_bayes_app, True = df_pca_app$y_num)
err_bayes_app <- mean(Y_pred_bayes_app != df_pca_app$y_num)

# AIC et BIC : informations supplémentaires sur la qualité du modèle
n <- nrow(df_pca_app)
k <- length(unique(df_pca_app$y)) # nombre de classes
p_lda <- ncol(df_pca_app) - 1 # nb variables explicatives
nb_param <- k * p_lda + (k - 1) # approx : moyennes + proportions
logLik_lda <- sum(log(pred_app$posterior[cbind(1:n, match(df_pca_app$y, colnames(pred_app$posterior)))]))
AIC_lda <- -2 * logLik_lda + 2 * nb_param
cat("AIC :", AIC_lda, "\n") # 503.7311 
BIC_lda <- -2 * logLik_lda + log(n) * nb_param
cat("BIC :", BIC_lda, "\n") # 534.5096

# Modèle sur les données de test 
qda_model_pca_test <- qda(y ~ ., data = df_pca_test[,-4])
qda_model_pca_test
# Call:
# qda(y ~ ., data = df_pca_test[,-4])
# Prior probabilities of groups:
#     Besni   Kecimen 
# 0.5233333 0.4766667 
# Group means:
#             Dim.1     Dim.2
# Besni    1.450527 -0.201702
# Kecimen -1.592537  0.221449
pred_test <- predict(qda_model_pca, newdata = df_pca_test)
predproba_test <- pred_test$posterior[, "Kecimen"]  # Proba d'appartenir à la classe "Kecimen"
Y_pred_bayes_test <- as.numeric(predproba_test > seuil_bayes)
df_pca_test$y_num <- as.numeric(df_pca_test[,3] == "Kecimen")
conf_bayes_test <- table(Pred = Y_pred_bayes_test, True = df_pca_test$y_num)
err_bayes_test <- mean(Y_pred_bayes_test != df_pca_test$y_num)

# Affichage des résultats 
cat("Analyse du modèle LDA :\n")
print(conf_bayes_app)
#     True
# Pred   0   1
#    0 215  21
#    1  78 286
cat("Erreur d'apprentissage (seuil 0.5) :", err_bayes_app, "\n") # 0.165
print(conf_bayes_test)
#     True
# Pred   0   1
#    0 117   5
#    1  40 138
cat("Erreur de test (seuil 0.5) :", err_bayes_test, "\n") # 0.15
# pas forcément des meilleurs ROC que les autres modèles, et même de moins erreurs de test et d'apprentissage


##################
## 3 : Analyse discriminante avec toutes les variables
##################
# avec le module R adapté 
lda_model_lin <- lda(y ~ ., data = df_app[,-p])
lda_model_lin
# Call:
# lda(y ~ ., data = df_app[, -p])
# Prior probabilities of groups:
#     Besni   Kecimen 
# 0.4883333 0.5116667 
# Group means:
#              Area MajorAxisLength MinorAxisLength Eccentricity ConvexArea    Extent Perimeter
# Besni   111803.37        510.0224        278.3604    0.8235253  116529.61 0.6910644 1350.1456
# Kecimen  63516.27        353.8875        229.2309    0.7427146   65902.25 0.7036834  986.4739
# Coefficients of linear discriminants:
# LD1
# Area            -0.0001732454
# MajorAxisLength  0.0125006648
# MinorAxisLength  0.0064832167
# Eccentricity    -3.7405511217
# ConvexArea       0.0002121957
# Extent          -1.0272489477
# Perimeter       -0.0175756089

seuil_bayes <- 0.5
# Prédictions sur les données d'apprentissage
pred_app <- predict(lda_model_lin, newdata = df_app[,-p])
predproba_app <- pred_app$posterior[, "Kecimen"]  # Proba d'appartenir à la classe "Kecimen"
Y_pred_bayes_app <- as.numeric(predproba_app > seuil_bayes)
df_app$y_num <- as.numeric(df_app[,p] == "Kecimen")
conf_bayes_app <- table(Pred = Y_pred_bayes_app, True = df_app$y_num)
err_bayes_app <- mean(Y_pred_bayes_app != df_app$y_num)

# AIC et BIC : informations supplémentaires sur la qualité du modèle
n <- nrow(df_app)
k <- length(unique(df_app$y)) # nombre de classes
p_lda <- ncol(df_app) - 1 # nb variables explicatives
nb_param <- k * p_lda + (k - 1) # approx : moyennes + proportions
logLik_lda <- sum(log(pred_app$posterior[cbind(1:n, match(df_app$y, colnames(pred_app$posterior)))]))
AIC_lda_lin <- -2 * logLik_lda + 2 * nb_param
cat("AIC :", AIC_lda_lin, "\n") # 456.1482 
BIC_lda_lin <- -2 * logLik_lda + log(n) * nb_param
cat("BIC :", BIC_lda_lin, "\n") # 539.6899

# Modèle sur les données de test 
lda_model_lin_test <- lda(y ~ ., data = df_test[,-p])
lda_model_lin_test
# Call:
# lda(y ~ ., data = df_test[, -p])
# Prior probabilities of groups:
# Besni   Kecimen 
# 0.5233333 0.4766667 
# Group means:
#              Area MajorAxisLength MinorAxisLength Eccentricity ConvexArea    Extent Perimeter
# Besni   112925.27        507.0938        281.9812    0.8166447  116948.70 0.6915722 1344.3600
# Kecimen  63192.76        350.6516        229.6139    0.7403386   65254.34 0.7165567  977.7016
# Coefficients of linear discriminants:
# LD1
# Area             5.972261e-05
# MajorAxisLength -8.367520e-03
# MinorAxisLength -1.587902e-02
# Eccentricity    -2.532489e+00
# ConvexArea      -1.027008e-05
# Extent           2.714035e+00
# Perimeter       -5.982489e-03
pred_test <- predict(lda_model_lin, newdata = df_test[,-p])
predproba_test <- pred_test$posterior[, "Kecimen"]  # Proba d'appartenir à la classe "Kecimen"
Y_pred_bayes_test <- as.numeric(predproba_test > seuil_bayes)
df_test$y_num <- as.numeric(df_test[,p] == "Kecimen")
conf_bayes_test <- table(Pred = Y_pred_bayes_test, True = df_test$y_num)
err_bayes_test <- mean(Y_pred_bayes_test != df_test$y_num)

# Affichage des résultats 
cat("Analyse du modèle LDA :\n")
print(conf_bayes_app)
#     True
# Pred   0   1
#    0 251  41
#    1  42 266
cat("Erreur d'apprentissage (seuil 0.5) :", err_bayes_app, "\n") # 0.1383333 
print(conf_bayes_test)
#     True
# Pred   0   1
#    0 131  17
#    1  26 126
cat("Erreur de test (seuil 0.5) :", err_bayes_test, "\n") # 0.1433333 

# Seuils et initialisation
seuils <- seq(0, 1, length.out = 1000)
# Appliquer la fonction à chaque seuil
metrics <- sapply(seuils, function(s) {
  Y_pred <- as.numeric(predproba_app > s)
  FP <- sum(Y_pred == 1 & df_app$y_num == 0)
  FN <- sum(Y_pred == 0 & df_app$y_num == 1)
  VP <- sum(Y_pred == 1 & df_app$y_num == 1)
  VN <- sum(Y_pred == 0 & df_app$y_num == 0)
  err <- mean(Y_pred != df_app$y_num)
  c(FP = FP, FN = FN, FPN = FP + FN, VP = VP, VN = VN, err = err)
})
# Transposer pour avoir une matrice avec une colonne par variable
metrics <- t(metrics)
# Construire df_plot à partir de cette matrice
df_plot <- data.frame(
  seuil = seuils,
  FP = metrics[, "FP"],
  FN = metrics[, "FN"],
  FPN = metrics[, "FPN"],
  VP = metrics[, "VP"],
  VN = metrics[, "VN"],
  err = metrics[, "err"],
  sens = metrics[, "VP"] / (metrics[, "VP"] + metrics[, "FN"]),
  spec = metrics[, "VN"] / (metrics[, "VN"] + metrics[, "FP"])
)
# Taux de faux positifs, faux négatifs et erreur
seuil_optimal <- seuils[which.min(df_plot$err)]
cat("Seuil minimisant l'erreur :", seuil_optimal, "\n") # 0.4564565

# Graphique FP, FN, FPN
plot_fp_fn_err <- ggplot(df_plot, aes(x = seuil)) +
  geom_line(aes(y = FP), color = "red") +
  geom_line(aes(y = FN), color = "blue") +
  geom_line(aes(y = FPN), color = "darkgreen", linetype = "dashed") +
  annotate("text", x = 0.98, y = max(df_plot$FPN)-70, label = "Faux positifs", color = "red", hjust = 1) +
  annotate("text", x = 0.98, y = max(df_plot$FPN)-35, label = "Faux négatifs", color = "blue", hjust = 1) +
  annotate("text", x = 0.98, y = max(df_plot$FPN), label = "Faux positifs + négatifs", color = "darkgreen", hjust = 1) +
  labs(x = "Seuil", y = "Nombre d'erreurs") +
  theme_minimal()
print(plot_fp_fn_err)

# Graphique de l'erreur
plot_err <- ggplot(df_plot) +
  geom_line(aes(x = seuil, y = err), color = "darkgreen") +
  geom_point(x = seuil_optimal, y = min(df_plot$err), color = "red", size = 2) +
  annotate("text", x = seuil_optimal, y = min(df_plot$err), label = paste("min à", round(seuil_optimal, 3)), hjust = -0.1, vjust = 1, color = "red") +
  labs(x = "Seuil", y = "Erreur de classification", title = "Erreur selon Seuil") +
  theme_minimal()
print(plot_err)

# Courbe ROC
pred_rocr <- prediction(predproba_app, df_app$y_num)
perf_rocr <- performance(pred_rocr, "tpr", "fpr")
# Calcul du seuil pour sensibilité ≥ 0.95
i95 <- which(rev(df_plot$sens) >= 0.95)[1]
i95_real <- length(seuils) - i95 + 1
seuil_95 <- seuils[i95_real]
x_95 <- 1 - df_plot$spec[i95_real]
y_95 <- df_plot$sens[i95_real]
cat("Seuil 95% :", seuil_95, "\n") # 0.2932933 
  
# AUC
perf_auc <- performance(pred_rocr, "auc") # 0.9260486 
AUC <- unlist(perf_auc@y.values)
cat("AUC :", AUC, "\n")

# Construction du graphique ROC avec marquage du point
plot_roc <- ggplot() +
  geom_line(data = df_plot, aes(x = 1 - spec, y = sens), color = "blue", size = 1.5) + 
  geom_line(aes(x = unlist(perf_rocr@x.values), y = unlist(perf_rocr@y.values)), color = "darkorange", size = 0.75) +
  geom_abline(slope = 1, intercept = 0, linetype = "dashed", color = "gray") +
  geom_point(aes(x = x_95, y = y_95), color = "red", size = 3) +
  annotate("text", x = x_95, y = y_95, label = paste0("seuil 95% = ", round(seuil_95, 2)), hjust = 0, vjust = 1, color = "red") +
  annotate("text", x = 0.6, y = 0.1, label = paste0("AUC = ", round(AUC, 3)), hjust = 0, vjust = 0, size = 5, color = "black") +
  labs(x = "Taux de faux positifs (1 - spécificité)", y = "Sensibilité (rappel)", title = "Courbe ROC") +
  theme_minimal()
plot_roc

# Combine et afficher les graphiques
g_final <- plot_fp_fn_err / plot_err / plot_roc + plot_layout(guides = "collect")
print(g_final)
ggsave(file.path(directory, "model_lda_ROC.pdf"), plot = g_final, width = 5, height = 10)
# modèle équivalent pour les erreurs et les AIC, il a ici un des seuils à 95% les plus bas permettant d'enlever du faux positifs plus facilement 
# par rapport aux autres lda : un peu plus d'erreur sur le test, moins sur l'apprentissage et une meilleure ROC (la meilleur de toutes même)
# par rapport aux résultats de la P2 : équivalent 

directory <- "Model_Choice"
dir.create(directory, showWarnings = FALSE)

# création du graphique pour le LDA sur les deux premières composantes de l'ACP pour l'affichage (sur le modèle d'apprentissage)
classe_pred <- ifelse(predproba_app > 0.5, "Kecimen", "Besni")
df_plot <- data.frame(
  PC1 = acp_coords[, 1],
  PC2 = acp_coords[, 2],
  ClasseReelle = df_app$y,
  ProbaKecimen = predproba_app,
  ClassePredite = classe_pred
)
plot_model_aic <- ggplot(df_plot, aes(x = PC1, y = PC2)) +
  geom_point(aes(color = df_app$y, shape = ClassePredite, alpha = ProbaKecimen), size = 3) +
  scale_color_manual(values = c("Besni" = "blue", "Kecimen" = "red")) +
  scale_shape_manual(values = c("Besni" = 3, "Kecimen" = 16)) +
  scale_alpha_continuous(range = c(0.4, 1)) +
  labs(title = "Projection des individus sur les 2 premiers axes ACP", subtitle = "Couleur : classe réelle | Forme : classe prédite | Transparence : proba prédite", x = "PC1", y = "PC2") +
  theme_minimal()
plot_model_aic
ggsave(file.path(directory, "model_lda_projection_app.pdf"), plot_model_aic, width = 6, height = 5)


####################################
####################################
## Bonus
####################################
####################################
directory <- "Bonus_Models"
dir.create(directory, showWarnings = FALSE)

# On repart des données de base
df_app <- df[train, ]
df_test <- df[!train, ]
p = ncol(df_app)
acp_coords <- as.data.frame(res_pca_app$ind$coord[, 1:2]) 


# Random Forest
rf_model <- randomForest(x = df_app[, -p], y = as.factor(df_app[,p]))
# Affiche les prédictions sur les données d'apprentissage de manière automatique 
print(rf_model)
# Call:
# randomForest(x = df_app[, -p], y = as.factor(df_app[, p])) 
# Type of random forest: classification
# Number of trees: 500
# No. of variables tried at each split: 2
# OOB estimate of  error rate: 14%
# Confusion matrix:
#         Besni Kecimen class.error
# Besni     239      54  0.18430034
# Kecimen    30     277  0.09771987
# Pas d'AIC/BIC directement, mais car modèle non paramétrique
seuil_bayes <- 0.5
# Prédictions sur données de test
pred_test <- predict(rf_model, newdata = df_test[, -p], type = "prob")
predproba_test <- pred_test[, "Kecimen"]
Y_pred_bayes_test <- as.numeric(predproba_test > seuil_bayes)
df_test$y_num <- as.numeric(df_test[,p] == "Kecimen")
conf_bayes_test <- table(Pred = Y_pred_bayes_test, True = df_test$y_num)
err_bayes_test <- mean(Y_pred_bayes_test != df_test$y_num)
cat("Analyse modèle Random Forest :\n")
#     True
# Pred   0   1
#    0 122   4
#    1  35 139
print(conf_bayes_test)
cat("Erreur test (seuil 0.5) :", err_bayes_test, "\n") # 0.13 

# Récupération des prédictions du modèle Random Forest (sur données d'apprentissage)
classe_pred <- rf_model$predicted # prédictions directement issues de l'apprentissage
proba_rf <- rf_model$votes # probabilités pour chaque classe
# Tracé et sauvegarde du graphique 
df_plot_rf <- data.frame(
  PC1 = acp_coords[, 1],
  PC2 = acp_coords[, 2],
  ClasseReelle = df_app[, p],
  ClassePredite = classe_pred,
  ProbaKecimen = proba_rf[, "Kecimen"]  # probabilité d'appartenir à la classe "Kecimen"
)
plot_rf <- ggplot(df_plot_rf, aes(x = PC1, y = PC2)) +
  geom_point(aes(color = ClasseReelle, shape = ClassePredite, alpha = ProbaKecimen), size = 3) +
  scale_color_manual(values = c("Besni" = "blue", "Kecimen" = "red")) +
  scale_shape_manual(values = c("Besni" = 3, "Kecimen" = 16)) +
  scale_alpha_continuous(range = c(0.4, 1)) +
  labs(title = "Projection des individus sur les 2 premiers axes ACP", subtitle = "Couleur : classe réelle | Forme : classe prédite | Transparence : proba prédite", x = "PC1", y = "PC2") +
  theme_minimal()
plot_rf
ggsave(file.path(directory, "random_forest_projection_app.pdf"), plot_rf, width = 6, height = 5)


# Réseau de neurones simple
nn_model <- nnet(as.factor(df_app[, p]) ~ ., data = df_app[, -p], size = 5, maxit = 200, decay = 0.01, trace = FALSE)

# Seuil bayésien
seuil_bayes <- 0.5
# Prédictions sur données d'apprentissage
pred_nn_app <- predict(nn_model, newdata = df_app[,-p])
classe_pred_nn_app <- ifelse(pred_nn_app[, 1] > seuil_bayes, "Kecimen", "Besni")
Y_pred_app <- as.numeric(pred_nn_app[, 1]  > seuil_bayes)
df_app$y_num <- as.numeric(df_app[, p] == "Kecimen")
conf_nn_app <- table(Pred = Y_pred_app, True = df_app$y_num)
err_nn_app <- mean(Y_pred_app != df_app$y_num)
# Prédictions sur données de test
pred_nn_test <- predict(nn_model, newdata = df_test[,-p])
Y_pred_test <- as.numeric(pred_nn_test[, 1] > seuil_bayes)
df_test$y_num <- as.numeric(df_test[, p] == "Kecimen")
conf_nn_test <- table(Pred = Y_pred_test, True = df_test$y_num)
err_nn_test <- mean(Y_pred_test != df_test$y_num)
# Affichages 
cat("Analyse modèle NNET — données d'apprentissage :\n")
print(conf_nn_app)
#     True
# Pred   0   1
#    0 252  23
#    1  41 284
cat("Erreur d'apprentissage :", round(err_nn_app, 4), "\n\n") # 0.1067
cat("Analyse modèle NNET — données de test :\n")
print(conf_nn_test)
#     True
# Pred   0   1
#    0 126  11
#    1  31 132
cat("Erreur de test :", round(err_nn_test, 4), "\n") # 0.14
# Des erreurs d'apprentissage plus faibles pour le Neural Network mais on revient à la normale pour l'erreur de test

# Dataframe pour le plot (apprentissage)
df_plot_nn <- data.frame(
  PC1 = acp_coords[, 1],
  PC2 = acp_coords[, 2],
  ClasseReelle = df_app[, p],
  ClassePredite = classe_pred_nn_app,
  ProbaKecimen = pred_nn_app[, 1] 
)
# Plot
plot_nn <- ggplot(df_plot_nn, aes(x = PC1, y = PC2)) +
  geom_point(aes(color = ClasseReelle, shape = ClassePredite, alpha = ProbaKecimen), size = 3) +
  scale_color_manual(values = c("Besni" = "blue", "Kecimen" = "red")) +
  scale_shape_manual(values = c("Besni" = 3, "Kecimen" = 16)) +
  scale_alpha_continuous(range = c(0.4, 1)) +
  labs(title = "Neural Network (nnet)", x = "PC1", y = "PC2") +
  theme_minimal()
plot_nn
ggsave(file.path(directory, "neural_network_projection_app.pdf"), plot_nn, width = 6, height = 5)


# Le gradient boosting est une méthode d'apprentissage supervisé qui combine plusieurs arbres de décision faibles, chaque nouvel arbre corrigeant les erreurs des précédents. 
# Il fonctionne en minimisant une fonction de perte par descente de gradient.
library(xgboost)
# Variable binaire cible
df_app$y_num <- as.numeric(df_app[, p] == "Kecimen")
df_test$y_num <- as.numeric(df_test[, p] == "Kecimen")
# Matrices explicatives numériques (sans la variable cible)
X_app <- df_app[, setdiff(colnames(df_app), c(p, "y_num"))]
X_test <- df_test[, setdiff(colnames(df_test), c(p, "y_num"))]
X_app <- as.matrix(sapply(X_app, as.numeric))
X_test <- as.matrix(sapply(X_test, as.numeric))
# Entraînement modèle XGBoost
xgb_model <- xgboost(data = X_app, label = y_app,
            objective = "binary:logistic", nrounds = 100, max_depth = 3, eta = 0.1, verbose = 0)

# Seuil bayésien
seuil_bayes <- 0.5
# Prédictions sur données d'apprentissage
proba_xgb_app <- predict(xgb_model, newdata = X_app)
pred_xgb_app <- as.numeric(proba_xgb_app > seuil_bayes)
classe_pred_xgb_app <- ifelse(proba_xgb_app > seuil_bayes, "Kecimen", "Besni")
conf_xgb_app <- table(Pred = pred_xgb_app, True = y_app)
err_xgb_app <- mean(pred_xgb_app != y_app)
# Prédictions sur données de test
proba_xgb_test <- predict(xgb_model, newdata = X_test)
pred_xgb_test <- as.numeric(proba_xgb_test > seuil_bayes)
conf_xgb_test <- table(Pred = pred_xgb_test, True = y_test)
err_xgb_test <- mean(pred_xgb_test != y_test)

# Affichages
cat("Analyse modèle XGBoost — données d'apprentissage :\n")
print(conf_xgb_app)
#     True
# Pred   0   1
#    0 267  10
#    1  26 297
cat("Erreur d'apprentissage :", round(err_xgb_app, 4), "\n\n") # 0.06
cat("Analyse modèle XGBoost — données de test :\n")
print(conf_xgb_test)
#     True
# Pred   0   1
#    0 129   7
#    1  28 136
cat("Erreur de test :", round(err_xgb_test, 4), "\n") # 0.1167

# Dataframe pour le plot (apprentissage)
df_plot_xgb <- data.frame(
  PC1 = acp_coords[, 1],
  PC2 = acp_coords[, 2],
  ClasseReelle = df_app[, p],
  ClassePredite = classe_pred_xgb_app,
  ProbaKecimen = proba_xgb_app
)
# Plot
plot_xgb <- ggplot(df_plot_xgb, aes(x = PC1, y = PC2)) +
  geom_point(aes(color = ClasseReelle, shape = ClassePredite, alpha = ProbaKecimen), size = 3) +
  scale_color_manual(values = c("Besni" = "blue", "Kecimen" = "red")) +
  scale_shape_manual(values = c("Besni" = 3, "Kecimen" = 16)) +
  scale_alpha_continuous(range = c(0.4, 1)) +
  labs(title = "XGBoost - Projection ACP", x = "PC1", y = "PC2") +
  theme_minimal()
print(plot_xgb)
ggsave(file.path(directory, "xgboost_projection_app.pdf"), plot_xgb, width = 6, height = 5)

