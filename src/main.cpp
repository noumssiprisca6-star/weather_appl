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
#include <windows.h>
#include<cstdlib>




  int main() {
    SetConsoleCP(CP_UTF8);
    
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr <<"Erreur SDL_Init: " << SDL_GetError() << std::endl;
    
    }

    std::cout << "SDL3 initialisé avec succès !!" << std::endl;
 
    SDL_Window* window = SDL_CreateWindow("Meteo VIsuelle", 800, 600, SDL_WINDOW_RESIZABLE);
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
SDL_Surface* Surface[3]; 
Surface[0] = IMG_Load("assets/background.jpg");
Surface[1] = IMG_Load("assets/nb.jpg"); 
Surface[2] = IMG_Load("assets/cy.jpg");
//creation de la texture à partir de la surface 
SDL_Texture* texture[3] ;
for(int i = 0 ; i<3 ; i++){
texture[i] = SDL_CreateTextureFromSurface(renderer , Surface[i]);
} 
//destruction de la surface creer 
SDL_DestroySurface(Surface[0]);
Uint64 lastChange = 0 ;
int back =0;



 // =======================
    // Initialisation météo
    // =======================
    MeteoTime time;
    initTime(time);

Uint32 lastTick = SDL_GetTicks();
const Uint32 HOUR_DURATION = 2000; // 3000 ms = 3 secondes


    //boucle de jeu
    bool running = true;
    SDL_Event event;

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
        if(now - lastChange >=8000){
            back =(back + 1) % 3 ;
            lastChange = now ;
        }
        

        //  IMGUI
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
        //fenetre translucide 
        ImGui::SetNextWindowBgAlpha(0.0f); // a 100 % transparente
        

        //afin de modifier la taille de la fenetre imgui 
        ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_Once);

            ImGui::Begin("Controle meteo" , nullptr, ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoTitleBar);
            
          showstyle = true; 
        if(showstyle){
            Drawstyle();
        }
        
        
        ImGui::End();
        


         SDL_RenderTexture(renderer, texture[back],nullptr , nullptr);
            
        // Deuxième fenêtre météo
        //fenetre translucide 
        ImGui::SetNextWindowBgAlpha(0.0f); // a 100 % transparente
        

        //afin de modifier la taille de la fenetre imgui 
        ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_Once);
        ImGui::Begin("Météo" ,nullptr, ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoTitleBar);

        // Bouton pour avancer manuellement d'une heure
        if (ImGui::Button("METEO"))
            advanceOneHour(time);

        // Affichage dynamique
        ImGui::Text("Jour : %s", getDayName(time.dayIndex));
        ImGui::Text("Heure : %d h", time.hour);
        ImGui::Text("Température : %d °C", time.temperature);

        
        
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
   SDL_DestroyTexture(texture[back]);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << " sayonara! " << std::endl;
    return 0;


}
