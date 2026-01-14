#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>
#include"../src/SDL3/SDL3_image/SDL_image.h"
#include "../libs/stb/stb_image.h"
#include "../libs/imgui/imgui.h"
#include<vector>



// Données météo secondaires
struct MeteoStats
{
    int pluie;      // Fréquence pluie (%)
    int humidite;   // Humidité (%)
    int air;        // Qualité de l'air (%)
    int uv;         // Niveau UV (%)
};

// Initialise les stats météo
void initMeteoStats(MeteoStats& stats);

// Met à jour les stats de façon aléatoire
void updateMeteoStats(MeteoStats& stats, float deltaTime);

// Dessine les fenêtres ImGui
void drawMeteo(const MeteoStats& stats);


#endif
