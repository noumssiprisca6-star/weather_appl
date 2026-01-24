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
    SDL_Texture* nuit =  SDL_CreateTextureFromSurface(renderer, surface);
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
 
    SDL_Window* window = SDL_CreateWindow("Meteo VIsuelle", 1800, 900, 0);
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
    bool fond = false ;
    bool fonf = false ;
    bool coucher = false ;  
    bool lever = false ;
    bool couchersoleil = false ;

     
       //variable de la boucle principale
   // creation de la surface pour mon fond
   // Charge une texture BMP



 SDL_Surface* Surface = IMG_Load("assets/bn.jpg");

 //creation de la texture à partir de la surface 
 SDL_Texture* texture  = SDL_CreateTextureFromSurface(renderer , Surface);

 //destruction de la surface creer
    SDL_DestroySurface(Surface);
    
    int cheflieux = 0 ;


    Uint64 lastChange = 0 ;


  // Chargement des fonds
    SDL_Texture* fondFroid = chargerTexture(renderer, "assets/flocon.jpg");
    SDL_Texture* fondChaud = chargerTexture(renderer, "assets/yu.jpg");
    SDL_Texture* fondNeige = chargerTexture(renderer, "assets/crame.jpg");
    SDL_Texture* fondeclairs = chargerTexture(renderer, "assets/ph.jpg");
    SDL_Texture* fondPluie = chargerTexture(renderer, "assets/ser.jpg");
    SDL_Texture* fondCrame = chargerTexture(renderer, "assets/ml.jpg");
    SDL_Texture* fondNuit = chargerTexture(renderer, "assets/pl.jpg");
    SDL_Texture* fondnuage = chargerTexture(renderer, "assets/OIP (2).jpg");
    SDL_Texture* fondtour = chargerTexture(renderer, "assets/ji.jpg");
    SDL_Texture* fondbrou = chargerTexture(renderer, "assets/OIP.jpg");
    SDL_Texture* fondflocon = chargerTexture(renderer, "assets/neigep.jpg");
    SDL_Texture* fondcoucher = chargerTexture(renderer, "assets/soend.jpg");
    

    // chargement des icons
    SDL_Texture* iconpluie = changerIcon(renderer , "assets/yt.png ");
    SDL_Texture* iconnuit = changerIcon(renderer , "assets/nig.png ");
    SDL_Texture* iconjour = changerIcon(renderer , "assets/td.png ");
    SDL_Texture* iconcoucher = changerIcon(renderer , "assets/tel.png ");
    SDL_Texture* iconuv = changerIcon(renderer,"assets/rayo.png");
    SDL_Texture* iconhum = changerIcon(renderer, "assets/hum.png");
    SDL_Texture* iconvent = changerIcon(renderer, "assets/com.png");
    SDL_Texture* iconfloc = changerIcon(renderer , "assets/cop.png");
    SDL_Texture* iconsoleil = changerIcon(renderer , "assets/bv.png");
    SDL_Texture* iconsun = changerIcon(renderer ,"assets/ico.png");
    SDL_Texture* iconnuage = changerIcon(renderer , "assets/cloud.png");
    SDL_Texture* iconensol = changerIcon(renderer , "asssets/tel.png");
    SDL_Texture* iconlev = changerIcon(renderer , "assets/co.png");
    SDL_Texture* icontime = changerIcon(renderer , "assets/time.png");
    SDL_Texture* iconcarte = changerIcon(renderer , "assets/carte.png");
    SDL_Texture* iconmaps = changerIcon(renderer , "assets/maps.png");
    SDL_Texture* iconday = changerIcon(renderer , "assets/day.png");
    SDL_Texture* icontu = changerIcon(renderer ,"assets/iop.png");

    Temperature temperature;
    initTemperature(temperature); // Init température

 
    // Initialisation météo

    MeteoTime time;
    initTime(time);

    Uint32 lastTick = SDL_GetTicks();
    const Uint32 HOUR_DURATION = 2000; // 3000 ms = 3 secondes
    Uint32 deltaTime = SDL_GetTicks();

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
     if (now - deltaTime >= 3000){
        gestion (time );
        updateMeteotime(time , 10.0f);
        deltaTime = now ;
            
      }
        


       //fonction pour modifier la temperature
        updateTemperature(temperature, 10.0f); // Update température
        

        SDL_RenderClear(renderer); // Nettoyage écran

        // Choix du fond synchronisé avec la température
        SDL_Texture* fondActuel = choisirFond(
            time,
            fondFroid,
            fondChaud,
            fondPluie,
            fondCrame,
            fondNeige,
            fondeclairs,
            fondnuage ,
            fondtour,
            fondbrou ,
            fondflocon
         
        );

        if(fond){
        fondActuel = fondNuit ;
        }else if (fonf){
        fondActuel = fondActuel ;
        }else if (coucher){
        fondActuel = fondcoucher;
        }
           
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


   

       
        
        //  fenêtre 1 météo
        //fenetre translucide  
        ImGui::SetNextWindowBgAlpha(0.0f); // a 100 % transparente
        //afin de modifier la taille de la fenetre imgui 
        ImGui::SetNextWindowSize(ImVec2(450, 450), ImGuiCond_Once);
       


        ImGui::Begin("Météo" ,nullptr, ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoBackground
        );

     //nullptr, ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoBackground
        
        // Bouton pour avancer manuellement d'une heure
        if (ImGui::Button("##")){

        
            advanceOneHour(time);
        // Affichage dynamique avec des polices
        }
       
   
        const float CIRCLE_SIZE = 450.0f;

       ImGui::SetNextWindowSize(ImVec2(CIRCLE_SIZE, CIRCLE_SIZE), ImGuiCond_Always);
       ImGui::SetNextWindowBgAlpha(0.0f);
       ImDrawList* draw = ImGui::GetWindowDrawList();

       ImVec2 pos = ImGui::GetWindowPos();
       ImVec2 size = ImGui::GetWindowSize();

       ImVec2 center = ImVec2(
       pos.x + size.x * 0.5f,
       pos.y + size.y * 0.5f
      );

      float radius = size.x * 0.5f;

      // Couleur du cercle (fond)
       draw->AddCircleFilled(
      center,
      radius,
      IM_COL32(255, 255, 255, 20), // gris foncé semi-transparent
      64
      );
      // contour


  
        
        ImFont* font = io.Fonts->AddFontFromFileTTF("assets/police/RobotoSlab-VariableFont_wght.ttf");
        ImGui::PushFont(font, 50.0f);
        
        ImGui::Spacing();
       
        ImGui::Spacing();
        ImGui::Separator();
         ImGui::SetWindowFontScale(1.8f);
         
        ImGui::PushFont(font, 90.0f);
        ImGui::SetCursorPosY(size.y* 0.25f);
        ImGui::SetCursorPosX(size.x* 0.25f);
        // Déterminer la couleur du texte selon la température
       ImVec4 textColor;
     if (time.temperature <= 0)
       textColor = ImVec4(0.5f, 0.7f, 1.0f, 1.0f); // bleu froid
     else if (time.temperature <= 20)
     textColor = ImVec4(0.6f, 0.8f, 1.0f, 1.0f); // bleu clair
      else if (time.temperature <= 40)
      textColor = ImVec4(1.0f, 0.8f, 0.3f, 1.0f); // jaune
     else if (time.temperature <= 70)
      textColor = ImVec4(1.0f, 0.55f, 0.2f, 1.0f); // orange
     else
       textColor = ImVec4(1.0f, 0.3f, 0.3f, 1.0f); // rouge chaud

      // Texte centré
     char tempText[16];
      sprintf(tempText, "%d°C", time.temperature);

     ImVec2 textSize = ImGui::CalcTextSize(tempText);
      draw->AddText(
      ImVec2(center.x - textSize.x * 0.5f, center.y - textSize.y * 0.5f),
       ImColor(textColor),
      tempText
      );
        ImGui::PopFont();
         ImGui::Spacing();

         
       //fenetre 2 translucide  
        ImGui::SetNextWindowBgAlpha(0.0f); // a 100 % transparente
        //afin de modifier la taille de la fenetre imgui 
        ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_Once);
       

        ImGui::Begin("#" ,nullptr, ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoBackground  );

        ImGui :: TextColored( ImVec4(0.6f, 0.95f , 1.0f , 1.0f), "  %s", getDayName(time.dayIndex)); 
         ImGui:: Image((void*)iconday,ImVec2(60,60));
        ImGui :: Text("HEURE : %d h", time.hour); 
        ImGui:: Image((void*)icontime ,ImVec2(60,60));
        if (time.hour == 17 ){
    
           coucher = true ;
           if (coucher){
            fondActuel = fondcoucher;
          }
          
          ImGui ::Text("coucher de soleil");
          ImGui:: Image((void*)iconcoucher ,ImVec2(50,50));
        }
        

       // le jour de 6h à 18
         if(time.hour >= 23 || time.hour <=19) { 
            fonf = true ;
            fond = false ;
            coucher = false ;
        
         ImGui::Text("JOUR") ;
         ImGui:: Image((void*)iconjour ,ImVec2(50,50));

         }else{
            // checkbox cest pour les bouton avec booleen & booleen
            fonf = false;
            coucher = false ;
            fond = true ;
            ImGui::Text("NUIT" );
           ImGui:: Image((void*)iconnuit ,ImVec2(50,50));
        } 

        
        ImGui::End();
       
        ImGui::Spacing();  
        ImGui::PopFont();
     SDL_RenderTexture(renderer, fondActuel, NULL, NULL); // Affiche fond

        //deuxieme fenetre imgui 
        ImGui::Spacing();
     //fenetre translucide 
        ImGui::SetNextWindowBgAlpha(0.0f); // a 100 % transparente
        //afin de modifier la taille de la fenetre imgui 

       ImGui::SetNextWindowSize(ImVec2(900, 700), ImGuiCond_Once);
       ImFont* style = io.Fonts->AddFontFromFileTTF("assets/police/ArchivoBlack-Regular.ttf");
       ImGui::PushFont(style, 30.0f);
   
      //fenetre 3
      ImGui::Begin("Indicateurs Meteo" ,nullptr, ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoBackground);
           
        // Fenêtre principale
    
        ImGui::BeginChild("Pluie", ImVec2(190, 130), false); // Fenêtre pluie
        ImGui::Text(" Pluie");
        ImGui:: Image((void*)iconpluie ,ImVec2(50,50));
        ImGui::Text("%d %%", time.pluie);
        ImGui::EndChild();

        ImGui::SameLine();
   
        ImGui::BeginChild("Humidité", ImVec2(190, 130), false); // Fenêtre humidité
        ImGui::Text(" Humidité");
        ImGui:: Image((void*)iconhum ,ImVec2(40,40));
        ImGui::Text("%d %%", time.humidite);
        ImGui::EndChild();

        ImGui::SameLine();
    
        ImGui::BeginChild("Vent", ImVec2(190, 130), false); // Fenêtre air
       ImGui::Text(" Vent");
       ImGui:: Image((void*)iconvent ,ImVec2(40,40));
       ImGui::Text("%d %%", time.vent);
       ImGui::EndChild();

       ImGui::SameLine();

     //fenetre translucide  
     ImGui::SetNextWindowBgAlpha(0.0f); // a 100 % transparente
       //afin de modifier la taille de la fenetre imgui 
     ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_Once);

     ImGui::BeginChild("Ultra V", ImVec2(250, 180), false); // Fenêtre UV
     ImGui::Text("UV");
     ImGui:: Image((void*)iconuv ,ImVec2(50,50));
     ImGui::Text("%d %%", time.uv);
     ImGui::EndChild();

     
      ImGui::BeginChild("Lever de soleil", ImVec2(270, 100), false); // Fenêtre humidité
   
      ImGui::TextColored(ImVec4(0.9f, 0.95f , 1.0f , 1.0f) , "lever de soleil: 6h ");
      ImGui::Image((void*)iconlev ,ImVec2(40,40));
      ImGui::EndChild();



     ImGui::BeginChild("coucher de soleil", ImVec2(340, 280), false); // Fenêtre humidité
     ImGui::TextColored(ImVec4(0.9f, 0.95f , 1.0f , 1.0f) ,"coucher de soleil: 18h ");
     ImGui:: Image((void*)iconjour ,ImVec2(40,40));
     ImGui::EndChild();

     ImGui::End(); // Fin fenêtre principale
     

      //fenetre translucide 
        ImGui::SetNextWindowBgAlpha(0.0f); // a 100 % transparente
        //afin de modifier la taille de la fenetre imgui 

       ImGui::SetNextWindowSize(ImVec2(300, 900), ImGuiCond_Once);
     //autre fenetre
     ImGui::Begin("Prévisions météo" ,nullptr, ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoBackground );

      // ---------- Prévision 1 ----------
     ImGui::BeginChild("p1", ImVec2(270, 200), true);
     ImGui::Text(" Lundi : 8h");
     ImGui::TextColored(ImVec4(1.00f,0.84f,0.31f,1.0f),"Garoua");
     ImGui::Text(" Soleil");
      ImGui:: Image((void*)iconjour ,ImVec2(35,35));
     ImGui::Text(" 32 °C");
      ImGui::EndChild();

      ImGui::Spacing();

     // ---------- Prévision 2 ----------
     ImGui::BeginChild("p2", ImVec2(270, 200), true);
      ImGui::Text("Mardi : 9h");
     ImGui::Text("Maroua");
      ImGui::TextColored(ImVec4(0.69f,0.75f,0.77f,1.0f)," Nuageux");
       ImGui:: Image((void*)iconnuage ,ImVec2(35,35));
      ImGui::Text(" 30 °C");
      ImGui::EndChild();

      ImGui::Spacing();

      // ---------- Prévision 3 ----------
     ImGui::BeginChild("p3", ImVec2(270, 200), true);
     ImGui::Text("Mercredi : 10h");
     ImGui::Text(" Douala");
     ImGui::TextColored(ImVec4(0.31f,0.76f,0.97f,1.0f), "Pluie");
      ImGui:: Image((void*)iconpluie ,ImVec2(35,35));
     ImGui::Text("26 °C");
      ImGui::EndChild();

       ImGui::Spacing();

     // ---------- Prévision 4 ----------
      ImGui::BeginChild("p4", ImVec2(270, 200), true);
      ImGui::Text("Jeudi : 11h");
      ImGui::Text("Yaounde");
      ImGui::TextColored(ImVec4(0.36f,0.21f,0.69f,1.0f),"Orage");
       ImGui:: Image((void*)icontu,ImVec2(35,35));
     ImGui::Text("25 °C");
     ImGui::EndChild();

     ImGui::Spacing();

     // ---------- Prévision 5 ----------
      ImGui::BeginChild("p5", ImVec2(270, 200), true);
     ImGui::Text(" Vendredi : 12h");
     ImGui::Text(" Bamenda");
     ImGui::TextColored( ImVec4(0.38f,0.46f,0.55f,1.0f)," Nuageux");
      ImGui:: Image((void*)iconnuage ,ImVec2(35,35));
     ImGui::Text(" 24 °C");
      ImGui::EndChild();

     ImGui::Spacing();

// ---------- Prévision 6 ----------
     ImGui::BeginChild("p6", ImVec2(270, 200), true);
     ImGui::Text(" Samedi : 8h");
      ImGui::TextColored(ImVec4(1.00f,0.84f,0.31f,1.0f),"Bafoussam");
      ImGui::Text(" Soleil");
       ImGui:: Image((void*)iconlev ,ImVec2(35,35));
      ImGui::Text(" 27 °C");
      ImGui::EndChild();

     ImGui::Spacing();

      // ---------- Prévision 7 ----------
      ImGui::BeginChild("p7", ImVec2(270, 200), true);
       ImGui::Text("  Dimanche : 9h");
        ImGui::Text(" Garoua");
        ImGui::TextColored(ImVec4(0.70f,0.90f,0.99f,1.0f)," Venteux");
         ImGui:: Image((void*)iconvent ,ImVec2(35,35));
       ImGui::Text(" 29 °C");
       ImGui::EndChild();

      ImGui::End();
     // pour afficher un message
     ImGui::Begin("message" ,nullptr, ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoBackground
     )  ; 
        //fenetre texte

     ImGui::Text("Etat Actuel ");
     switch(etat(time)){

      case Neigeux :
      
      ImGui :: TextColored(ImVec4(0.75f ,0.75f ,0.75f ,1.0f) , "NEIGEUX");
      ImGui:: Image((void*)iconfloc ,ImVec2(50,50));
      break ;

      case Nuageux:
      ImGui :: TextColored(ImVec4(0.7f , 0.7f ,0.7f ,1.0f) , "NUAGEUX");
           ImGui:: Image((void*)iconnuage,ImVec2(50,50));
      break;

      case Ensolleille :

      ImGui :: TextColored(ImVec4(1.0f , 0.9f ,0.3f ,1.0f) , "CHALEUR");
         ImGui:: Image((void*)iconsun,ImVec2(50,50));
      break;

      case Leger_Soleil :
      ImGui:: TextColored(ImVec4(0.38f ,0.38f ,0.38f ,0.75f) , "chaotique");
       ImGui:: Image((void*)icontu,ImVec2(50,50));
      break;

      case Canicule :
 
     ImGui :: TextColored(ImVec4(0.9f , 0.2f ,0.2f ,1.0f) , "CANICULE");
     ImGui:: Image((void*)iconsun,ImVec2(50,50));
      break;
    

     }
     
     ImGui::PopFont();
     ImGui::End();
    


     ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_Once);
     //fenetre translucide  
     ImGui::SetNextWindowBgAlpha(0.0f); // a 100 % transparente
        //afin de modifier la taille de la fenetre imgui 
         
        ImFont* theme = io.Fonts->AddFontFromFileTTF("assets/police/Rubik_Storm/RubikStorm-Regular.ttf");
        ImGui::PushFont(font, 50.0f);
        //fenetre 4
     ImGui::Begin("Region du Cameroun" ,nullptr, ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoBackground
         );
     chefLieux();
     ImGui::PushFont(font, 60.0f);
     ImGui:: Image((void*)iconcarte,ImVec2(90,90));
     ImGui::TextColored(ImVec4(0.6f ,0.95f ,1.0f,1.0f) ,"%s" , changelieu() );
     ImGui:: Image((void*)iconmaps,ImVec2(90,90));
     ImGui::Text("temperature actuelle : %d °C ", time.temperature);
     ImGui::PopFont();
     ImGui::Separator();
   
     ImGui::PopFont();
     ImGui::End () ;
    

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
    SDL_DestroyTexture(fondPluie);
    SDL_DestroyTexture(fondCrame);
    SDL_DestroyTexture(fondCrame);
    SDL_DestroyTexture( fondNeige);
    SDL_DestroyTexture( fondeclairs);
    SDL_DestroyTexture( fondnuage );
    SDL_DestroyTexture(fondtour);
    SDL_DestroyTexture ( fondbrou) ;
    SDL_DestroyTexture (fondflocon);
    SDL_DestroyTexture(iconpluie);
    SDL_DestroyTexture(iconnuit);
    SDL_DestroyTexture(iconcoucher);
    SDL_DestroyTexture(iconjour);
    SDL_DestroyTexture(iconuv);
    SDL_DestroyTexture(iconhum);
    SDL_DestroyTexture(iconvent);
    SDL_DestroyTexture(iconfloc);
    SDL_DestroyTexture(iconsoleil);
    SDL_DestroyTexture(iconsun);
    SDL_DestroyTexture(iconnuage);
    SDL_DestroyTexture(iconensol);
    SDL_DestroyTexture(iconlev);
    SDL_DestroyTexture(icontime);
    SDL_DestroyTexture(iconcarte);
    SDL_DestroyTexture(iconmaps);
    SDL_DestroyTexture(iconday);
    SDL_DestroyTexture(icontu);

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << " sayonara! " << std::endl;
    return 0;


}
