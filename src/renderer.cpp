#include"../include/renderer.h"
#include "../include/meteo.h"
#include <SDL3/SDL.h>
#include"../src/SDL3/SDL3_image/SDL_image.h"
#include "../libs/stb/stb_image.h"
#include "../libs/imgui/imgui.h"
#include <ctime>
#include<iostream>
#include<vector>
#include <cstdlib>









// Sélection du fond selon la température
SDL_Texture* choisirFond( float temperature,SDL_Texture* fondFroid,SDL_Texture* fondChaud ,SDL_Texture* fondNeige ,SDL_Texture* fondPluie  ,SDL_Texture* fondCrame )
{
    
    if ( temperature <= 0.0f && temperature <= 5.0f){
        return fondNeige;//temps neigeux
     }else if(temperature <= 15.0f && temperature <= 22.0f ){
        return fondFroid; //temps froid 
     }else if (temperature >= 24.0f && temperature <= 30.0f ){
        return fondChaud; //temps chaud
     }
     // Temps froid
      return fondCrame;  // Temps chaud
     
}


// Initialise les valeurs
void initMeteoStats(MeteoStats& stats)
{ 
   
    stats.pluie = std:: rand() % 100 + 1;      // 0 à 99
    stats.humidite = rand() % 100;   // 0 à 99
    stats.air = rand() % 100;        // 0 à 99
    stats.uv = rand() % 100;         // 0 à 99
}

// Met à jour les valeurs toutes les 2 secondes
void updateMeteoStats(MeteoStats& stats, float deltaTime)
{
    static float timer = 1.0f;       // Timer interne
    timer += deltaTime;              // Avance le temps

    if ( timer >= 6000)               // Toutes les 6 secondes
    {
        timer = 0.0f;                // Reset timer
        stats.pluie = rand() % 100 + 1 ;
        stats.humidite = rand() % 100 + 1;
        stats.air = rand() % 100 + 1 ;
        stats.uv = rand() % 100 + 1; 
    }
}

// Dessine les fenêtres enfants ImGui
