#pragma once
#include "Simulation.h"
#include "Area.h"
#include <iostream>
#include "Singleton.h"
#include "Ameisenhuegel.h"
#include "Ameise.h"
#include "Futter.h"
#include <list>
#include <typeinfo>

Simulation* Simulation::_instance = 0;

//Gibt die aktuelle Instanz der Simulation zurück, bzw. Erzeugt diese beim ersten Aufruf (Singleton)
Simulation* Simulation::getInstance() {
	if (_instance == 0) {
		_instance = new Simulation();
	}
	return _instance;
}

//Erzeugt eine dynamische, Zeilen x Spalten Matrix aus Area-Elementen !Achtung: Singleton - Aufruf durch getInstance()!
void Simulation::create_environment(int Zeilen=0, int Spalten=0) {

	//Überprüfung: Mindestgröße des Spielfeldes ist 2 x 2
	if(Zeilen<2 || Spalten <2){
		std::cout << "Das Spielfeld muss aus min. 2 Zeilen und 2 Spalten bestehen!" << std::endl;
		EXIT_FAILURE;
	}

	Rows = Zeilen;
	Colls = Spalten;
	
	//Erzeugt eine unbestimmt große Zeilen*Spalten Matrix (durch verschachtelte Area-Element Vektoren)
	//Mittels resize() wird die Größe des Spielfeldes dynamisch angepasst
	this->Spielfeld.resize(Zeilen);
	for(int v = 0; v < Zeilen; v++) {
		this->Spielfeld[v].resize(Spalten);
	}
	
	//Allokiert in jedem Spielfeldbereich eine Area
	for (int z = 0; z < Zeilen; z++) {
		for (int s = 0; s < Spalten; s++) {
			Spielfeld[z][s] = new Area(z, s);
			Spielfeld[z][s]->ItemList = {};
		}
	}

	// Test: printf("Spielfeld-Area-Liste-Groesse: %d", Spielfeld[1][1]->ItemList.empty());

	//Setzt die Pointer (north, south, east, west) in der Spielfeld-Matrix
	//Alle Pointer, die nach außerhalb des Feldes zeigen sind standardmäßig auf NULL
	for (int z = 0; z < Zeilen; z++) {
		for (int s = 0; s < Spalten; s++) {
			//Nord
			if(z!=0){
				Spielfeld[z][s]->setRichtung(Spielfeld[z - 1][s], "north");
			}
			//Sued
			if(z!=Zeilen-1){
				Spielfeld[z][s]->setRichtung(Spielfeld[z + 1][s], "south");
			}
			//Ost
			if(s!=Spalten-1){
				Spielfeld[z][s]->setRichtung(Spielfeld[z][s + 1], "east");
			}
			//West
			if(s!=0){
				Spielfeld[z][s]->setRichtung(Spielfeld[z][s - 1], "west");
			}			
		}	
	}

std::cout << "Das Spielfeld der Groesse "<<Zeilen<<"x"<<Spalten<< " wurde erzeugt"<< std::endl;
}

//Destruktor
Simulation::~Simulation() {
}

//Gibt den Area Pointer zurück, der sich im angegebenen Spielfeldbereich befindet
Area * Simulation::getSpielfeldArea(int x, int y) {
		return Spielfeld[x][y];	
}

//Simulationskern - Aufruf der einzelnen act() Funktionen in bestimmter Reihenfolge
void Simulation::ActAll() {

	std::cout << "Anfang ActAll"<<std::endl;

	//Erstellen des Listen-Iterators
	std::list<Item*>::iterator it;
	std::list<Item*>Gesamt_Item_ListeT = Gesamt_Item_Liste; //Deep Kopie der Pointer; Liste damit konstant/unabhaengig von aenderungen in den Iterationen

	//Die Gesaamt_Item_Liste der Simulation wird in folgender Reihenfolge abgearbeitet:
	//1. Ameisenhügel (Erzeugen Ameisen, wenn Futter vorhanden)
	//2. Area's (Lassen die Pheromonspur verdampfen, wenn vorhanden)
	//3. Ameisen (Bewegung, Futter aufnehmen und - ablegen)

	//toDo: Achtung!!! Wir haben ein Problem mit einer Liste, die veraendert wird, waehrend wir durch sie iterieren, das fuert zu einer Endlosschleife,
	//da in jedem durchlauf wieder eine Ameise hinzugefuegt wird. Der Iterator ist jedenfalls nicht mehr valide!!!!
	//Die Gesamt_Item_Liste wird nach Ameisenhügeln durchsucht, für die jeweils act() aufgerufen wird
	//for (size_t i = 0; i < Gesamt_Item_Liste.size();i++) {
	long int counter=0;
	for (it = Gesamt_Item_ListeT.begin(); it != Gesamt_Item_ListeT.end(); ++it) {
		if(typeid(*(*it))==typeid(Ameisenhuegel)){
			Ameisenhuegel* tmpAnthill = dynamic_cast<Ameisenhuegel*>(*it);
			tmpAnthill->act();
			std::cout << "tmpAnthill->act()" << "Zaehler: "<< ++counter << " Typ in Liste: " << typeid(*(*it)).name() << std::endl;
		}
	}

	//Die Gesamt_Item_Liste wird nach Area's durchsucht, für die jeweils act() aufgerufen wird
	for (it = Gesamt_Item_ListeT.begin(); it != Gesamt_Item_ListeT.end(); ++it) {
				if (typeid(*(*it)) == typeid(Area)) {
			Area* tmpArea = dynamic_cast<Area*>(*it);
			tmpArea->act();
			std::cout << "tmpArea->act()" << std::endl;
		}
	}

	//Die Gesamt_Item_Liste wird nach Ameisen durchsucht, für die jeweils act() aufgerufen wird
	for (it = Gesamt_Item_ListeT.begin(); it != Gesamt_Item_ListeT.end(); ++it) {
		if (typeid(*(*it)) == typeid(Ameise)) {
			Ameise* tmpAnt = dynamic_cast<Ameise*>(*it);
			tmpAnt->act();
			std::cout << "tmpAnt->act()" << std::endl;
		}
	}

	std::cout << "Ende ActAll" << std::endl;
}

//Standard Konstruktor
Simulation::Simulation() {
}