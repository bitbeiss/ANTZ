// AntColonyOptimization.cpp : Definiert den Einstiegspunkt f�r die Konsolenanwendung.
//
#pragma once
#include "stdafx.h"
#include <iostream>
#include <list>
#include "Item.h"
#include "Area.h"
#include "Ameisenhuegel.h"
#include "Futter.h"
#include "Ameise.h"
#include "Simulation.h"
#include "Singleton.h"
#include "Creator.h"
#include "Parameter.h"
#include <time.h>

const int verbose = 0;

int main(void) {

	srand((unsigned)time(NULL));

	Parameter data;
	Simulation *Welt = Simulation::getInstance();	//statischer Funktionsaufruf, Doppelpunkt verwenden!
	std::cout << "Pointer " << Welt << std::endl;
	Welt->create_environment(data.EnvironmentSizeCols,data.EnvironmentSizeRows);

	//Grundlegende Dinge im Ameisen Universum erschaffen...
	Creator *kp = Creator::getInstance();			//statischer Funktionsaufruf, Doppelpunkt verwenden!
	kp->createItem("Anthill");
	kp->createItem("Food");
	
	long double cycle_counter=0;
	long double futterzaehler=0;
	long double ameisenzaehler=0;
	for (long double NumberOfSimulations_counter = 0; NumberOfSimulations_counter < data.NumberOfSimulations; NumberOfSimulations_counter++) {
			for (cycle_counter = 0; cycle_counter < data.MaxCycles; cycle_counter++) {
				if (verbose==1) std::cout << "Runde #:" << cycle_counter << std::endl;
				Welt->ActAll();
				//Alle Ameisen gestorben oder Futter aus: Simulation beenden, Ergebnis ausgeben (Runden)

				futterzaehler = 0;
				ameisenzaehler = 0;
				for (std::list<Item*>::iterator it = Welt->Gesamt_Item_Liste.begin(); it != Welt->Gesamt_Item_Liste.end(); it++) {
					if (typeid(**it) == typeid(Ameise)) {
						ameisenzaehler += 1;
					}
					if (typeid(**it) == typeid(Futter)) {
						futterzaehler += dynamic_cast<Futter*>(*it)->Naehrstoffe;
					}
				}
				if (futterzaehler == 0 || ameisenzaehler == 0 || cycle_counter>data.MaxCycles) {
					std::cout << "**************Simulation beendet********************" << std::endl;
					std::cout << "Futter verbleibend: " << futterzaehler << std::endl;
					std::cout << "Ameisen verbleibend: " << ameisenzaehler << std::endl;
					std::cout << "Runden:" << cycle_counter << std::endl;
				}
			}
		std::cout << "cycles survived: " << cycle_counter << std::endl;
	}
	return 0;
}


