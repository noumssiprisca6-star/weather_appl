#include <SDL3/SDL.h>
#include"../src/SDL3/SDL3_image/SDL_image.h"
#include <iostream>
#include<vector>
// main.cpp

#include "../libs/stb/stb_image.h"
#include "../libs/imgui/imgui.h"
#include "../libs/imgui/backends/imgui_impl_sdl3.h"
#include "../libs/imgui/backends/imgui_impl_sdlrenderer3.h"
#include "../include/style.h"
#include"../include/meteo.h"
#include"../include/renderer.h"
#include <windows.h>
#include<cstdlib>




// Charge une texture BMP
SDL_Texture* chargerTexture(SDL_Renderer* renderer, const char* chemin)
{
    SDL_Surface* surface = IMG_Load(chemin); // Charge image
    if (!surface) return NULL;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface); // Libère surface
    return texture;
}


  int main() {
    SetConsoleCP(CP_UTF8);
    std::srand(std::time(NULL));
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr <<"Erreur SDL_Init: " << SDL_GetError() << std::endl;
    
    }

    std::cout << "SDL3 initialisé avec succès !!" << std::endl;
 
    SDL_Window* window = SDL_CreateWindow("Meteo VIsuelle", 1600, 900, 0);
    if (!window) {
        std::cerr << "Erreur de creation fenêtre: " << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

   
    if (!renderer) {
        std::cerr << "Erreur de création renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

     IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark();
    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_WindowBg] =ImVec4(1.0f,1.0f,1.0f,1.0f);//blanc
    style.Colors[ImGuiCol_Button]        = ImVec4(0.2f, 0.5f, 0.9f, 1.0f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.3f, 0.6f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_ButtonActive]  = ImVec4(0.1f, 0.4f, 0.8f, 1.0f);

//pour le style des textes

             //les booleens
             bool showstyle = false ;
             bool icon = false ;
        
   

     
       //variable de la boucle principale
   // creation de la surface pour mon fond
   // Charge une texture BMP



SDL_Surface* Surface = IMG_Load("assets/bn.jpg");

//creation de la texture à partir de la surface 
SDL_Texture* texture  = SDL_CreateTextureFromSurface(renderer , Surface);

//destruction de la surface creer
    SDL_DestroySurface(Surface);
    

    MeteoStats stats;
   

    Uint64 lastChange = 0 ;
    


  // Chargement des fonds
    SDL_Texture* fondFroid = chargerTexture(renderer, "assets/Rain.jpg");
    SDL_Texture* fondChaud = chargerTexture(renderer, "assets/OIP (1).jpg");
    SDL_Texture* fondNeige = chargerTexture(renderer, "assets/neige.jpg");
    SDL_Texture* fondPluie = chargerTexture(renderer, "assets/ser.jpg");
    SDL_Texture* fondCrame = chargerTexture(renderer, "assets/ml.jpg");
    
    
    Temperature temperature;
    initTemperature(temperature); // Init température

 
    // Initialisation météo

    MeteoTime time;
    initTime(time);

      Uint32 lastTick = SDL_GetTicks();
     const Uint32 HOUR_DURATION = 2000; // 3000 ms = 3 secondes


        //boucle de jeu
      bool running = true;
       SDL_Event event;
 //boule d'evenement
    while (running) {
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
            //ne place plus le code de ta fenetre ici❌
        }
        /**
         * les frames IMGUI commencent a se faire creer ici sinon il y aura des problemes 
         * lors de l'affichage.
         */

       // Avancer le temps automatiquement toutes les 3 secondes
    

     Uint32 now = SDL_GetTicks();
     if (now - lastTick >= HOUR_DURATION)
     {
        advanceOneHour(time); // avance d'une heure + mise à jour température
        lastTick = now;
      }
        
     
         
        


       //fonction pour modifier la temperature
        updateTemperature(temperature, 10.0f); // Update température

        SDL_RenderClear(renderer); // Nettoyage écran

        // Choix du fond synchronisé avec la température
        SDL_Texture* fondActuel = choisirFond(
            time.temperature,
            fondFroid,
            fondChaud,
            fondPluie,
            fondCrame,
            fondNeige

        );

        if (fondActuel){
            SDL_RenderTexture(renderer, fondActuel, NULL, NULL); // Affiche fond
        }
        //  IMGUI
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        
         
        //fenetre translucide 
        ImGui::SetNextWindowBgAlpha(0.0f); // a 100 % transparente
        //afin de modifier la taille de la fenetre imgui 
        ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_Once);

       /*ImGui::Begin("Controle meteo" , nullptr, ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoTitleBar);

        showstyle = true; 
        if(showstyle){
            Drawstyle();
        }
        
          
         ImGui::Separator();
         ImGui::End();
         ImGui::Render();
*/
        

            
        // Deuxième fenêtre météo
        //fenetre translucide  
        ImGui::SetNextWindowBgAlpha(0.0f); // a 100 % transparente
        //afin de modifier la taille de la fenetre imgui 
        ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_Once);

        ImGui::Begin("Météo" ,nullptr, ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoTitleBar);

        // Bouton pour avancer manuellement d'une heure
        if (ImGui::Button("##")){

        
            advanceOneHour(time);
        // Affichage dynamique avec des polices
        }
         
        
        ImFont* font = io.Fonts->AddFontFromFileTTF("assets/police/RobotoSlab-VariableFont_wght.ttf");
        ImGui::PushFont(font, 35.0f);

        ImGui::Spacing();
        ImGui::TextColored(
        ImVec4(0.0f, 0.0f, 0.5f, 1.0f),
        "Bienvenue dans la simulation météo ");
        ImGui::Spacing();
        ImGui::Separator();

        ImGui::PushFont(font, 85.0f);
        ImGui::Text(" %d °C", time.temperature);
        ImGui::PopFont();
        ImGui::Text("Jour : %s", getDayName(time.dayIndex));
        ImGui::Text("Heure : %d h", time.hour);
        ImGui::PopFont();
    SDL_RenderTexture(renderer, fondActuel, NULL, NULL); // Affiche fond

        //deuxieme fenetre imgui 
        ImGui::Spacing();
     //fenetre translucide 
        ImGui::SetNextWindowBgAlpha(0.0f); // a 100 % transparente
        //afin de modifier la taille de la fenetre imgui 
    ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_Once);
    ImFont* style = io.Fonts->AddFontFromFileTTF("assets/police/ArchivoBlack-Regular.ttf");
        ImGui::PushFont(style, 30.0f);
 
    ImGui::Begin("Indicateurs Meteo"); // Fenêtre principale
    updateMeteoStats (stats ,12.0f);
    ImGui::BeginChild("Pluie", ImVec2(180, 100), true ); // Fenêtre pluie
    ImGui::Text(" Pluie");
    ImGui::Text("%d %%", stats.pluie);
    ImGui::EndChild();

    ImGui::SameLine();
   
    ImGui::BeginChild("Humidité", ImVec2(180, 100), true); // Fenêtre humidité
    ImGui::Text(" Humidite");
    ImGui::Text("%d %%", stats.humidite);
    ImGui::EndChild();
    

    ImGui::BeginChild("Air", ImVec2(180, 100), true); // Fenêtre air
    ImGui::Text(" Air");
    ImGui::Text("%d %%", stats.air);
    ImGui::EndChild();

    ImGui::SameLine();



    ImGui::BeginChild("Ultra V", ImVec2(180, 100), true); // Fenêtre UV
    ImGui::Text("UV");
    ImGui::Text("%d %%", stats.uv);
    ImGui::PopFont();
    ImGui::EndChild();
    ImGui::End(); // Fin fenêtre principale
     
           
        
   


         ImGui::Separator();
        ImGui::End();
         ImGui::Render();
 
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(),renderer);
        SDL_RenderPresent(renderer);

       }

    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
    

    //effface toutes les fenetres creer
    // Libération ressources
    SDL_DestroyTexture(fondFroid);
    SDL_DestroyTexture(fondChaud);

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << " sayonara! " << std::endl;
    return 0;


}
/* SDL_Surface* Surface[3]; 
Surface[0] = IMG_Load("assets/ml.jpg");
Surface[1] = IMG_Load("assets/ui.jpg"); 
Surface[2] = IMG_Load("assets/ser.jpg");
//creation de la texture à partir de la surface 
SDL_Texture* texture[3] ;
for(int i = 0 ; i<3 ; i++){
texture[i] = SDL_CreateTextureFromSurface(renderer , Surface[i]);
} 
//destruction de la surface creer 

if(Surface[0]){
    SDL_DestroySurface(Surface[0]);
    Surface[0]= nullptr;

}
if(Surface[1]){
    SDL_DestroySurface(Surface[1]);
    Surface[1]= nullptr;
}
if(Surface[2]){
    SDL_DestroySurface(Surface[2]);
    Surface[2]= nullptr;

}*/
/*  for(int i = 0 ; i<3 ; i++){
   SDL_DestroyTexture(texture[back]);
    }
    if(texture[0]){
        SDL_DestroyTexture(texture[0]);
        texture[0] = nullptr;
    }
    if(texture[1]){
        SDL_DestroyTexture(texture[1]);
        texture[1] = nullptr;
    }
    
    if(texture[2]){
        SDL_DestroyTexture(texture[2]);
        texture[2] = nullptr;
    }
    
    
    */