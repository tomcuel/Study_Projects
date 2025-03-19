rm(list=objects())
library(xts)
library(dplyr)
library(tidyr)
library(dygraphs)
library(lubridate)
library(caret)
library(ggplot2)
library(GGally)
library(corrplot)
library(nortest)
library(scales)
library(zoo)
library(mgcv)
library(forecast)
plot_digraph <- FALSE
plot_raw_graphs <- TRUE
plot_tendance_saison <- TRUE

# Lire le fichier CSV avec moins de colonnes --> aide si pas le dataset complet, attention aux graphiques de corrélations qui ne fonctionneront pas
# df <- read.csv("Datasets/house_prices_france.csv", stringsAsFactors = FALSE, header = TRUE) # fichier avec les outlayers
# getting only the necessary columns
# df <- df %>% select(date, area_living, area_land, price)
# writing it into a new csv file
# write.csv(df, "Datasets/house_prices_france_less_columns.csv", row.names = FALSE)


df2 <- read.csv("Datasets/house_prices_france.csv", stringsAsFactors = FALSE, header = TRUE) # fichier avec les outlayers
df <- read.csv("Datasets/house_prices_france.csv", stringsAsFactors = FALSE, header = TRUE)
summary(df)
str(df)

# Visualisation avant suppression des valeurs aberrantes
boxplot_before <- ggplot(df, aes(y = price)) + 
  geom_boxplot(fill = "blue", alpha = 0.5) + 
  ggtitle("Boxplot des prix avant suppression des valeurs aberrantes") +
  scale_y_continuous(labels = label_number(suffix = " €"))
print(boxplot_before)
ggsave("Results/Data_Cleaning/boxplot_before_cleaning.png", plot = boxplot_before, width = 8, height = 6, dpi = 300)

# Supprimer les valeurs nulles pour le prix
df_clean <- df %>% filter(!is.na(price))

# Visualisation de la distribution des prix
plot_distribution <- ggplot(df_clean, aes(x = price)) + 
  geom_histogram(binwidth = 50000, fill = "skyblue", color = "black", alpha = 0.7) +
  ggtitle("Distribution des prix des maisons") +
  xlab("Prix (en €)") + 
  ylab("Fréquence") +
  scale_x_continuous(labels = scales::label_comma(suffix = " €")) +  # Ajout des séparateurs de milliers et €
  theme_minimal()
print(plot_distribution)
ggsave("Results/Data_Cleaning/distribution_prix_maisons.png", plot = plot_distribution, width = 8, height = 5, dpi = 300)


# Appliquer la transformation logarithmique aux prix
df_clean$log_price <- log(df_clean$price + 1)  # On ajoute 1 pour éviter les valeurs infinies (si le prix est 0)
# Vérification visuelle de la distribution des log-prix (histogramme)
plot_log_distribution <- ggplot(df_clean, aes(x = log_price)) + 
  geom_histogram(binwidth = 0.1, fill = "skyblue", color = "black", alpha = 0.7) +
  ggtitle("Distribution des prix après transformation logarithmique") +
  xlab("Log(Prix)") + ylab("Fréquence")
print(plot_log_distribution)
ggsave("Results/Data_Cleaning/distribution_log_prix.png", plot = plot_log_distribution, width = 8, height = 5, dpi = 300)

# Filtrer les valeurs où log_price est supérieur ou égal à 9
#df_clean <- df_clean %>% filter(log_price >= 8.5)
# Filtrer les valeurs où log_price est supérieur ou égal à 9
#df_clean <- df_clean %>% filter(log_price <= 14)
# Visualiser la distribution après la suppression des valeurs inférieures à log(Prix) < 9
'''ggplot(df_clean, aes(x = log_price)) + 
  geom_histogram(binwidth = 0.1, fill = "skyblue", color = "black", alpha = 0.7) +
  ggtitle("Distribution après suppression des valeurs avec log(Prix) < 9") +
  xlab("Log(Prix)") + ylab("Fréquence")'''

# Apply the Anderson-Darling test
ad_test_result <- ad.test(df_clean$log_price)
print(ad_test_result) # p-value < 2.2e-16, reject H0, not normal

# Appliquer la transformation logarithmique aux variables
df$log_price <- log(df$price + 1)  
df$log_area_living <- log(df$area_living + 1)
df$log_area_land <- log(df$area_land + 1)

# Détection et suppression des valeurs aberrantes sur l'échelle logarithmique
# suppression des valeurs aberrantes sur l'échelle logarithmique du prix
log_price_threshold <- quantile(df$log_price, 0.99, na.rm = TRUE)
df <- df[df$log_price <= log_price_threshold, ]
# suppression des valeurs aberrantes sur l'échelle logarithmique de la surface habitable
log_area_living_threshold <- quantile(df$log_area_living, 0.99, na.rm = TRUE)
df <- df[df$log_area_living <= log_area_living_threshold, ]
# suppression des valeurs aberrantes sur l'échelle logarithmique de la surface du terrain
log_area_land_threshold <- quantile(df$log_area_land, 0.99, na.rm = TRUE)
df <- df[df$log_area_land <= log_area_land_threshold, ]
# (Facultatif) Supprimer les colonnes log si elles ne sont plus nécessaires
df <- df %>% select(-log_price, -log_area_living, -log_area_land)

# Visualisation après suppression des valeurs aberrantes
boxplot_after <- ggplot(df, aes(y = price)) + 
  geom_boxplot(fill = "blue", alpha = 0.5) + 
  ggtitle("Boxplot des prix après suppression des valeurs aberrantes") +
  scale_y_continuous(labels = label_number(suffix = " €"))
print(boxplot_after)
# Sauvegarde du graphique
ggsave("Results/Data_Cleaning/boxplot_after_cleaning.png", plot = boxplot_after, width = 8, height = 6, dpi = 300)

# Calculer la matrice de corrélation et sélectionner les variables les plus corrélées
# Calcul de la matrice de corrélation
cor_matrix <- cor(df[, sapply(df, is.numeric)], use = "complete.obs")
# Sauvegarde du corrplot
png("Results/Data_Cleaning/correlation_matrix.png", width = 800, height = 600)
corrplot(cor_matrix, method = "circle")
dev.off()


select_top_n <- function(target, cor_matrix, n) {
  return(names(sort(abs(cor_matrix[target, ]), decreasing = TRUE))[2:(n+1)]) # Exclut la variable cible elle-même
}
# Tester les modèles avec 2, 3 et 4 meilleures variables
compare_models <- function(target) {
  vars_2 <- select_top_n(target, cor_matrix, 2)
  vars_3 <- select_top_n(target, cor_matrix, 3)
  vars_4 <- select_top_n(target, cor_matrix, 4)
  
  complete_cases <- df[complete.cases(df[, c(target, vars_4)]), ]
  
  model_2 <- train(as.formula(paste(target, "~", paste(vars_2, collapse = " + "))), data = complete_cases, method = "lm")
  model_3 <- train(as.formula(paste(target, "~", paste(vars_3, collapse = " + "))), data = complete_cases, method = "lm")
  model_4 <- train(as.formula(paste(target, "~", paste(vars_4, collapse = " + "))), data = complete_cases, method = "lm")
  
  results <- data.frame(
    Variables = c(2, 3, 4),
    RMSE = c(model_2$results$RMSE, model_3$results$RMSE, model_4$results$RMSE)
  )
  
  best_n <- results$Variables[which.min(results$RMSE)]
  best_vars <- select_top_n(target, cor_matrix, best_n)
  
  return(best_vars)
}
best_vars_area_living <- compare_models("area_living")
best_vars_area_land <- compare_models("area_land")
best_vars_price <- compare_models("price")

# Gestion des valeurs manquantes : imputation par régression linéaire
impute_lm <- function(df, target, predictors) {
  complete_cases <- df[complete.cases(df[, c(target, predictors)]), ]
  model <- lm(as.formula(paste(target, "~", paste(predictors, collapse = " + "))), data = complete_cases)
  missing_index <- which(is.na(df[[target]]))
  df[[target]][missing_index] <- predict(model, newdata = df[missing_index, ])
  return(df)
}
df <- impute_lm(df, "area_living", best_vars_area_living)
df <- impute_lm(df, "area_land", best_vars_area_land)
df <- impute_lm(df, "price", best_vars_price)

# Identifier les outliers supprimés avec les coordonnées (x_lbt93, y_lbt93)
df_outliers <- anti_join(df, df2, by = c("x_lbt93", "y_lbt93"))
# Fusionner df2 et les outliers supprimés
df <- bind_rows(df2, df_outliers)
# Correction des incohérences : suppression des doublons
df <- df %>% distinct()

# Exporter le nouveau fichier CSV avec les données nettoyées
write.csv(df, "Datasets/house_prices_france_cleaned.csv", row.names = FALSE)

# Visualisation de la distribution des prix avant et après transformation
plot_new_histogram <- ggplot(df, aes(x = price)) + 
  geom_histogram(bins = 30, fill = "blue", alpha = 0.5) + 
  ggtitle("Distribution des prix après nettoyage") +
  scale_x_continuous(labels = scales::comma) +  # Format en euros
  theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
print(plot_new_histogram)
ggsave("Results/Data_Cleaning/distribution_prix_apres_nettoyage.png", plot = plot_new_histogram, width = 8, height = 5, dpi = 300)

df$log_price <- log(df$price + 1)  # Transformation logarithmique
plot_new_histogram_log <- ggplot(df, aes(x = log_price)) +
  geom_histogram(bins = 30, fill = "red", alpha = 0.5) + 
  ggtitle("Distribution des prix après transformation logarithmique") +
  theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
print(plot_new_histogram_log)
ggsave("Results/Data_Cleaning/distribution_log_prix_apres_nettoyage.png", plot = plot_new_histogram_log, width = 8, height = 5, dpi = 300)



# Lire le fichier CSV avec moins de colonnes --> aide si pas le dataset complet, attention aux graphiques de corrélations qui ne fonctionneront pas
# df <- read.csv("Datasets/house_prices_france_cleaned.csv", stringsAsFactors = FALSE, header = TRUE)
# getting only the necessary columns
# df <- df %>% select(date, area_living, area_land, price)
# writing it into a new csv file
# write.csv(df, "Datasets/house_prices_france_cleaned_less_columns.csv", row.names = FALSE)


# Lire le fichier nettoyé
df <- read.csv("Datasets/house_prices_france_cleaned.csv", stringsAsFactors = FALSE, header = TRUE)
# Transformation de la colonne date
df$date <- as.Date(df$date, format = "%Y-%m-%d")
df$week <- floor_date(df$date, "week")
area_land_importance <- 0.15 # Importance de la surface du terrain par rapport à la surface habitable
summary(df)




### ÉVOLUTION DU PRIX TOTAL VENDU PAR SEMAINE ###
df_total_weekly_price <- df %>%
  group_by(week) %>%
  summarise(price = sum(price, na.rm = TRUE))
total_price_weekly_xts <- xts(df_total_weekly_price$price, order.by = df_total_weekly_price$week)

# Graphique statique avec ggplot
if (plot_raw_graphs == TRUE){
plot_total_price_weekly_xts <- ggplot(df_total_weekly_price, aes(x = week, y = price)) +
  geom_line(color = "black") +
  scale_y_continuous(labels = scales::comma) +  # Format en euros
  labs(title = "Évolution du prix total des maisons vendues par semaine", y = "Prix total (en €)", x = "Temps") +
  theme_minimal()
print(plot_total_price_weekly_xts)
ggsave("Results/Raw_Graphs/total_price_weekly.png", plot = plot_total_price_weekly_xts, width = 8, height = 5, dpi = 300)
}

# Graphique interactif avec dygraphs
if (plot_digraph == TRUE){
  dygraph(total_price_weekly_xts) %>%
    dyAxis("y", label = "Prix total (en €)", valueFormatter = 'function(x) { return x.toLocaleString("fr-FR") + " €"; }') %>%
    dyAxis("x", label = "Temps") %>%
    dyOptions(fillGraph = TRUE, drawGrid = FALSE) %>%
    dyRangeSelector()
}

# estimation de la tendance par régression linéaire pour raw graph visualisation
if (plot_raw_graphs == TRUE){
model <- lm(price ~ week, data = df_total_weekly_price)
df_total_weekly_price$tendance <- predict(model, newdata = df_total_weekly_price)
plot_total_price_weekly_xts_tendance <- ggplot(df_total_weekly_price, aes(x = week, y = price)) +
  geom_line(color = "black") +
  geom_line(aes(y = tendance), color = "red", linewidth = 1.2) +
  scale_y_continuous(labels = scales::comma) +  # Format en euros
  labs(title = "Évolution du prix total par semaine avec tendance linéaire", y = "Prix total (en €)", x = "Temps") +
  theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
print(plot_total_price_weekly_xts_tendance)
ggsave("Results/Raw_Graphs/total_price_weekly_tendance.png", plot = plot_total_price_weekly_xts_tendance, width = 8, height = 5, dpi = 300)
}

# Tracer les graphiques de tendance et de saisonnalité
if (plot_tendance_saison == TRUE){

## Moyenne Mobile ## 
    nb_points_moyenne_mobile_tendance <- 40
    nb_points_moyenne_mobile_saison <- 10
    ## estimation de la tendance par moyenne mobile
    l <- nb_points_moyenne_mobile_tendance # définit le nombre de points précédents et suivants à considérer pour la moyenne mobile 
    # --> ne peut donner la tendance de tout le graphe mais en donne une bonne représentation
    str(total_price_weekly_xts)
    mb<-stats::filter(total_price_weekly_xts, filter=array(1/l,dim=l), method = c("convolution"), sides = 2, circular = FALSE)
    mb<-xts(mb,order.by=df_total_weekly_price$week)
    # Graphique de la tendance
    plot_total_price_weekly_xts_tendance <- ggplot(df_total_weekly_price, aes(x = week, y = price)) +
      geom_line(color = "black") +
      geom_line(aes(y = mb), color = "red", linewidth = 1.2) +
      scale_y_continuous(labels = scales::comma) +  # Format en euros
      labs(title = "Évolution du prix total de ventes par semaine avec tendance par moyenne mobile", y = "Prix total (en €)", x = "Temps") +
      theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
    print(plot_total_price_weekly_xts_tendance)
    ggsave("Results/Tendance_Saison/total_price_weekly_moyenne_mobile_tendance.png", plot = plot_total_price_weekly_xts_tendance, width = 8, height = 5, dpi = 300)

    ## Par moyenne mobile = dégager la tendance + détecter la saisonnalité 
    K <- nb_points_moyenne_mobile_saison
    mb.season <- stats::filter(total_price_weekly_xts-mb, filter = array(1/K, dim = K), method = "convolution", sides = 2, circular = TRUE) # total_price_weekly_xts-mb for the residual
    mb.season <- xts(mb.season, order.by = df_total_weekly_price$week)
    # Graphique de la saisonnalité
    plot_total_price_weekly_xts_saison <- ggplot(df_total_weekly_price, aes(x = week, y = price)) +
      geom_line(color = "black") +
      geom_line(aes(y = mb.season+mb), color = "blue", linewidth = 1.2) +
      scale_y_continuous(labels = scales::comma) +  # Format en euros
      labs(title = "Évolution du prix total de ventes par semaine avec saisonnalité par moyenne mobile", y = "Prix total (en €)", x = "Temps") +
      theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
    print(plot_total_price_weekly_xts_saison)
    ggsave("Results/Tendance_Saison/total_price_weekly_moyenne_mobile_saison.png", plot = plot_total_price_weekly_xts_saison, width = 8, height = 5, dpi = 300)

    # Création du graphique avec tendance et saisonnalité
    plot_total_price_weekly_xts_tendance_saison <- ggplot(df_total_weekly_price, aes(x = week, y = price)) +
      geom_line(color = "black") +
      geom_line(aes(y = mb), color = "red", linewidth = 1.2) +
      geom_line(aes(y = mb.season + mb), color = "blue", linewidth = 1.2) +
      scale_y_continuous(labels = scales::comma) +  # Format en euros
      labs(title = "Évolution du prix total de ventes par semaine avec tendance et saisonnalité par moyenne mobile", y = "Prix total (en €)", x = "Temps") +
          theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
    print(plot_total_price_weekly_xts_tendance_saison)
    ggsave("Results/Tendance_Saison/total_price_weekly_moyenne_mobile_tendance_saison.png", plot = plot_total_price_weekly_xts_tendance_saison, width = 8, height = 5, dpi = 300)
    

## Noyau Gaussien ##
    # Paramètre de lissage (plus il est grand, plus c'est lisse)
    h <- 10000  # Lissage élevé pour la tendance
    t <- as.numeric(df_total_weekly_price$week)  
    X <- as.numeric(df_total_weekly_price$price)
    n <- length(t)
    # Définition du noyau gaussien
    noyau <- function(x,h) {
      w <- dnorm(x - t, 0, sd = sqrt(h / 2))
      w / sum(w)
    }

    # Calcul de la tendance
    W <- matrix(unlist(lapply(t, function(x) noyau(x, h))), ncol = n, nrow = n, byrow = FALSE)
    ychap.kernel <- colSums(X * W)  # Tendance estimée
    ychap.kernel <- xts(ychap.kernel, order.by = df_total_weekly_price$week)
    # Graphique de la tendance
    plot_total_price_weekly_xts_kernel <- ggplot(df_total_weekly_price, aes(x = week, y = price)) +
      geom_line(color = "black") +  # Série originale
      geom_line(aes(y = ychap.kernel), color = "red", linewidth = 1.2) +  # Tendance
      scale_y_continuous(labels = scales::comma) +  # Format en euros
      labs(title = "Évolution du prix total de ventes par semaine avec noyau gaussien", y = "Prix total (en €)", x = "Temps") +
      theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
    print(plot_total_price_weekly_xts_kernel)
    ggsave("Results/Tendance_Saison/total_price_weekly_kernel_tendance.png", plot = plot_total_price_weekly_xts_kernel, width = 8, height = 5, dpi = 300)

    # Extraction de la saisonnalité
    X.detrend <- X - as.numeric(ychap.kernel)
    h <- 100  # Lissage plus faible pour capter la saisonnalité
    W_saison <- matrix(unlist(lapply(t, function(x) noyau(x, h))), ncol = n, nrow = n, byrow = FALSE)
    ychap.season <- colSums(X.detrend * W_saison)
    ychap.season <- xts(ychap.season, order.by = df_total_weekly_price$week)
    # Graphique de la saisonnalité
    plot_total_price_weekly_xts_kernel_saison <- ggplot(df_total_weekly_price, aes(x = week, y = price)) +
      geom_line(color = "black") +  # Série originale
      geom_line(aes(y = ychap.kernel + ychap.season), color = "blue", linewidth = 1.2) +  # Tendance + saisonnalité
      scale_y_continuous(labels = scales::comma) +  # Format en euros
      labs(title = "Évolution du prix total de ventes par semaine avec saisonnalité par noyau gaussien", y = "Prix total (en €)", x = "Temps") +
      theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
    print(plot_total_price_weekly_xts_kernel_saison)
    ggsave("Results/Tendance_Saison/total_price_weekly_kernel_saison.png", plot = plot_total_price_weekly_xts_kernel_saison, width = 8, height = 5, dpi = 300)

    # Création du graphique avec tendance et saisonnalité
    plot_total_price_weekly_xts_kernel_tendance_saison <- ggplot(df_total_weekly_price, aes(x = week, y = price)) +
      geom_line(color = "black") +  # Série originale
      geom_line(aes(y = ychap.kernel), color = "red", linewidth = 1.2) +  # Tendance
      geom_line(aes(y = ychap.kernel + ychap.season), color = "blue", linewidth = 1.2) +  # Tendance + saisonnalité
      scale_y_continuous(labels = scales::comma) +  # Format en euros
      labs(title = "Évolution du prix total de ventes par semaine avec tendance et saisonnalité par noyau gaussien", y = "Prix total (en €)", x = "Temps") +
      theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
    print(plot_total_price_weekly_xts_kernel_tendance_saison)
    ggsave("Results/Tendance_Saison/total_price_weekly_kernel_tendance_saison.png", plot = plot_total_price_weekly_xts_kernel_tendance_saison, width = 8, height = 5, dpi = 300)

    # Calcul de l'autocorrélation des résidus issus de la décomposition en tendance et saisonnalité
    residus <- total_price_weekly_xts - ychap.kernel - ychap.season
    # Save the ACF plot as a file
    png("Results/Tendance_Saison/acf_residus_gaussien_total_price_weekly.png", width = 800, height = 500, res = 100)
    acf(residus, main = "Autocorrélation des résidus de la décomposition par noyau gaussien")
    dev.off()

## Polynômes locaux ## 
    # Estimation de la tendance par polynômes locaux
    model <- loess(price ~ as.numeric(week), data = df_total_weekly_price, span = 0.3) # 0,3 --> 30% des points les plus proches utilisés pour estimer la valeur de chaque point
    model.lo <- xts(model$fitted, order.by = df_total_weekly_price$week)
    # Graphique de la tendance
    plot_total_price_weekly_xts_loess <- ggplot(df_total_weekly_price, aes(x = week, y = price)) +
      geom_line(color = "black") +
      geom_line(aes(y = model.lo), color = "red", linewidth = 1.2) +
      scale_y_continuous(labels = scales::comma) +  # Format en euros
      labs(title = "Évolution du prix total de ventes par semaine avec polynômes locaux", y = "Prix total (en €)", x = "Temps") +
      theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
    print(plot_total_price_weekly_xts_loess)
    ggsave("Results/Tendance_Saison/total_price_weekly_loess_tendance.png", plot = plot_total_price_weekly_xts_loess, width = 8, height = 5, dpi = 300)

    # Extraction de la saisonnalité
    model.detrend <- df_total_weekly_price$price - model.lo
    model.season <- loess(model.detrend ~ as.numeric(df_total_weekly_price$week), span = 0.1)  # Lissage plus faible pour la saisonnalité
    model.season.lo <- xts(model.season$fitted, order.by = df_total_weekly_price$week)
    # Graphique de la saisonnalité
    plot_total_price_weekly_xts_loess_saison <- ggplot(df_total_weekly_price, aes(x = week, y = price)) +
      geom_line(color = "black") +
      geom_line(aes(y = model.season.lo + model.lo), color = "blue", linewidth = 1.2) +
      scale_y_continuous(labels = scales::comma) +  # Format en euros
      labs(title = "Évolution du prix total de ventes par semaine avec saisonnalité par polynômes locaux", y = "Prix total (en €)", x = "Temps") +
      theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
    print(plot_total_price_weekly_xts_loess_saison)
    ggsave("Results/Tendance_Saison/total_price_weekly_loess_saison.png", plot = plot_total_price_weekly_xts_loess_saison, width = 8, height = 5, dpi = 300)

    # Création du graphique avec tendance et saisonnalité
    plot_total_price_weekly_xts_loess_tendance_saison <- ggplot(df_total_weekly_price, aes(x = week, y = price)) +
      geom_line(color = "black") +
      geom_line(aes(y = model.lo), color = "red", linewidth = 1.2) +
      geom_line(aes(y = model.season.lo + model.lo), color = "blue", linewidth = 1.2) +
      scale_y_continuous(labels = scales::comma) +  # Format en euros
      labs(title = "Évolution du prix total de ventes par semaine avec tendance et saisonnalité par polynômes locaux", y = "Prix total (en €)", x = "Temps") +
      theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
    print(plot_total_price_weekly_xts_loess_tendance_saison)
    ggsave("Results/Tendance_Saison/total_price_weekly_loess_tendance_saison.png", plot = plot_total_price_weekly_xts_loess_tendance_saison, width = 8, height = 5, dpi = 300)

    # Calcul de l'autocorrélation des résidus issus de la décomposition en tendance et saisonnalité
    residus <- df_total_weekly_price$price - model.lo
    # Save the ACF plot as a file
    png("Results/Tendance_Saison/acf_residus_loess_total_price_weekly.png", width = 800, height = 500, res = 100)
    acf(residus, main = "Autocorrélation des résidus de la décomposition par polynômes locaux")
    dev.off()
}






### ÉVOLUTION DU PRIX MOYEN DES BIENS VENDU PAR SEMAINE ###
df_weekly_house_price <- df %>%
  group_by(week) %>%
  summarise(price = mean(price, na.rm = TRUE))
price_house_weekly_xts <- xts(df_weekly_house_price$price, order.by = df_weekly_house_price$week)

# Graphique statique
plot_house_weekly_xts <- ggplot(df_weekly_house_price, aes(x = week, y = price)) +
  geom_line(color = "black") +
  scale_y_continuous(labels = scales::comma) +  # Format en euros
  labs(title = "Évolution du prix moyen des maisons vendues par semaine", y = "Prix total (en €)", x = "Temps") +
  theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
print(plot_house_weekly_xts)
ggsave("Results/Raw_Graphs/price_house_weekly.png", plot = plot_house_weekly_xts, width = 8, height = 5, dpi = 300)

# Graphique interactif
if (plot_digraph == TRUE){
dygraph(price_house_weekly_xts) %>%
  dyAxis("y", label = "Prix maison (en €)", valueFormatter = 'function(x) { return x.toLocaleString("fr-FR") + " €"; }') %>%
  dyAxis("x", label = "Temps") %>%
  dyOptions(fillGraph = TRUE, drawGrid = FALSE) %>%
  dyRangeSelector()
}

# estimation de la tendance par régression linéaire pour raw graph visualisation
if (plot_raw_graphs == TRUE){
model <- lm(price ~ week, data = df_weekly_house_price)
df_weekly_house_price$tendance <- predict(model, newdata = df_weekly_house_price)
plot_total_price_weekly_xts_tendance <- ggplot(df_weekly_house_price, aes(x = week, y = price)) +
  geom_line(color = "black") +
  geom_line(aes(y = tendance), color = "red", linewidth = 1.2) +
  scale_y_continuous(labels = scales::comma) +  # Format en euros
  labs(title = "Évolution du prix moyen des maisons vendues par semaine", y = "Prix total (en €)", x = "Temps") +
  theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
print(plot_total_price_weekly_xts_tendance)
ggsave("Results/Raw_Graphs/price_house_weekly_tendance.png", plot = plot_total_price_weekly_xts_tendance, width = 8, height = 5, dpi = 300)
}

# Tracer les graphiques de tendance et de saisonnalité
if (plot_tendance_saison == TRUE){

## Moyenne Mobile ## 
    nb_points_moyenne_mobile_tendance <- 40
    nb_points_moyenne_mobile_saison <- 10
    ## estimation de la tendance par moyenne mobile
    l <- nb_points_moyenne_mobile_tendance # définit le nombre de points précédents et suivants à considérer pour la moyenne mobile 
    # --> ne peut donner la tendance de tout le graphe mais en donne une bonne représentation
    str(price_house_weekly_xts)
    mb<-stats::filter(price_house_weekly_xts, filter=array(1/l,dim=l), method = c("convolution"), sides = 2, circular = FALSE)
    mb<-xts(mb,order.by=df_weekly_house_price$week)
    # Graphique de la tendance
    plot_total_price_weekly_xts_tendance <- ggplot(df_weekly_house_price, aes(x = week, y = price)) +
      geom_line(color = "black") +
      geom_line(aes(y = mb), color = "red", linewidth = 1.2) +
      scale_y_continuous(labels = scales::comma) +  # Format en euros
      labs(title = "Évolution du prix moyen des maisons vendues par semaine avec tendance par moyenne mobile", y = "Prix total (en €)", x = "Temps") +
      theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
    print(plot_total_price_weekly_xts_tendance)
    ggsave("Results/Tendance_Saison/price_house_weekly_moyenne_mobile_tendance.png", plot = plot_total_price_weekly_xts_tendance, width = 8, height = 5, dpi = 300)

    ## Par moyenne mobile = dégager la tendance + détecter la saisonnalité 
    K <- nb_points_moyenne_mobile_saison
    mb.season <- stats::filter(price_house_weekly_xts-mb, filter = array(1/K, dim = K), method = "convolution", sides = 2, circular = TRUE) # price_house_weekly_xts-mb for the residual
    mb.season <- xts(mb.season, order.by = df_weekly_house_price$week)
    # Graphique de la saisonnalité
    plot_total_price_weekly_xts_saison <- ggplot(df_weekly_house_price, aes(x = week, y = price)) +
      geom_line(color = "black") +
      geom_line(aes(y = mb.season+mb), color = "blue", linewidth = 1.2) +
      scale_y_continuous(labels = scales::comma) +  # Format en euros
      labs(title = "Évolution du prix moyen des maisons vendues par semaine avec saisonnalité par moyenne mobile", y = "Prix total (en €)", x = "Temps") +
      theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
    print(plot_total_price_weekly_xts_saison)
    ggsave("Results/Tendance_Saison/price_house_weekly_moyenne_mobile_saison.png", plot = plot_total_price_weekly_xts_saison, width = 8, height = 5, dpi = 300)

    # Création du graphique avec tendance et saisonnalité
    plot_total_price_weekly_xts_tendance_saison <- ggplot(df_weekly_house_price, aes(x = week, y = price)) +
      geom_line(color = "black") +
      geom_line(aes(y = mb), color = "red", linewidth = 1.2) +
      geom_line(aes(y = mb.season + mb), color = "blue", linewidth = 1.2) +
      scale_y_continuous(labels = scales::comma) +  # Format en euros
      labs(title = "Évolution du prix moyen des maisons vendues par semaine avec tendance et saisonnalité par moyenne mobile", y = "Prix total (en €)", x = "Temps") +
      theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
    print(plot_total_price_weekly_xts_tendance_saison)
    ggsave("Results/Tendance_Saison/price_house_weekly_moyenne_mobile_tendance_saison.png", plot = plot_total_price_weekly_xts_tendance_saison, width = 8, height = 5, dpi = 300)
    
   
## Noyau Gaussien ##
    # Paramètre de lissage (plus il est grand, plus c'est lisse)
    h <- 10000  # Lissage élevé pour la tendance
    t <- as.numeric(df_weekly_house_price$week)  
    X <- as.numeric(df_weekly_house_price$price)
    n <- length(t)
    # Définition du noyau gaussien
    noyau <- function(x,h) {
      w <- dnorm(x - t, 0, sd = sqrt(h / 2))
      w / sum(w)
    }

    # Calcul de la tendance
    W <- matrix(unlist(lapply(t, function(x) noyau(x, h))), ncol = n, nrow = n, byrow = FALSE)
    ychap.kernel <- colSums(X * W)  # Tendance estimée
    ychap.kernel <- xts(ychap.kernel, order.by = df_weekly_house_price$week)
    # Graphique de la tendance
    plot_total_price_weekly_xts_kernel <- ggplot(df_weekly_house_price, aes(x = week, y = price)) +
      geom_line(color = "black") +  # Série originale
      geom_line(aes(y = ychap.kernel), color = "red", linewidth = 1.2) +  # Tendance
      scale_y_continuous(labels = scales::comma) +  # Format en euros
      labs(title = "Évolution du prix moyen des maisons vendues par semaine avec noyau gaussien", y = "Prix total (en €)", x = "Temps") +
      theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
    print(plot_total_price_weekly_xts_kernel)
    ggsave("Results/Tendance_Saison/price_house_weekly_kernel_tendance.png", plot = plot_total_price_weekly_xts_kernel, width = 8, height = 5, dpi = 300)

    # Extraction de la saisonnalité
    X.detrend <- X - as.numeric(ychap.kernel)
    h <- 100  # Lissage plus faible pour capter la saisonnalité
    W_saison <- matrix(unlist(lapply(t, function(x) noyau(x, h))), ncol = n, nrow = n, byrow = FALSE)
    ychap.kernel.season <- colSums(X.detrend * W_saison)
    ychap.kernel.season <- xts(ychap.kernel.season, order.by = df_weekly_house_price$week)
    # Graphique de la saisonnalité
    plot_total_price_weekly_xts_kernel_saison <- ggplot(df_weekly_house_price, aes(x = week, y = price)) +
      geom_line(color = "black") +  # Série originale
      geom_line(aes(y = ychap.kernel + ychap.kernel.season), color = "blue", linewidth = 1.2) +  # Tendance + saisonnalité
      scale_y_continuous(labels = scales::comma) +  # Format en euros
      labs(title = "Évolution du prix moyen des maisons vendues par semaine avec saisonnalité par noyau gaussien", y = "Prix total (en €)", x = "Temps") +
      theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
    print(plot_total_price_weekly_xts_kernel_saison)
    ggsave("Results/Tendance_Saison/price_house_weekly_kernel_saison.png", plot = plot_total_price_weekly_xts_kernel_saison, width = 8, height = 5, dpi = 300)

    # Création du graphique avec tendance et saisonnalité
    plot_total_price_weekly_xts_kernel_tendance_saison <- ggplot(df_weekly_house_price, aes(x = week, y = price)) +
      geom_line(color = "black") +  # Série originale
      geom_line(aes(y = ychap.kernel), color = "red", linewidth = 1.2) +  # Tendance
      geom_line(aes(y = ychap.kernel + ychap.kernel.season), color = "blue", linewidth = 1.2) +  # Tendance + saisonnalité
      scale_y_continuous(labels = scales::comma) +  # Format en euros
      labs(title = "Évolution du prix moyen des maisons vendues par semaine avec tendance et saisonnalité par noyau gaussien", y = "Prix total (en €)", x = "Temps") +
      theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
    print(plot_total_price_weekly_xts_kernel_tendance_saison)
    ggsave("Results/Tendance_Saison/price_house_weekly_kernel_tendance_saison.png", plot = plot_total_price_weekly_xts_kernel_tendance_saison, width = 8, height = 5, dpi = 300)

    # Calcul de l'autocorrélation des résidus issus de la décomposition en tendance et saisonnalité
    residus <- price_house_weekly_xts - ychap.kernel - ychap.kernel.season
    # Save the ACF plot as a file
    png("Results/Tendance_Saison/acf_residus_gaussien_price_house_weekly.png", width = 800, height = 500, res = 100)
    acf(residus, main = "Autocorrélation des résidus de la décomposition par noyau gaussien")
    dev.off()


## Polynômes locaux ##
    # Estimation de la tendance par polynômes locaux
    df_weekly_house_price$price <- as.numeric(df_weekly_house_price$price)
    model <- loess(price ~ as.numeric(week), data = df_weekly_house_price, span = 0.3) # 0,3 --> 30% des points les plus proches utilisés pour estimer la valeur de chaque point
    model.lo <- xts(model$fitted, order.by = df_weekly_house_price$week)
    # Graphique de la tendance
    plot_total_price_weekly_xts_loess <- ggplot(df_weekly_house_price, aes(x = week, y = price)) +
      geom_line(color = "black") +
      geom_line(aes(y = model.lo), color = "red", linewidth = 1.2) +
      scale_y_continuous(labels = scales::comma) +  # Format en euros
      labs(title = "Évolution du prix moyen des maisons vendues par semaine avec polynômes locaux", y = "Prix total (en €)", x = "Temps") +
      theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
    print(plot_total_price_weekly_xts_loess)
    ggsave("Results/Tendance_Saison/price_house_weekly_loess_tendance.png", plot = plot_total_price_weekly_xts_loess, width = 8, height = 5, dpi = 300)

    # Extraction de la saisonnalité
    model.detrend <- df_weekly_house_price$price - model.lo
    model.season <- loess(model.detrend ~ as.numeric(df_weekly_house_price$week), span = 0.1)  # Lissage plus faible pour la saisonnalité
    model.season.lo <- xts(model.season$fitted, order.by = df_weekly_house_price$week)
    # Graphique de la saisonnalité
    plot_total_price_weekly_xts_loess_saison <- ggplot(df_weekly_house_price, aes(x = week, y = price)) +
      geom_line(color = "black") +
      geom_line(aes(y = model.season.lo + model.lo), color = "blue", size =1.2) + 
      scale_y_continuous(labels = scales::comma) +  # Format en euros
      labs(title = "Évolution du prix moyen des maisons vendues par semaine avec saisonnalité par polynômes locaux", y = "Prix total (en €)", x = "Temps") +
      theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
    print(plot_total_price_weekly_xts_loess_saison)
    ggsave("Results/Tendance_Saison/price_house_weekly_loess_saison.png", plot = plot_total_price_weekly_xts_loess_saison, width = 8, height = 5, dpi = 300)

    # Création du graphique avec tendance et saisonnalité
    plot_total_price_weekly_xts_loess_tendance_saison <- ggplot(df_weekly_house_price, aes(x = week, y = price)) +
      geom_line(color = "black") +
      geom_line(aes(y = model.lo), color = "red", linewidth = 1.2) +
      geom_line(aes(y = model.season.lo + model.lo), color = "blue", linewidth = 1.2) +
      scale_y_continuous(labels = scales::comma) +  # Format en euros
      labs(title = "Évolution du prix moyen des maisons vendues par semaine avec tendance et saisonnalité par polynômes locaux", y = "Prix total (en €)", x = "Temps") +
      theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
    print(plot_total_price_weekly_xts_loess_tendance_saison)
    ggsave("Results/Tendance_Saison/price_house_weekly_loess_tendance_saison.png", plot = plot_total_price_weekly_xts_loess_tendance_saison, width = 8, height = 5, dpi = 300)

    # Calcul de l'autocorrélation des résidus issus de la décomposition en tendance et saisonnalité
    residus <- df_weekly_house_price$price - model.lo
    # Save the ACF plot as a file
    png("Results/Tendance_Saison/acf_residus_loess_price_house_weekly.png", width = 800, height = 500, res = 100)
    acf(residus, main = "Autocorrélation des résidus de la décomposition par polynômes locaux")
    dev.off()
}






### ÉVOLUTION DU PRIX DU M2 PAR SEMAINE ###
df$price_m2 <- df$price / (df$area_living + df$area_land * area_land_importance) # répartition arbitraire entre les deux surfaces
# Vérifier les valeurs aberrantes (infinites ou NaN)
df <- df[is.finite(df$price_m2) & !is.na(df$price_m2), ]
# Calculer le total des prix au m² par semaine
df_weekly_price_m2 <- df %>%
  group_by(week) %>%
  summarise(price_m2 = mean(price_m2, na.rm = TRUE))
price_m2_xts <- xts(df_weekly_price_m2$price_m2, order.by = df_weekly_price_m2$week)
# Graphique statique
plot_m2_xts <- ggplot(df_weekly_price_m2, aes(x = week, y = price_m2)) +
  geom_line(color = "black") +
  scale_y_continuous(labels = scales::comma) +  # Format en euros
  labs(title = "Évolution du prix au m² par semaine", y = "Prix au m² (€)", x = "Temps") +
  theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
print(plot_m2_xts)
ggsave("Results/Raw_Graphs/price_m2_weekly.png", plot = plot_m2_xts, width = 8, height = 5, dpi = 300)
# Graphique interactif
if (plot_digraph == TRUE){
dygraph(price_m2_xts) %>%
  dyAxis("y", label = "Prix au m2 (en €)", valueFormatter = 'function(x) { return x.toLocaleString("fr-FR") + " €"; }') %>%
  dyAxis("x", label = "Temps") %>%
  dyOptions(fillGraph = TRUE, drawGrid = FALSE) %>%
  dyRangeSelector()
}

# estimation de la tendance par régression linéaire pour raw graph visualisation
if (plot_raw_graphs == TRUE){
model <- lm(price_m2 ~ week, data = df_weekly_price_m2)
df_weekly_price_m2$tendance <- predict(model, newdata = df_weekly_price_m2)
plot_total_price_weekly_xts_tendance <- ggplot(df_weekly_price_m2, aes(x = week, y = price_m2)) +
  geom_line(color = "black") +
  geom_line(aes(y = tendance), color = "red", size = 1.2) +
  scale_y_continuous(labels = scales::comma) +  # Format en euros
  labs(title = "Évolution du prix au m² par semaine", y = "Prix au m² (€)", x = "Temps") +
  theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
print(plot_total_price_weekly_xts_tendance)
ggsave("Results/Raw_Graphs/price_m2_weekly_tendance.png", plot = plot_total_price_weekly_xts_tendance, width = 8, height = 5, dpi = 300)
}





###  ÉVOLUTION DU NOMBRE DE VENTES PAR SEMAINE ###
df_weekly_sales <- df %>%
  group_by(week) %>%
  summarise(n_sales = n())
sales_weekly_xts <- xts(df_weekly_sales$n_sales, order.by = df_weekly_sales$week)

# Graphique statique
plot_sales_weekly_xts <- ggplot(df_weekly_sales, aes(x = week, y = n_sales)) +
  geom_line(color = "black") +
  labs(title = "Nombre de ventes par semaine", y = "Nombre de ventes", x = "Temps") +
  theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
print(plot_sales_weekly_xts)
ggsave("Results/Raw_Graphs/sales_weekly.png", plot = plot_sales_weekly_xts, width = 8, height = 5, dpi = 300)

# Graphique interactif
if (plot_digraph == TRUE){
dygraph(sales_weekly_xts) %>%
  dyAxis("y", label = "Nombre de ventes par semaine") %>%
  dyAxis("x", label = "Temps") %>%
  dyOptions(fillGraph = TRUE, drawGrid = FALSE) %>%
  dyRangeSelector()
}

# estimation de la tendance par régression linéaire pour raw graph visualisation
if (plot_raw_graphs == TRUE){
model <- lm(n_sales ~ week, data = df_weekly_sales)
df_weekly_sales$tendance <- predict(model, newdata = df_weekly_sales)
plot_total_price_weekly_xts_tendance <- ggplot(df_weekly_sales, aes(x = week, y = n_sales)) +
  geom_line(color = "black") +
  geom_line(aes(y = tendance), color = "red", size = 1.2) +
  labs(title = "Nombre de ventes par semaine", y = "Nombre de ventes", x = "Temps") +
  theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
print(plot_total_price_weekly_xts_tendance)
ggsave("Results/Raw_Graphs/sales_weekly_tendance.png", plot = plot_total_price_weekly_xts_tendance, width = 8, height = 5, dpi = 300)
}





###  ÉVOLUTION DE LA SURFACE MOYENNE DES BIENS VENDUS PAR SEMAINE ###
df$area_total <- df$area_living + area_land_importance * df$area_land # répartition arbitraire entre les deux surfaces
df_weekly_area <- df %>%
  group_by(week) %>%
  summarise(area_total = mean(area_total, na.rm = TRUE))
area_weekly_xts <- xts(df_weekly_area$area_total, order.by = df_weekly_area$week)

# Graphique statique
plot_surface_weekly_xts <- ggplot(df_weekly_area, aes(x = week, y = area_total)) +
  geom_line(color = "black") +
  labs(title = "Évolution de la surface moyenne des biens vendus par semaine", y = "Surface totale (m²)", x = "Temps") +
  theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
print(plot_surface_weekly_xts)
ggsave("Results/Raw_Graphs/area_weekly.png", plot = plot_surface_weekly_xts, width = 8, height = 5, dpi = 300)

# Graphique interactif
if (plot_digraph == TRUE){
dygraph(area_weekly_xts) %>%
  dyAxis("y", label = "Surface totale (m²)") %>%
  dyAxis("x", label = "Temps") %>%
  dyOptions(fillGraph = TRUE, drawGrid = FALSE) %>%
  dyRangeSelector()
}

# estimation de la tendance par régression linéaire pour raw graph visualisation
if (plot_raw_graphs == TRUE){
model <- lm(area_total ~ week, data = df_weekly_area)
df_weekly_area$tendance <- predict(model, newdata = df_weekly_area)
plot_total_price_weekly_xts_tendance <- ggplot(df_weekly_area, aes(x = week, y = area_total)) +
  geom_line(color = "black") +
  geom_line(aes(y = tendance), color = "red", size = 1.2) +
  labs(title = "Évolution de la surface moyenne des biens vendus par semaine", y = "Surface totale (m²)", x = "Temps") +
  theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
print(plot_total_price_weekly_xts_tendance)
ggsave("Results/Raw_Graphs/area_weekly_tendance.png", plot = plot_total_price_weekly_xts_tendance, width = 8, height = 5, dpi = 300)
}

    


### Visualisation graphique des données combinées ###
### 1. Evolution of Total Price Sold and Sales Count ###
scale_factor <- max(total_price_weekly_xts, na.rm = TRUE) / max(sales_weekly_xts, na.rm = TRUE)
data_combined <- merge(total_price_weekly_xts / scale_factor, sales_weekly_xts)

plot_data_combined <- ggplot(data_combined, aes(x = index(data_combined))) +
  geom_line(aes(y = sales_weekly_xts, color = "Nombre de ventes")) +  # sales on the left axis
  geom_line(aes(y = total_price_weekly_xts / scale_factor, color = "Prix total ajusté")) +  # price on the right axis
  scale_y_continuous(name = "Nombre de ventes", sec.axis = sec_axis(~ . * scale_factor, name = "Prix total (en €)")) +  # swapped axes
  labs(title = "Évolution du prix total vendu et du nombre de ventes par semaine", x = "Temps") +
  scale_color_manual(values = c("Prix total ajusté" = "blue", "Nombre de ventes" = "red")) +
  theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
print(plot_data_combined)
ggsave("Results/Raw_Graphs/Combined/data_combined_total_price_sales_inverted.png", plot = plot_data_combined, width = 8, height = 5, dpi = 300)
colnames(data_combined) <- c("Prix total ajusté", "Nombre de ventes")

if (plot_digraph) {
  dygraph(data_combined) %>%
    dySeries("Prix total ajusté", label = "Prix total vendu (×10^6 €)", color = "blue") %>%
    dySeries("Nombre de ventes", label = "Nombre de ventes", color = "red") %>%
    dyOptions(fillGraph = TRUE, drawGrid = FALSE) %>%
    dyAxis("y", label = "Nombre de ventes") %>%
    dyAxis("y2", label = "Prix total (M€)", independentTicks = TRUE) %>%
    dyRangeSelector()
}



### 2. Evolution of Total Price Sold and Price per m² ###
scale_factor <- max(total_price_weekly_xts, na.rm = TRUE) / max(price_m2_xts, na.rm = TRUE)
data_combined <- merge(price_m2_xts, total_price_weekly_xts / scale_factor)

plot_data_combined <- ggplot(data_combined, aes(x = index(data_combined))) +
  geom_line(aes(y = price_m2_xts, color = "Prix au m² ajusté")) +  # Price per m² on the left axis
  geom_line(aes(y = total_price_weekly_xts / scale_factor, color = "Prix total ajusté")) +  # Total price on the right axis
  scale_y_continuous(name = "Prix au m² ajusté", sec.axis = sec_axis(~ . * scale_factor, name = "Prix total (en €)")) +  # Swapped axes
  labs(title = "Évolution du prix total vendu et du prix au m²", x = "Temps") +
  scale_color_manual(values = c("Prix total ajusté" = "blue", "Prix au m² ajusté" = "green")) +
  theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
print(plot_data_combined)
ggsave("Results/Raw_Graphs/Combined/data_combined_price_m2_inverted.png", plot = plot_data_combined, width = 8, height = 5, dpi = 300)
colnames(data_combined) <- c("Prix au m² ajusté", "Prix total ajusté")

if (plot_digraph) {
  dygraph(data_combined) %>%
    dySeries("Prix au m² ajusté", label = "Prix au m² (×10^3 €)", color = "green") %>%
    dySeries("Prix total ajusté", label = "Prix total vendu (×10^6 €)", color = "blue") %>%
    dyOptions(fillGraph = TRUE, drawGrid = FALSE) %>%
    dyAxis("y", label = "Prix au m² ajusté") %>%
    dyAxis("y2", label = "Prix total (M€)", independentTicks = TRUE) %>%
    dyRangeSelector()
}




### 3. Evolution of House Price and Price per m² ###
scale_factor <- max(price_house_weekly_xts, na.rm = TRUE) / max(price_m2_xts, na.rm = TRUE)
data_combined <- merge(price_m2_xts, price_house_weekly_xts / scale_factor)

plot_data_combined <- ggplot(data_combined, aes(x = index(data_combined))) +
  geom_line(aes(y = price_m2_xts, color = "Prix au m² ajusté")) +  # Price per m² on the left axis
  geom_line(aes(y = price_house_weekly_xts / scale_factor, color = "Prix moyen ajusté")) +  # House price on the right axis
  scale_y_continuous(name = "Prix au m² ajusté", sec.axis = sec_axis(~ . * scale_factor, name = "Prix des maisons (en €)")) +  # Swapped axes
  labs(title = "Évolution du prix des maisons et du prix au m²", x = "Temps") +
  scale_color_manual(values = c("Prix moyen ajusté" = "orange", "Prix au m² ajusté" = "green")) +
  theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
print(plot_data_combined)
ggsave("Results/Raw_Graphs/Combined/data_combined_house_m2_inverted.png", plot = plot_data_combined, width = 8, height = 5, dpi = 300)
colnames(data_combined) <- c("Prix au m² ajusté", "Prix moyen ajusté")

if (plot_digraph) {
  dygraph(data_combined) %>%
    dySeries("Prix au m² ajusté", label = "Prix au m² (€)", color = "green") %>%
    dySeries("Prix moyen ajusté", label = "Prix moyen (€)", color = "orange") %>%
    dyOptions(fillGraph = TRUE, drawGrid = FALSE) %>%
    dyAxis("y", label = "Prix au m²") %>%
    dyAxis("y2", label = "Prix moyen (€)", independentTicks = TRUE) %>%
    dyRangeSelector()
}



### 4. Evolution of House Price and Average Property Surface ###
scale_factor <- max(price_house_weekly_xts, na.rm = TRUE) / max(area_weekly_xts, na.rm = TRUE)
data_combined <- merge(area_weekly_xts, price_house_weekly_xts / scale_factor)

plot_data_combined <- ggplot(data_combined, aes(x = index(data_combined))) +
  geom_line(aes(y = area_weekly_xts, color = "Surface moyenne ajustée")) +  # Average area on the left axis
  geom_line(aes(y = price_house_weekly_xts / scale_factor, color = "Prix des maisons ajusté")) +  # House price on the right axis
  scale_y_continuous(name = "Surface moyenne ajustée", sec.axis = sec_axis(~ . * scale_factor, name = "Prix des maisons (en €)")) +  # Swapped axes
  labs(title = "Évolution du prix des maisons et de la surface moyenne", x = "Temps") +
  scale_color_manual(values = c("Prix des maisons ajusté" = "blue", "Surface moyenne ajustée" = "purple")) +
  theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
print(plot_data_combined)
ggsave("Results/Raw_Graphs/Combined/data_combined_house_area_inverted.png", plot = plot_data_combined, width = 8, height = 5, dpi = 300)
colnames(data_combined) <- c("Surface moyenne ajustée", "Prix des maisons ajusté")

if (plot_digraph) {
  dygraph(data_combined) %>%
    dySeries("Surface moyenne ajustée", label = "Surface moyenne (m²)", color = "purple") %>%
    dySeries("Prix des maisons ajusté", label = "Prix des maisons (×10^6 €)", color = "blue") %>%
    dyOptions(fillGraph = TRUE, drawGrid = FALSE) %>%
    dyAxis("y", label = "Surface moyenne ajustée") %>%
    dyAxis("y2", label = "Prix des maisons", independentTicks = TRUE) %>%
    dyRangeSelector()
}





### 6. Full Combined Graph (Total Price, House Price, Sales, Price per m², Average Surface) ###
# Définition des facteurs d'échelle pour normaliser les données
scale_total_price <- max(total_price_weekly_xts, na.rm = TRUE) / max(sales_weekly_xts, na.rm = TRUE)
scale_house_price <- max(price_house_weekly_xts, na.rm = TRUE) / max(sales_weekly_xts, na.rm = TRUE)
scale_price_m2 <- max(price_m2_xts, na.rm = TRUE) / max(sales_weekly_xts, na.rm = TRUE)
scale_area <- max(area_weekly_xts, na.rm = TRUE) / max(sales_weekly_xts, na.rm = TRUE)

# Fusion des séries temporelles avec normalisation
data_combined <- merge(
  total_price_weekly_xts / scale_total_price, 
  price_house_weekly_xts / scale_house_price,
  sales_weekly_xts, 
  price_m2_xts / scale_price_m2, 
  area_weekly_xts / scale_area
)

colnames(data_combined) <- c("Prix total ajusté", "Prix des maisons ajusté", "Nombre de ventes", "Prix au m2 ajusté", "Surface moyenne ajustée")
# Affichage interactif avec dygraph
if (plot_digraph){
dygraph(data_combined) %>%
  dySeries("Prix total ajusté", label = "Prix total vendu (M€)", color = "blue") %>%
  dySeries("Prix des maisons ajusté", label = "Prix des maisons (M€)", color = "purple") %>%
  dySeries("Nombre de ventes", label = "Nombre de ventes", color = "red") %>%
  dySeries("Prix au m2 ajusté", label = "Prix au m² (M€)", color = "green") %>%
  dySeries("Surface moyenne ajustée", label = "Surface moyenne (m²)", color = "orange") %>%
  dyOptions(fillGraph = TRUE, drawGrid = FALSE) %>%
  dyAxis("y", label = "Échelle normalisée") %>%
  dyAxis("y2", label = "Nombre de ventes", independentTicks = TRUE) %>%
  dyRangeSelector()
}





### Prédiction du prix total des maisons vendues par semaine ###
# Lissage exponentiel simple
exp_simple=function(x,alpha)
{
  xsmooth=x
  for(i in c(2:length(x))){
    xsmooth[i] <- alpha*x[i]+(1-alpha)*xsmooth[i-1]
  }
  return(xsmooth)
}

# Lissage exponentiel double
exp_double=function(x,alpha) # h=1 ici, xsmooth[i]=l[i]+b[i]
{
  xsmooth=x
  l <- array(x[1],dim=length(x))
  b <- array(x[2]-x[1],dim=length(x))
  
  for(i in c(2:length(x))){
    l[i] <- xsmooth[i-1]+(1-(1-alpha)^2)*(x[i]-xsmooth[i-1])
    b[i] <- b[i-1]+alpha^2*(x[i]-xsmooth[i-1])
    xsmooth[i] <- l[i]+b[i]
  }
  
  res <- list()
  res$smooth <- xsmooth
  res$l <- l
  res$b <- b
  return(res)
}

## Exponentielle simple ##
# Appliquer le lissage exponentiel simple avec alpha=0.1
alpha <- 0.1
price_smooth <- exp_simple(df_total_weekly_price$price, alpha)
# Graphique avec la courbe lissée (alpha=0.1)
plot_total_price_weekly_xts_smooth <- ggplot(df_total_weekly_price, aes(x = week, y = price)) +
  geom_line(color = "black") +
  geom_line(aes(y = price_smooth), color = "red", size = 1.2) +
  scale_y_continuous(labels = scales::comma) +  # Format en euros
  labs(title = "Évolution du prix total des maisons vendues par semaine avec lissage exponentiel simple", y = "Prix total (en €)", x = "Temps") +
  theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
print(plot_total_price_weekly_xts_smooth)
ggsave("Results/Prédiction/price_total_price_weekly_exp_simple_0_1.png", plot = plot_total_price_weekly_xts_smooth, width = 8, height = 5, dpi = 300)

# Tester différentes valeurs de alpha et visualiser l'erreur de prédiction
alpha_seq <- seq(0.05, 0.95, length = 100)
forecast_smooth <- lapply(alpha_seq, exp_simple, x = df_total_weekly_price$price)
errors <- unlist(lapply(forecast_smooth, function(x) {mean((tail(df_total_weekly_price$price, -1) - head(x, -1))^2)}))
# Graphique de l'erreur en fonction d'alpha
plot_errors_alpha <- ggplot(data.frame(alpha = alpha_seq, error = errors), aes(x = alpha, y = error)) +
  geom_line(color = "black") +
  labs(title = "Erreur de prédiction en fonction de alpha", y = "Erreur quadratique moyenne", x = "Alpha") +
  theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
print(plot_errors_alpha)
ggsave("Results/Prédiction/price_total_price_weekly_exp_simple_errors_alpha.png", plot = plot_errors_alpha, width = 8, height = 5, dpi = 300)

# Identifier le meilleur alpha et appliquer le lissage exponentiel simple
best_alpha <- alpha_seq[which.min(errors)]
price_smooth_best <- exp_simple(df_total_weekly_price$price, best_alpha)
# Graphique avec le meilleur alpha trouvé
plot_total_price_weekly_xts_best <- ggplot(df_total_weekly_price, aes(x = week, y = price)) +
  geom_line(color = "black") +
  geom_line(aes(y = price_smooth_best), color = "red", size = 1.2) +
  scale_y_continuous(labels = scales::comma) +  # Format en euros
  labs(title = paste("Évolution du prix total avec alpha =", round(best_alpha, 2)), y = "Prix total (en €)", x = "Temps") +
  theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
print(plot_total_price_weekly_xts_best)
ggsave("Results/Prédiction/price_total_price_weekly_exp_simple_best_alpha.png", plot = plot_total_price_weekly_xts_best, width = 8, height = 5, dpi = 300)


## Exponentielle double ##
# trouver le meilleur alpha pour le lissage exponentiel double
forecast_smooth_double <- lapply(alpha_seq, exp_double, x = df_total_weekly_price$price)
errors_double <- unlist(lapply(forecast_smooth_double, function(x) {mean((tail(df_total_weekly_price$price, -1) - head(x$smooth, -1))^2)}))
# Graphique de l'erreur en fonction d'alpha
plot_errors_alpha_double <- ggplot(data.frame(alpha = alpha_seq, error = errors_double), aes(x = alpha, y = error)) +
  geom_line(color = "black") +
  labs(title = "Erreur de prédiction en fonction de alpha (lissage exponentiel double)", y = "Erreur quadratique moyenne", x = "Alpha") +
  theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
print(plot_errors_alpha_double)
ggsave("Results/Prédiction/price_total_price_weekly_exp_double_errors_alpha.png", plot = plot_errors_alpha_double, width = 8, height = 5, dpi = 300)

# Identifier le meilleur alpha et appliquer le lissage exponentiel double
best_alpha_double <- alpha_seq[which.min(errors_double)]
price_smooth_best_double <- exp_double(df_total_weekly_price$price, best_alpha_double)$smooth
# Graphique avec le meilleur alpha trouvé
plot_total_price_weekly_xts_best_double <- ggplot(df_total_weekly_price, aes(x = week, y = price)) +
  geom_line(color = "black") +
  geom_line(aes(y = price_smooth_best_double), color = "red", size = 1.2) +
  scale_y_continuous(labels = scales::comma) +  # Format en euros
  labs(title = paste("Évolution du prix total avec alpha =", round(best_alpha_double, 2), "(lissage exponentiel double)"), y = "Prix total (en €)", x = "Temps") +
  theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
print(plot_total_price_weekly_xts_best_double)
ggsave("Results/Prédiction/price_total_price_weekly_exp_double_best_alpha.png", plot = plot_total_price_weekly_xts_best_double, width = 8, height = 5, dpi = 300)





### Prédiction du prix total de vente à un certain horizon ###
## Noyau Gaussien ##
# Paramètre de lissage (plus il est grand, plus c'est lisse)
h <- 10000  # Lissage élevé pour la tendance
t <- as.numeric(df_total_weekly_price$week)  
X <- as.numeric(df_total_weekly_price$price)
n <- length(t)
# Définition du noyau gaussien
noyau <- function(x,h) {
  w <- dnorm(x - t, 0, sd = sqrt(h / 2))
  w / sum(w)
}
# Calcul de la tendance
W <- matrix(unlist(lapply(t, function(x) noyau(x, h))), ncol = n, nrow = n, byrow = FALSE)
ychap.kernel <- colSums(X * W)  # Tendance estimée
ychap.kernel <- xts(ychap.kernel, order.by = df_total_weekly_price$week)
# Extraction de la saisonnalité
X.detrend <- X - as.numeric(ychap.kernel)
h <- 100  # Lissage plus faible pour capter la saisonnalité
W_saison <- matrix(unlist(lapply(t, function(x) noyau(x, h))), ncol = n, nrow = n, byrow = FALSE)
ychap.season <- colSums(X.detrend * W_saison)
ychap.season <- xts(ychap.season, order.by = df_total_weekly_price$week)

## Polynômes locaux ## 
# Estimation de la tendance par polynômes locaux
model <- loess(price ~ as.numeric(week), data = df_total_weekly_price, span = 0.3) # 0,3 --> 30% des points les plus proches utilisés pour estimer la valeur de chaque point
model.lo <- xts(model$fitted, order.by = df_total_weekly_price$week)
# Extraction de la saisonnalité
model.detrend <- df_total_weekly_price$price - model.lo
model.season <- loess(model.detrend ~ as.numeric(df_total_weekly_price$week), span = 0.1)  # Lissage plus faible pour la saisonnalité
model.season.lo <- xts(model.season$fitted, order.by = df_total_weekly_price$week)


# Extraction du modèle 
gaussien_model <- ychap.kernel + ychap.season
lo_model <- model.lo + model.season.lo


length(as.numeric(df_total_weekly_price$price))
# Charger les données
n0 <- 300
n1 <- 366 - n0
cac_0 <- as.numeric(df_total_weekly_price$price[1:n0])
cac_1 <- as.numeric(df_total_weekly_price$price[(n0+1):(n0+n1)])
time <- c(1:(n0 + n1))

# Auto-corrélation et corrélation partielle des données
acf(cac_0)
acf(diff(cac_0))
pacf(diff(cac_0))

# Graphique des données où l'on va faire la validation croisée
par(mfrow=c(1,1))
n0 <- length(cac_0)
n1 <- length(cac_1)
plot_predict_part <- ggplot(df_total_weekly_price, aes(x = week, y = price)) +
  geom_line(color = "black") +
  geom_line(aes(y = c(rep(NA, n0), cac_1)), color = "red") +
  labs(title = "Prédiction du prix total des maisons vendues par semaine", y = "Prix total (en €)", x = "Temps") +
  theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
print(plot_predict_part)
ggsave("Results/Prédiction/price_total_price_weekly_predict_part.png", plot = plot_predict_part, width = 8, height = 5, dpi = 300)

# Modèles exponentiels
ets_simple_best <- exp_simple(cac_0, best_alpha)
ets_double_best <- exp_double(cac_0, best_alpha_double)$smooth
# Prédictions des modèles exponentiels
ets_simple_best.forecast <- forecast(ets_simple_best, h=length(cac_1))
ets_double_best.forecast <- forecast(ets_double_best, h=length(cac_1))

# Affichage des prédictions sur le graphique
plot_predict_expo <- ggplot(df_total_weekly_price, aes(x = week, y = price)) +
  geom_line(color = "black") +
  geom_line(aes(y = c(rep(NA, n0), cac_1)), color = "red") +
  geom_line(aes(y = c(rep(NA, n0), ets_simple_best.forecast$mean)), color = "blue") +
  geom_line(aes(y = c(rep(NA, n0), ets_simple_best.forecast$lower[,1])), color = "blue", linetype = "dashed") +
  geom_line(aes(y = c(rep(NA, n0), ets_simple_best.forecast$upper[,1])), color = "blue", linetype = "dashed") +
  geom_line(aes(y = c(rep(NA, n0), ets_double_best.forecast$mean)), color = "orange") +
  geom_line(aes(y = c(rep(NA, n0), ets_double_best.forecast$lower[,1])), color = "orange", linetype = "dashed") +
  geom_line(aes(y = c(rep(NA, n0), ets_double_best.forecast$upper[,1])), color = "orange", linetype = "dashed") +
  labs(title = "Prédiction du prix total des maisons vendues par semaine", y = "Prix total (en €)", x = "Temps") +
  theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
print(plot_predict_expo)
ggsave("Results/Prédiction/price_total_price_weekly_predict_expo.png", plot = plot_predict_expo, width = 8, height = 5, dpi = 300)

# prédiction pour les modèles noyau gaussien et polynômes locaux
# Prédiction pour le noyau gaussien
gaussien_forecast <- forecast(gaussien_model, h = n1)
# Prédiction pour les polynômes locaux
loess_forecast <- forecast(lo_model, h = n1)

# Graphique avec les différentes prédictions
plot_predict_gauss_pol <- ggplot(df_total_weekly_price, aes(x = week, y = price)) +
  geom_line(color = "black") +
  geom_line(aes(y = c(rep(NA, n0), cac_1)), color = "red") +
  geom_line(aes(y = c(rep(NA, n0), gaussien_forecast$mean)), color = "blue") +
  geom_line(aes(y = c(rep(NA, n0), gaussien_forecast$lower[,1])), color = "blue", linetype = "dashed") +
  geom_line(aes(y = c(rep(NA, n0), gaussien_forecast$upper[,1])), color = "blue", linetype = "dashed") +
  geom_line(aes(y = c(rep(NA, n0), loess_forecast$mean)), color = "orange") +
  geom_line(aes(y = c(rep(NA, n0), loess_forecast$lower[,1])), color = "orange", linetype = "dashed") +
  geom_line(aes(y = c(rep(NA, n0), loess_forecast$upper[,1])), color = "orange", linetype = "dashed") +
  labs(title = "Prédiction du prix total des maisons vendues par semaine", y = "Prix total (en €)", x = "Temps") +
  theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Adjust for X and Y labels)
print(plot_predict_gauss_pol)
ggsave("Results/Prédiction/price_total_price_weekly_predict_gauss_pol.png", plot = plot_predict_gauss_pol, width = 8, height = 5, dpi = 300)







## Prévision pour l'avenir ##
# Définir l'horizon de prévision pour le futur (1 an)
future_horizon <- 52  # Par exemple, plus de 52 semaines de prévision (peut être ajusté si nécessaire), soit un an
future_time <- c(1:(n0 + n1 + future_horizon))  # Extension du vecteur de temps

# Faire la prévision pour la période future
future_forecast_loess <- forecast(loess_forecast, h = future_horizon)  
future_forecast_gaussien <- forecast(gaussien_forecast, h = future_horizon)
future_forecast_exp_simple <- forecast(ets_simple_best.forecast, h = future_horizon)
future_forecast_exp_double <- forecast(ets_double_best.forecast, h = future_horizon)

# Créer un dataframe unique contenant toutes les prévisions
df_plot_extended <- data.frame(
  time = future_time,
  actual = c(cac_0, cac_1, rep(NA, future_horizon)),
  loess = c(rep(NA, n0 + n1), future_forecast_loess$mean),
  gaussien = c(rep(NA, n0 + n1), future_forecast_gaussien$mean),
  exp_simple = c(rep(NA, n0 + n1), future_forecast_exp_simple$mean),
  exp_double = c(rep(NA, n0 + n1), future_forecast_exp_double$mean)
)
# Mettre les données au format long pour ggplot
df_long <- df_plot_extended %>%
  pivot_longer(cols = -c(time, actual), names_to = "model", values_to = "forecast")
# Visualisation avec ggplot
plot_predict_future <- ggplot(df_long, aes(x = time)) +
  geom_line(aes(y = actual), color = "black", size = 1, na.rm = TRUE) +  # Données réelles
  geom_line(aes(y = forecast, color = model, linetype = model), size = 1, na.rm = TRUE) +  # Prévisions
  scale_color_manual(values = c("loess" = "blue", "gaussien" = "red", "exp_simple" = "green", "exp_double" = "orange")) +
  scale_linetype_manual(values = c("loess" = "dashed", "gaussien" = "dashed", "exp_simple" = "dashed", "exp_double" = "dashed")) +
  labs(title = "Prévisions pour l'avenir à 1an avec différents modèles", y = "Prix Total", x = "Semaine", color = "Modèle", linetype = "Modèle") +
  theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Ajuster les étiquettes X et Y
print(plot_predict_future)
ggsave("Results/Prédiction/price_total_price_weekly_predict_1_an.png", plot = plot_predict_future, width = 8, height = 5, dpi = 300)









## Validation croisée ## --> rien ne marche 
# Define the rolling window cross-validation function
rolling_window_cv <- function(data, model_func, window_size, horizon, alpha = NULL) {
  n <- length(data)
  errors <- numeric(n - window_size - horizon + 1)
  
  for (i in 1:(n - window_size - horizon + 1)) {
    train <- data[i:(i + window_size - 1)]
    test <- data[(i + window_size):(i + window_size + horizon - 1)]
    
    if (!is.null(alpha)) {
      model <- model_func(train, alpha)
    } else {
      model <- model_func(train)
    }
    
    forecast <- predict(model, h = horizon)$mean
    errors[i] <- mean((test - forecast)^2)  # MSE
  }
  
  return(mean(errors))
}
# Example usage with exponential smoothing models
window_size <- 100
horizon <- 10

# Cross-validation for simple exponential smoothing
mse_simple <- rolling_window_cv(df_total_weekly_price$price, exp_simple, window_size, horizon, alpha = best_alpha)

# Cross-validation for double exponential smoothing
#mse_double <- rolling_window_cv(df_total_weekly_price$price, exp_double, window_size, horizon, alpha = best_alpha_double)

# Cross-validation for Gaussian kernel model
#mse_gaussian <- rolling_window_cv(df_total_weekly_price$price, function(x) { forecast(gaussien_model, h = horizon) }, window_size, horizon)

# Cross-validation for LOESS model
#mse_loess <- rolling_window_cv(df_total_weekly_price$price, function(x) { forecast(lo_model, h = horizon) }, window_size, horizon)

# Print the results
cat("MSE for Simple Exponential Smoothing:", mse_simple, "\n")
#cat("MSE for Double Exponential Smoothing:", mse_double, "\n")
#cat("MSE for Gaussian Kernel Model:", mse_gaussian, "\n")
#cat("MSE for LOESS Model:", mse_loess, "\n")

# Compare the models
results <- data.frame(
  Model = c("Simple Exponential Smoothing"),
  MSE = c(mse_simple)
)
print(results)


# Définition des paramètres
n_cut <- 200  # Nombre de points à couper
start_cut <- 100  # Début de l'intervalle coupé

# Découpage des données
train_x <- time[1:(start_cut-1)]
train_y <- cac_0[1:(start_cut-1)]
cut_x <- time[start_cut:(start_cut + n_cut - 1)]
cut_y <- cac_0[start_cut:(start_cut + n_cut - 1)]

# Ajustement du modèle Gaussien
fit <- ksmooth(train_x, train_y, kernel = "normal", bandwidth = 10, n.points = n_cut) # comme ce qu'on avait avant 
pred_y <- fit$y

# Construction du dataframe pour ggplot
df_plot <- data.frame(time = time, actual = c(cac_0, cac_1))
df_pred <- data.frame(time = cut_x, pred = pred_y)

# Graphique
plot_cross_validation <- ggplot(df_plot, aes(x = time, y = actual)) +
  geom_line(color = "black") +
  geom_line(data = df_pred, aes(x = time, y = pred), color = "blue", size = 1) +
  labs(title = "Prédiction Gaussienne sur une partie de cac_0", y = "Prix Total", x = "Semaine") +
  theme(plot.title = element_text(size = 10), axis.title = element_text(size = 12))  # Ajuster les étiquettes X et Y
print(plot_cross_validation)
ggsave("Results/Prédiction/price_total_price_weekly_cross_validation.png", plot = plot_cross_validation, width = 8, height = 5, dpi = 300)




