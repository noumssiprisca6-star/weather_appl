#include "../include/meteo.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

// =======================
// Initialisation du temps
// =======================
void initTime(MeteoTime& time)
{
    time.hour = 6;       // début à 6h
    time.dayIndex = 0;   // 0 = Lundi
    std::srand(std::time(NULL)); // initialiser rand
    time.temperature = getTemperatureForTranche(time.hour);
}

// =======================
// Nom du jour
// =======================
const char* getDayName(int dayIndex)
{
    static const char* days[NB_JOURS] = {"Lundi","Mardi","Mercredi","Jeudi","Vendredi"};
    return days[dayIndex];
}

// =======================
// Température par tranche de 5h
// =======================
int getTemperatureForTranche(int hour)
{
    int tranche = hour / 5; // 0-4 → tranche 0, 5-9 → tranche 1, etc.
    int minT, maxT;

    switch(tranche)
    {
        case 0: minT=12; maxT=15; break; // 0-4h
        case 1: minT=16; maxT=20; break; // 5-9h
        case 2: minT=21; maxT=28; break; // 10-14h
        case 3: minT=23; maxT=26; break; // 15-19h
        case 4: minT=18; maxT=22; break; // 20-23h
        default: minT=20; maxT=25; break;
    }

    return minT + (std::rand() % (maxT - minT + 1));
}

// =======================
// Avancer le temps
// =======================
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
    if (time.hour % 2 == 0)
    {
        time.temperature = getTemperatureForTranche(time.hour);
    }
}

// =======================
// Affichage météo pour debug / ImGui
// =======================
void displayWeatherInfo(const MeteoTime& time)
{
    std::cout << "Jour: " << getDayName(time.dayIndex)
              << " | Heure: " << time.hour
              << "h | Temp: " << time.temperature << "°C\n";
}