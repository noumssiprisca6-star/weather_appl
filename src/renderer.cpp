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
SDL_Texture* choisirFond( const MeteoTime& time,SDL_Texture* fondFroid,SDL_Texture* fondChaud ,SDL_Texture* fondNeige ,SDL_Texture* fondPluie  ,SDL_Texture* fondCrame , SDL_Texture* fondeclairs , SDL_Texture* fondnuage , SDL_Texture* fondtour ,SDL_Texture* fondbrou ,SDL_Texture* fondflocon )

{  
    
      // les conditions de changement d'images
    if ( time.temperature <= 5 ){
         return fondflocon;//temps neigeux
    }else if (time.temperature <= 16){
        return fondNeige;//temps neigeux
    }else if ( time.temperature <= 24 ){
        return fondeclairs ; //le ciel vibre 
     }else if(time.temperature <= 30){
        return fondbrou; //temps froid 
         }else if(time.temperature <= 35){
            return fondtour ; //tourbillon 
     }else if(time.temperature <= 36){
        return fondnuage ; //beau temps
     }else if (time.temperature <= 38){
        return fondChaud; //temps chaud
     }else{
      return fondCrame;  // Temps chaud
     }
}
//pour charger des icones
 // Charge une texture BMP
SDL_Texture* changerIcon(SDL_Renderer* renderer, const char* icon)
{
    SDL_Surface* surface = IMG_Load(icon); // Charge image
    if (!surface) return NULL;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Texture* nuit =  SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface); // Libère surface
    return texture;

}
  