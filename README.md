#  Météo Visuelle 

## Description

Ce projet est une simulation de météo visuelle développée en C++ avec SDL3 et Dear ImGui.
Il simule l’écoulement du temps (heures , chef lieux et jours de lundi à vendredi) et fait varier une température
affichée graphiquement dans une interface ImGui.

La météo est représentée visuellement par un cercle blanc transparent et un texte dont la couleur
change en fonction de la température.



## Objectifs

- Simuler le passage du temps
- Gérer les jours de la semaine (lundi à vendredi)
- Générer une température dynamique
- Afficher l’heure, le jour et la température
- Utiliser SDL3 et ImGui ensemble
- Créer une visualisation météo simple et claire



## Fonctionnalités

- Avancement automatique des heures
- Changement automatique des jours
- changement automatique des regions
- Température comprise entre -5°C et 100°C
- Cercle ImGui blanc et transparent
- Couleur du texte de la température dynamique
- Fenêtre ImGui dédiée à la météo
- Possibilité de changer le fond SDL selon la température


## Structure du projet
'''
# Weather_appl

Application de simulation météo développée en C++ avec SDL3 et ImGui.

Weather_appl/
├── .git/               # Dépôt Git (historique des versions)
├── assets/             # Ressources du projet
│   ├── images/         # Images météo (soleil, pluie, nuages, etc.)
│   ├── fonts/          # Polices d’écriture
│   └── sounds/         # Sons (vent, pluie, orage...)
│
├── build/              # Fichiers générés à la compilation
│   └── (binaires, cache, etc.)
│
├── libs/               # Bibliothèques externes
│   ├── SDL3/
│   └── imgui/
│
├── include/            # Fichiers d’en-tête (.h / .hpp)
│   ├── Renderer.hpp
│   ├── Meteo.hpp
│   └── son.hpp
│
├── src/                # Code source (.cpp)
│   ├── main.cpp
│   ├── Renderer.cpp
│   ├── Meteo.cpp
│   └── Son.cpp
│
├── .gitignore          # Fichiers à ignorer par Git
├── CMakeLists.txt      # Configuration de build (si tu utilises CMake)
└── README.md           # Documentation du projet
'''
---

## Interface

L’interface affiche :
- Le jour de la semaine
- L’heure
- La température
- Un cercle blanc transparent
- Un texte coloré selon la température

---

## Améliorations possibles

- Ajouter des icônes météo
- Ajouter des animations (pluie, soleil, vent)
- Ajouter des sons
- Ajouter un mode manuel
- Améliorer le rendu graphique

---

## Auteur
NOUMSSI TIATSAP 
## ENCADREUR
M.TEUGUIA

Projet réalisé à des fins pédagogiques pour l’apprentissage du C++,
de SDL3 et de Dear ImGui.
##  UNIVERS DU GAME PROGRAMMING

