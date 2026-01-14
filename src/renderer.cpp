#include"../include/renderer.h"
#include <SDL3/SDL.h>
#include"../src/SDL3/SDL3_image/SDL_image.h"
#include "../libs/stb/stb_image.h"
#include "../libs/imgui/imgui.h"
#include <ctime>
#include<iostream>
#include<vector>
#include <cstdlib>

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




 
//Fonction pour charger une image avec stb_image
/*SDL_Texture* LoadImageTexture(SDL_Renderer* renderer, const char* icon) { 
int width, height, channels; 
// Charge l'image en mémoire 
unsigned char* image_data = stbi_load(icon, &width, &height, &channels, 
4); // Force RGBA 
if (!image_data) { 
std::cerr << "Erreur stb_image: " << stbi_failure_reason() << 
std::endl; 
return nullptr; 
    } 
std::cout << "Image chargée: " << width << "x" << height  
              << 
" (" << channels << " canaux)" << std::endl; 
// Crée une texture SDL 
    SDL_Texture* texture = SDL_CreateTexture( 
        renderer, 
        SDL_PIXELFORMAT_RGBA32, 
        SDL_TEXTUREACCESS_STATIC, 
        width, height 
    ); 
if (!texture) { 
std::cerr << "Erreur création texture: " << SDL_GetError() << std::endl;
        stbi_image_free(image_data); 
return nullptr; 
    } 
// Copie les pixels dans la texture 
    SDL_UpdateTexture(texture, nullptr, image_data, width * 4); 
// Libère la mémoire de stb_image
    stbi_image_free(image_data); 
return texture; 
} 
*/

