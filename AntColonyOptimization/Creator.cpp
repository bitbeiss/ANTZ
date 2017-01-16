#include "Ameise.h"
#include "Ameisenhuegel.h"
#include "Futter.h"
#include "Item.h"
#include "Parameter.h"
#include <cstdlib>
#include "Creator.h"		//ItemFactory Klasse Synonym
#include "Simulation.h"
#include "Area.h"
#include "list"
#include <iostream>

Creator *Creator::_instance = 0;

//Singleton!
Creator *Creator::getInstance() {
	if (Creator::_instance == 0) {
		_instance = new Creator;
	}
	return _instance;
}

//Konstruktor mit Startwerten
Creator::Creator() {
	AnthillReference = nullptr;
}

//Destruktor
Creator::~Creator() {
}

//Erzeugt ein Item je nach Übergabestring ("Anthill, Ant, Food")
Item *Creator::createItem(std::string itemtype)
{
	Parameter data;

	//Erzeugt einen Ameisenhuegel an einer zufälligen Position im Spielfeld
	if (itemtype == "Ameisenhuegel" || itemtype == "Anthill") {
		Simulation* currentSimulation = Simulation::getInstance();

		int randx = std::rand() % (currentSimulation->Rows); //Zufallszahl für Reihen
		int randy = std::rand() % (currentSimulation->Colls); //Zufallszahl für Spalten
		
		//Startwert für Ameisenhügelfutter setzten, Wert aus Parameter
		Item* Anthill = new Ameisenhuegel(currentSimulation->getSpielfeldArea(randx, randy), data.AnthillFood);
		//Eintragen des Ameisenhuegels in Globale Liste (Simulation)
		currentSimulation->Gesamt_Item_Liste.push_back(Anthill);
		//Eintragen des Ameisenhuegels in Item Liste (Area)
		currentSimulation->getSpielfeldArea(randx, randy)->ItemList.push_back(Anthill); 

		AnthillReference = Anthill;
		std::cout << "Ameisenhuegel wurde erzeugt" << std::endl;

		return AnthillReference;
	}

	//Erzeugt eine Ameise im Ameisenhuegel
	if (itemtype == "Ameise" || itemtype == "Ant") {

		//Überprüfung, ob ein Ameisenhügel vorhanden ist
		if(AnthillReference == NULL) {
			std::cerr << "Es existiert noch kein Ameisenhuegel, Ameisen koennen nicht erzeugt werden!" << std::endl;
			exit(1);
			return nullptr;
		}

		//Wenn Ameisenhügel vorhanden, erzeugen der Ameise und eintragen in die Listen
		else{
			Simulation* currentSimulation = Simulation::getInstance();
			Ameisenhuegel* tmpAnthill = dynamic_cast<Ameisenhuegel*>(AnthillReference);
			Ameise* currentAnt = dynamic_cast<Ameise*>(new Ameise(tmpAnthill->position));
			currentAnt->life_time = data.Lifetime; //Lebensdauer der Ameise, Wert aus Parameter
			
			currentSimulation->Gesamt_Item_Liste.push_back(currentAnt);	//Eintragen der Ameise in Globale Liste (Simulation)
			//tmpAnthill->position->ItemList.push_back(currentAnt);		//Eintragen der Ameise in Item Liste (Area)

			std::cout << "Ameise wurde erzeugt" << std::endl;
			return tmpAnthill;
		}
		return nullptr;
	}

	//Erzeugt ein Futter zufaellig auf dem Spielfeld !Futter kann nicht auf dem selben Feld wie Ameisenhügel liegen!
	if (itemtype == "Futter" || itemtype == "Food") {
		Simulation* currentSimulation = Simulation::getInstance();
		Ameisenhuegel* tmpAnthill = dynamic_cast<Ameisenhuegel*>(AnthillReference);

		int randx = 1 + std::rand() % (currentSimulation->Rows);	//Zufallszahl fuer Reihen
		int randy = 1 + std::rand() % (currentSimulation->Colls);	//Zufallszahl fuer Spalten

		//While-Schleife soll so lange ausgefuehrt werden, bis die Position von currentSimulation (Futter) und Anthill unterschiedlich sind
 		while (currentSimulation->getSpielfeldArea(randx, randy) == tmpAnthill->position) {

			int randx = 1 + std::rand() % (currentSimulation->Rows);	//Zufallszahl fuer Reihen
			int randy = 1 + std::rand() % (currentSimulation->Colls);	//Zufallszahl fuer Spalten
		}

		Item* currentFood = new Futter(currentSimulation->getSpielfeldArea(randx, randy));
		Futter* tmpFood = dynamic_cast<Futter*>(currentFood);
		currentSimulation->Gesamt_Item_Liste.push_back(tmpFood);							//Eintragen des Futters in Globale Liste (Simulation)
		currentSimulation->getSpielfeldArea(randx, randy)->ItemList.push_back(tmpFood);		//Eintragen des Futters in Item Liste (Area)

		tmpFood->Naehrstoffe = data.FoodQuantity; //Startwerte fuer die Futtermenge setzten, Wert aus Parameter
		std::cout << "Futter wurde erzeugt" << std::endl;
		return tmpFood;
		
	}
	else return nullptr;
}
