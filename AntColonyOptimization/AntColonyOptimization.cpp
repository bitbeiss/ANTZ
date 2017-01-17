// AntColonyOptimization.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
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
	Parameter data;

	for (long double NumberOfSimulations_counter = 0; NumberOfSimulations_counter < data.NumberOfSimulations; NumberOfSimulations_counter++) {
		srand((unsigned)time(NULL));

		
		Simulation *Welt = Simulation::getInstance();	//statischer Funktionsaufruf, Doppelpunkt verwenden!
		Welt->reset_instance();
		std::cout << "Pointer " << Welt << std::endl;
		Welt->create_environment(data.EnvironmentSizeCols, data.EnvironmentSizeRows);

		//Grundlegende Dinge im Ameisen Universum erschaffen...
		Creator *kp = Creator::getInstance();			//statischer Funktionsaufruf, Doppelpunkt verwenden!
		kp->createItem("Anthill");  //2x Ameisenhuegel erzeugen
		kp->createItem("Anthill");
		kp->createItem("Food");     //3x Food erzeugen
		kp->createItem("Food");
		kp->createItem("Food");

		long double cycle_counter = 0;
		long double futterzaehler = 0;
		long double ameisenzaehler = 0;

		for (cycle_counter = 0; cycle_counter < data.MaxCycles; cycle_counter++) {
			srand((unsigned)time(NULL));
			if (verbose == 1) std::cout << "Runde #:" << cycle_counter << std::endl;
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
			if (futterzaehler == 0 || ameisenzaehler == 0 || cycle_counter == (data.MaxCycles - 1)) {
				std::cout << "**************Simulation beendet********************" << std::endl;
				std::cout << "Futter verbleibend: " << futterzaehler << std::endl;
				std::cout << "Ameisen verbleibend: " << ameisenzaehler << std::endl;
				std::cout << "Runden ueberlebt:" << cycle_counter << std::endl;
				break;
			}
		}
		//std::cout << "cycles survived: " << cycle_counter << std::endl;
	}
	return 0;
}


