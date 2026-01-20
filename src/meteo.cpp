#include "../include/meteo.h"
#include"../include/renderer.h"
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
    std::srand(std::time(NULL)); // initialiser rand
    time.hour = 6;       // début à 6h
    time.dayIndex = 0;   // 0 = Lundi
    time.temperature = getTemperatureForTranche(time.hour);
    time.pluie = std:: rand() % 100 + 1;      // 0 à 99
    time.humidite = std :: rand() % 100;   // 0 à 99
    time.vent = std::rand() % 100;        // 0 à 99
    time.uv = std:: rand() % 100;        // 0 à 99
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
        case 4: minT=15; maxT=50; break; // 20-23h
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
    if (time.hour % 3 == 0)
    {
        time.temperature = getTemperatureForTranche(time.hour);
    }
    
}



// Initialise la température
void initTemperature(Temperature& t)
{
    t.valeur = 15.0f; // Température de départ
    t.timer = 0.0f;   // Timer à zéro
}

// Met à jour la température toutes les 5 secondes
void updateTemperature(Temperature& t, float deltaTime)
{
    t.timer += deltaTime; // Avance le temps

    if (t.timer >= 4000)  // Toutes les 5 secondes
    {
        t.timer = 0.0f;   // Reset timer
        t.valeur = (float)(rand() % 46 - 5); // -5 à 40
    }
    
}
// Met à jour les valeurs toutes les 2 secondes
void updateMeteotime(MeteoTime& time, float deltaTime )
{
   
     time.timer+= deltaTime;      // Timer interne
                // Avance le temps

    if ( time.timer >= 3000)               // Toutes les 6 secondes
    {
        time.timer = 0.0f;      // Reset timer
        time.humidite = std :: rand() % 100 ;
        time.uv = std :: rand() % 100 ;
        time.pluie = std:: rand() % 100 + 1;      // 0 à 99
         time.vent = std:: rand() % 100 + 1;      // 0 à 99
        
    }
}

void gestion (MeteoTime& time){
    
    // froid 
    if( time.temperature <= 10  ){
        time.pluie = std::rand() % 31 + 4 ; //peu de pluie 
        time.vent = std::rand() % 60 + 20 ; //vent moderer
        time.humidite = std::rand() % 80 + 30; //humidite forte
         time.uv = std::rand() % 6 ; // uv moderer
        //doux
    }else if(time.temperature <= 22){
        time.pluie = std::rand() % 70 + 20 ; // pluie possible
        time.vent = std::rand()% 50 + 10 ; // vent est assez normal
        time.humidite = std::rand() % 76 + 8 ; // l'humidite reduit
        time.uv = std::rand() % 42 + 2 ;  //les uv monte 
         //chaud 
    } else if  (time.temperature <= 32){
        time.pluie = std::rand() % 21 ; //pluie rare
        time.vent = std::rand () % 40 + 13 ; // le vent reduit
         time.humidite = std::rand() % 40 + 15 ; // l'humidite aussi
          time.uv = std::rand() % 89 + 70 ; //uv augmente
        //canicule
    }else{
      time.pluie = std::rand()% 6; // pas de pluie quasiment
      time.vent = std::rand()% 31 ; //pas assez de vent
       time.humidite = std::rand() % 20 + 1; //c'est sec
        time.uv = std::rand() % 98 + 15 ; //les uv a max
    }


}

//fonction pour gerer les etats 
 Etat  etat ( const MeteoTime& time){
    if(time.temperature <= 10){
        return Neigeux ;
    }else if( time.temperature <= 22){
        return Nuageux ;
    }else if (time.temperature <= 32){
        return Ensolleille;
    }else{
        return Canicule;
    }
 }
