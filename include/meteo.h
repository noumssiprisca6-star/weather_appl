#ifndef METEO_H
#define METEO_H

#include <SDL3/SDL.h>
#include <cstdlib>
#include <ctime>
#include "../libs/stb/stb_image.h"
#include"../src/SDL3/SDL3_image/SDL_image.h"
#include <iostream>
#include<string>

const int NB_JOURS = 5;

// Structure pour le temps
struct MeteoTime
{
    int hour;        // 0-23
    int dayIndex;    // 0 = Lundi, ... 4 = Vendredi
    int temperature; // température actuelle
    int pluie  ;  // quantite de pluie
    int humidite ;// quqntite d'humidite 
    int vent  ;  // quantite d'air
    int uv     ;     // quantite de rayon ultra violet
    float timer ;
};

// Initialisation
void initTime(MeteoTime& time);

// Avancer d'une heure et mettre à jour la température toutes les 5h
void advanceOneHour(MeteoTime& time);

// Nom du jour
const char* getDayName(int dayIndex);

// Générer la température pour cette tranche de 5 heures
int getTemperatureForTranche(int hour);
//fonction pour gerer les facteurs 
void gestion (MeteoTime& time);

void updateMeteotime(MeteoTime& time, float deltaTime) ;

// Structure température
struct Temperature
{
    float valeur;      // Température actuelle
    float timer;       // Timer interne
};

//structure pour gerer l'etat
enum Etat{
    Nuageux,
    Neigeux ,
    Ensolleille , 
    Canicule ,
    Leger_Soleil,
   
};

// Initialise la température
void initTemperature(Temperature& t);

// Met à jour la température toutes les 5 secondes
void updateTemperature(Temperature& t, float deltaTime);
 //pour gerer les messages d'etat
 Etat etat(const MeteoTime& time);

#endif