
#include "../include/style.h"
#include <SDL3/SDL.h>
#include"../src/SDL3/SDL3_image/SDL_image.h"
#include "../libs/stb/stb_image.h"
#include "../libs/imgui/imgui.h"
#include<vector>
#include<iostream>

  /* cette fonction permet de gerer le style des boutons 
  *avec imgui
  */
enum WeatherView
{

    DAYS,
    TIME,
    LOCATION
};

 //fonction pour le style
void Drawstyle()
{
    WeatherView currentView ;

    
    const char* day = "Lundi";
    const char* time = "14:32";
    const char* location = "Douala, Cameroun";

    //  TITRE 
    ImGui::Spacing();
    ImGui::TextColored(
        ImVec4(0.2f, 0.7f, 1.0f, 1.0f),
        "Bienvenue dans l'application de simulation météo "
    );
    ImGui::Separator();
    ImGui::Spacing();

    //  ZONE MENU VERTICAL 
     //usage d'un imgui child pour creer une fenetre appartenant a une autre 
    ImGui::BeginChild("Menu", ImVec2(180, 300), true);

    ImGui::Spacing();
    if (ImGui::Button("Jours", ImVec2(-1, 45)))
        currentView = DAYS;

    ImGui::Spacing();
    if (ImGui::Button("Heure", ImVec2(-1, 45)))
        currentView = TIME;

    ImGui::Spacing();
    if (ImGui::Button("Lieu", ImVec2(-1, 45)))
        currentView = LOCATION;

    ImGui::EndChild();

    ImGui::SameLine();

    // ZONE CONTENU
    ImGui::BeginChild("Contenu", ImVec2(0, 300), true);

    switch (currentView)
    {
        

        case DAYS:
            ImGui::Text(" Jour actuel");
            ImGui::Separator();
            ImGui::Text("%s", day);
            break;

        case TIME:
            ImGui::Text("Heure actuelle");
            ImGui::Separator();
            ImGui::Text("%s", time);
            break;

        case LOCATION:
            ImGui::Text("Localisation");
            ImGui::Separator();
            ImGui::Text("%s", location);
            break;
    }

    ImGui::EndChild();

    

}
