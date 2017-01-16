#pragma once
#include "Parameter.h"
#include "Futter.h"
#include "Area.h"
#include "Ameise.h"
#include "Ameisenhuegel.h"
#include "Simulation.h"
#include <iostream>
#include <vector>

/*
Lieber Clemens!

Hab deine Lebenszeit-Verringerung in eine Funktion gepackt, welche ich am Ende der Act aufrufe: reduceLifeTime()
Dachte das wär schöner und praktischer so (du meintest auch wir könnten ruhig für diverse Sachen ne Funktion schreiben :P)

Des weiteren habe ich den Auslade-Vorgang der Ameise, wenn diese auf den Hügel sitzt fertig gemacht
und rufe diese Funktion ebenfalls in der Act auf: unloadFood()
Die Funktion unloadFood() macht einfach gar nichts, wenn kein Futter geladen ist

Area* check_food(Area* areaptr) bzw. Area* checkFoodSourrounding() sind ebenfalls fertig

Beim Fall 1: Futter geladen hab ich auch angefangen, aber jetzt bist du grad heimgekommen :P
Schicke dir das Projekt jetzt so wie es ist.

ACHTUNG! Aufpassen bei der Reihenfolge; Die Ameise soll ja nicht losmarschieren bevor sie das Futter auslädt.
Aufpassen auch bei der Ablage der Pheromonspur durch die Area-Funktion: void setPheromone(Area* AntPosition); 
Diese wird grad im Fall 1 aufgerufen, bevor sie das nächste Feld aus dem backtrack_stack pop()t.

LG Dan

*/



//Testfunktion
void Ameise::whoAmI() {
	std::cout << "Ich bin eine Ameise" << std::endl;
}

//Es wird überprüft, ob auf dem Übergebenen Area-Feld ein Futter liegt
//Rückgabe des Area-Feldes wenn positiv, NULL-Pointer wenn kein Futter vorhanden
Area *Ameise::check_food(Area* areaptr) {
	
	//Wenn die Item-Liste leer ist, gibt es kein Futter
	if(areaptr->ItemList.empty() == true){
		return nullptr;
	}

	//Die Item-Liste des des übergebenen Area-Pointers wird auf Futter untersucht
	std::list<Item*>::iterator it = areaptr->ItemList.begin();
	for (; it != areaptr->ItemList.end(); it++)	{
		if (typeid(**it) == typeid(Futter)) {
			//Falls Futter vorhanden -> Rückgabe des Area-Pointers
			return areaptr;
		}
	}
	return nullptr;
}

//Überprüft alle angrenzenden Felder auf Futter und gibt, wenn gefunden, den Area-Pointer mit Futter drauf zurück, ansonsten: nullptr
Area * Ameise::checkFoodSurrounding() {
	//Gibt es Futter im Norden?
	if(check_food(position->getRichtung("north")) != nullptr){
		return position->getRichtung("north");
	 }
	//Gibt es Futter im Süden?
	if (check_food(position->getRichtung("south")) != nullptr) {
		return position->getRichtung("south");
	}
	//Gibt es Futter im Osten?
	if (check_food(position->getRichtung("east")) != nullptr) {
		return position->getRichtung("east");
	}
	//Gibt es Futter im Westen?
	if (check_food(position->getRichtung("west")) != nullptr) {
		return position->getRichtung("west");
	}
//Kein Futter gefunden
return nullptr;
}


void Ameise::act() {
	//Ameise Entladen (wenn auf Hügel und Futter im Gepäck)
	unloadFood();
	//Ameise bewegen
	move();
	//Lebenszeit verringern (löschen wenn tot)
	reduceLifeTime();
}

std::string Ameise::get_direction_of_last_area() {
	//in den backtrack-Stack gucken und nachsehen, woher wir gekommen sind.
	if (backtrack_stack.top() == position->getRichtung("north")) { return "north"; }
	else if (backtrack_stack.top() == position->getRichtung("south")) { return "south"; }
	else if (backtrack_stack.top() == position->getRichtung("west")) { return "west"; }
	else if (backtrack_stack.top() == position->getRichtung("east")) { return "east"; }
	else {
		std::cerr << "Fehler: Herkunftsrichtung nicht feststellbar. Ameise kann nicht bewegt werden.";
		exit(1);
	}
}

void Ameise::move() {
	Parameter data;
	Area *nextDirection = nullptr;

//Fall 1: FUTTER GELADEN---------------------------------------------------------------------------------------------------------------------------
	if (food_quantity_loaded > 0) {
		//So lange backtrack_stack nicht leer ist wird ge-pop()t
		if (!backtrack_stack.empty()) {
			//Richtung aus backtrack_stack festlegen
			nextDirection = backtrack_stack.top();
			backtrack_stack.pop();
		}
		//Eine Futter-tragende Ameise hinterlässt Pheromone auf dem Area
		this->position->setPheromone(this->position);
	}	

//FALL 2: WIR SUCHEN NOCH FUTTER-------------------------------------------------------------------------------------------------------------------
	else {
		//Der backtrack_stack ist leer (Ameise will losgehen; wir sind am Ameisenhuegel)
		if (backtrack_stack.empty() == 1) {
			//Ameise befindet sich im Ameisenhügel, Position wird in den backtrack_stack übernommen.
			backtrack_stack.push(position);
		}

		// hier startet die if mit dem check-food-zweig
		//TO DO: Alle umgebenden Felder auf Futter ueberprüfen mittels bereits fertiggestellter Funktion: Area* checkFoodSurrounding();
		//Rueckgabe bei gefundenem Futter: Area*, Rueckgabe wenn nichts gefunden: nullptr
		Area *retval = this->checkFoodSurrounding();
		if ( retval != nullptr) {
			//Fall: Futter wird in der Umgebung gefunden: direkt (ohne weitere Ueberlegung/Berechnung) zum Futter gehen!
			nextDirection = retval;
		}
		else {	
			//Fall: kein Futter in direkter Nachbarschaft... 

			//Weitere Richtungen je nach Herkunftsrichtung
			//Format: vorwaerts, rueckwaerts, links, rechts
			std::vector<std::string> directions_from_north = {
			"south","north","east","west"
			};
			std::vector<std::string> directions_from_south = {
			"north","south","west","east"
			};
			std::vector<std::string> directions_from_west = {
			"east","west","north","south"
			};
			std::vector<std::string> directions_from_east = {
			"west","east","south","north"
			};

			provenience = get_direction_of_last_area();
			std::vector<std::string> chosenDirectionVector;

			//was-toDo: erster move muss ohne provenience erfolgen! (wenn stack size = 1)
			//die "Sichtweise" je nach Herkunftsrichtung festlegen.
			if (provenience == "north") chosenDirectionVector = directions_from_north;
			else if (provenience == "south") chosenDirectionVector = directions_from_south;
			else if (provenience == "east") chosenDirectionVector = directions_from_east;
			else if (provenience == "west") chosenDirectionVector = directions_from_west;
			else {
				std::cerr << "Fehler: Richtungsvektor konnte nicht bestimmt werden. Ameise kann nicht bewegt werden.";
				exit(1);
			}

			//ToDo: Pheromonspureinfluss auf die Futtersuche Bewegung abbilden.
			long pheromon_levels[3];
			long pheromon_levels_verrechnet[3];
			long sum=0;
			long tmp;
			int wurzel_faktor = 10;
			float einfluss_faktor = 0.7;
			for (int i = 0; i < 3; i++) {
				pheromon_levels[i] = this->position->getRichtung(chosenDirectionVector[i])->getPheromone();
			}
			for (int j = 0; i < 3; i++) {
				//Daempfung beim Einfluss sehr grosser Pheromon Mengen
				pheromon_levels_verrechnet[j] = sqrt(pheromon_levels[j] + wurzel_faktor)*einfluss_faktor;
				sum += pheromon_levels_verrechnet[j];
			}
			for (int t = 0; t < 3; t++) {
				tmp = pheromon_levels_verrechnet[t];
				//W-keiten auf 1 normieren
				pheromon_levels_verrechnet[t] = (tmp/sum);
			}

			//Errechnete Pheromoneinfluesse auf parametrisierte Bewegungswahrscheinlichkeiten verrechen



			//Fall: Wir sind am Ameisenhuegel, der backtack_stack ist daher noch leer!
			if (backtrack_stack.empty() == 1) {

				//So lange eine Richtung wuerfeln, bis eine gueltige gewaehlt wird. (Fall: Ameisenhuegel steht am Rand...)
				//Alle Richtungen sind hier gleich wahrscheinlich, da wir am Ameisenhuegel stehen!
				//was-todo: Würfel für start/Ameisenhügel (alle Richtungen gleich wahrscheinlich)
				do {
					int except_randval = rand() % 4;
					nextDirection = position->getRichtung(chosenDirectionVector[except_randval]);
				} while (nextDirection == nullptr);
			}
			else {
				//So lange eine neue Richtung suchen, bis ein gueltiger Zeiger zurueckgegeben wird. (oder  erreicht ist)

				//Nach Pheromonen auf den umliegenden Feldern suchen

				//Die gefundenen Quantitaeten gewichten und in W-keiten umrechnen

				//todo: pheromone in der umgebung erfassen

				double retry_counter = 0;
				while (nextDirection == nullptr || data.MaximumMovementRetries >= retry_counter) {

					if (randval <= data.BackwardProbability) {
						nextDirection = backtrack_stack.top();    // waere getRichtung(chosenDirectionVector[1]
					}
					//nach links
					else if (randval <= data.LeftProbability + data.BackwardProbability && randval > data.BackwardProbability) {
						nextDirection = position->getRichtung(chosenDirectionVector[2]);
					}
					//nach rechts
					else if (randval <= data.LeftProbability + data.RightProbability + data.BackwardProbability && randval > data.BackwardProbability + data.LeftProbability) {
						nextDirection = position->getRichtung(chosenDirectionVector[3]);
					}
					//gerade aus
					else if (randval > data.LeftProbability + data.RightProbability + data.BackwardProbability) {
						nextDirection = position->getRichtung(chosenDirectionVector[0]);
					}
					retry_counter++;
					if (retry_counter >= data.MaximumMovementRetries) std::cerr << "Warning: Maximum retries of ant movement reached. Ant will not move in this turn.";
				}
			}
		}
	}
	position = nextDirection;

	
}




void Ameise::take_food(Futter * futterptr) {
	//Futter in die Quantitaetenvariable der Ameise eintragen
	if (futterptr->Naehrstoffe > 1) {
		this->food_quantity_loaded = food_quantity_loaded + 1;
		futterptr->Naehrstoffe = futterptr->Naehrstoffe - 1;
	}
}


//Lebenszeit der Ameise jeden Zyklus um 1 verringern und löschen wenn tot
void Ameise::reduceLifeTime()
{
	//Verringert die Lebenszeit um 1
	if (this->life_time > 0) {
		this->life_time = this->life_time - 1;
	}
	//Lebenszeit vorbei, die Ameise verschwindet von der Bildflaeche
	else if(this->life_time < 0 || this->life_time == 0){
		Simulation *currentSimulation = Simulation::getInstance(); //Aus Globaler Liste löschen
		currentSimulation->Gesamt_Item_Liste.remove(this); //Aus dem Speicher löschen
		std::cout << "Ameise gestorben!" << std::endl;
		delete(this);
		return;
	}
}

//Entlädt die Ameise, wenn sie sich im Hügel befindet und Futter geladen hat
void Ameise::unloadFood(){

	//Ameise steht auf Ameisenhügel	
	if(this->backtrack_stack.empty() == true){

		//Ameise hat Futter geladen
		if (this->food_quantity_loaded > 0) {

			//Der Ameisenhügel wird aus der Item-Liste der Area herausgesucht
			std::list<Item*>::iterator it = this->position->ItemList.begin();
			for (; it != this->position->ItemList.end(); it++) {
				//Der Ameisenhügel wurde gefunden
				if (typeid(**it) == typeid(Ameisenhuegel)) {
					Ameisenhuegel* huegelptr = dynamic_cast<Ameisenhuegel*>(*it);
					//Futter wird in den Hügel geladen
					huegelptr->add_food(this->food_quantity_loaded);	
				}
			}
		}
	}
}

//Erzeugt eine Ameise und legt Startwerte fest, Werte aus Parameter
Ameise::Ameise(Area *startpos) {
	//Lebenszeit setzten, Wert aus Parameter
	Parameter data;
	this->life_time = data.Lifetime;
	//(Start-)position setzten, Übergabe vom Anthill
	this->position = startpos;
}

//Destruktor
Ameise::~Ameise() {
}