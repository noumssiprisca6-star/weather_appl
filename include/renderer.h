#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>
#include"../src/SDL3/SDL3_image/SDL_image.h"
#include "../libs/stb/stb_image.h"
#include"../include/meteo.h"
#include "../libs/imgui/imgui.h"
#include<vector>



// Sélection du fond selon la température
SDL_Texture* choisirFond( const MeteoTime& time ,SDL_Texture* fondFroid, SDL_Texture* fondChaud , SDL_Texture* fondNeige ,SDL_Texture* fondPluie ,SDL_Texture* fondCrame  , SDL_Texture* fondeclairs , SDL_Texture* fondnuage , SDL_Texture* fondtour ,SDL_Texture* fondbrou  ,SDL_Texture* fondflocon );
// Structure pour le temps

   SDL_Texture* changerIcon(SDL_Renderer* renderer, const char* icon);


#endif
