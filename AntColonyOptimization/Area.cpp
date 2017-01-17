#pragma once
#include <string>
#include <iostream>
#include "Area.h"
#include "Parameter.h"


//Erzeugt ein Area-Element mit Startwerten (NULL-Ptr usw.)
Area::Area(int Zeile, int Spalte) {
	Area::Nord = NULL;
	Area::Sued = NULL;
	Area::West = NULL;
	Area::Ost = NULL;

	//übebergebene Werte werden als Position in Zeile und Spalte eingetragen
	Area::Zeile = Zeile;
	Area::Spalte = Spalte;

	//Am Anfang hat jede Area einen Pheromonwert von 0
	pheromone = 0;
}

//Destruktor
Area::~Area() {
}

//Setzt die Area-Pointer auf die gewüschte Richtung ("north, south, east, west"), Simulationserstellung
void Area::setRichtung(Area* ein, std::string Richtung) {
	if (Richtung == "north") {
		Nord = ein;
	}
	else if (Richtung == "south") {
		Sued = ein;
	}
	else if (Richtung == "east") {
		Ost = ein;
	}
	else if (Richtung == "west") {
		West = ein;
	}
}

//Verringert jede Runde den Pheromonwert auf dem Area, Werte aus Parameter
void Area::act() {
	Parameter data;
	if (pheromone >= data.PheromoneEvaporate ) {
		pheromone = pheromone - data.PheromoneEvaporate;
	}
}


//Ameisen mit Futter legen Pheromone auf das Feld, Werte aus Parameter
void Area::setPheromone(Area* AntPosition)
{
	if (AntPosition == nullptr) return;
	Parameter data;
	AntPosition->pheromone = AntPosition->pheromone + data.PheromoneQuantity;
}

//Gibt den Pheromonwert des aktuellen Area's zurück
long Area::getPheromone(Area* AntPosition)
{
	return AntPosition->pheromone;
}

//Zurückgegeben wird der Pointer auf die angeforderte Richtung ("north, south, east, west")
Area* Area::getRichtung(std::string ein){

	if(ein == "north") {
		return Nord;
	}
	else if(ein == "south") {
		return Sued;
	}
	else if(ein == "east") {
		return Ost;
	}
	else if(ein == "west") {
		return West;
	}
	else return nullptr;
}

