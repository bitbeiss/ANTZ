#pragma once
#include "Ameisenhuegel.h"
#include "Creator.h"
#include "Item.h"
#include "Simulation.h"
#include <iostream>
#include <list>

//Erzeugt eine neue Ameise und fügt sie an das hintere Ende der Liste an
void Ameisenhuegel::createAnt() {
	Creator* currentCreator = Creator::getInstance();
	Item* Ant = currentCreator->createItem("Ant");
	//Simulation* currentSimulation = Simulation::getInstance();
	//currentSimulation->Gesamt_Item_Liste_tmp.push_back(Ant); //hat bereits der Creator erledigt
}

//Gibt den Klassennamen aus
void Ameisenhuegel::whoAmI() {
	std::cout << "Ich bin ein Ameisenhuegel" << std::endl;

}

//Falls Futter vorhanden wird "createAnt()" ausgeführt
void Ameisenhuegel::act() {
	if(Futterlager > 0){
		createAnt();
		//std::cout << "Ameisenhuegel hat neue Ameise erzeugt!" << std::endl;
	}
	else return;
}

//Futter wird zum "Futterlager" hinzugefuegt
void Ameisenhuegel::add_food(int quantity) {
	Futterlager = Futterlager + quantity;
}

//Erzeugung Ameisenhügel, der Wert von "Futterlager" wird dabei auf den Übergabeparameter gesetzt
Ameisenhuegel::Ameisenhuegel(Area* position, int FutterStartwert):position(position),Futterlager(FutterStartwert) {
}

//Destruktor
Ameisenhuegel::~Ameisenhuegel() {
}
