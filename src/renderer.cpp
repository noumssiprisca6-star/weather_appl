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
SDL_Texture* choisirFond( float temperature,SDL_Texture* fondFroid,SDL_Texture* fondChaud ,SDL_Texture* fondNeige ,SDL_Texture* fondPluie ,SDL_Texture* fondNuit)
{
    
    if (temperature < 0.0f){
        return fondNeige;//temps neigeux
     } // Temps froid
      return fondChaud;  // Temps chaud
     
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
void drawMeteo(const MeteoStats& stats)
{
    
        
     ImGuiIO& io = ImGui::GetIO();
    ImFont* font = io.Fonts->AddFontFromFileTTF("assets/police/RobotoSlab-VariableFont_wght.ttf");
    ImGui::PushFont(font, 35.0f);
    ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_Once);

    ImGui::Begin("Indicateurs Meteo"); // Fenêtre principale
    
    ImGui::BeginChild("Pluie", ImVec2(180, 80), true ); // Fenêtre pluie
    ImGui::Text(" Pluie");
    ImGui::Text("%d %%", stats.pluie);
    ImGui::EndChild();

    ImGui::SameLine();
   
    ImGui::BeginChild("Humidite", ImVec2(180, 80), true); // Fenêtre humidité
    ImGui::Text("Humidite");
    ImGui::Text("%d %%", stats.humidite);
    ImGui::EndChild();
    

    ImGui::BeginChild("Air", ImVec2(180, 80), true); // Fenêtre air
    ImGui::Text(" Air");
    ImGui::Text("%d %%", stats.air);
    ImGui::EndChild();

    ImGui::SameLine();



    ImGui::BeginChild("UV", ImVec2(180, 80), true); // Fenêtre UV
    ImGui::Text("UV");
    ImGui::Text("%d %%", stats.uv);
    ImGui::EndChild();
    ImGui::PopFont();
    ImGui::End(); // Fin fenêtre principale
    
}




 
