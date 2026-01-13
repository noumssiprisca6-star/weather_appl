#include "../include/meteo.h"
#include <SDL3/SDL.h>
#include <cstdlib>
#include <ctime>
#include "../libs/stb/stb_image.h"
#include"../src/SDL3/SDL3_image/SDL_image.h"
#include "../libs/stb/stb_image.h"
#include "../libs/imgui/imgui.h"
#include <iostream>

#include<string>


// Initialisation du temps

void initTime(MeteoTime& time)
{
    time.hour = 6;       // début à 6h
    time.dayIndex = 0;   // 0 = Lundi
    std::srand(std::time(NULL)); // initialiser rand
    time.temperature = getTemperatureForTranche(time.hour);
}

// Nom du jour

const char* getDayName(int dayIndex)
{
     const char* days[NB_JOURS] = {"Lundi","Mardi","Mercredi","Jeudi","Vendredi"};
    return days[dayIndex];
}


// Température par tranche de 5h

int getTemperatureForTranche(int hour)
{
    int tranche = hour / 5; // 0-4 → tranche 0, 5-9 → tranche 1, etc.
    int minT, maxT;

    switch(tranche)
    {
        case 0: minT=-5; maxT=5; break; // 0-4h
        case 1: minT=0; maxT=15; break; // 5-9h
        case 2: minT=10; maxT=30; break; // 10-14h
        case 3: minT=20; maxT=40; break; // 15-19h
        case 4: minT=15; maxT=100; break; // 20-23h
        default: minT=0; maxT=25; break;
    }

    return minT + (std::rand() % (maxT - minT + 1));
}


// Avancer le temps

void advanceOneHour(MeteoTime& time)
{
    time.hour++;
    if (time.hour >= 24)
    {
        time.hour = 0;
        time.dayIndex++;
        if (time.dayIndex >= NB_JOURS)
            time.dayIndex = 0;
    }

    // Mise à jour de la température toutes les 5 heures
    if (time.hour % 4 == 0)
    {
        time.temperature = getTemperatureForTranche(time.hour);
    }
    
}

