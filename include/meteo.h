#ifndef METEO_H
#define METEO_H

#include <SDL3/SDL.h>

const int NB_JOURS = 5;

// Structure pour le temps
struct MeteoTime
{
    int hour;        // 0-23
    int dayIndex;    // 0 = Lundi, ... 4 = Vendredi
    int temperature; // température actuelle
};

// Initialisation
void initTime(MeteoTime& time);

// Avancer d'une heure et mettre à jour la température toutes les 5h
void advanceOneHour(MeteoTime& time);

// Nom du jour
const char* getDayName(int dayIndex);

// Générer la température pour cette tranche de 5 heures
int getTemperatureForTranche(int hour);


#endif