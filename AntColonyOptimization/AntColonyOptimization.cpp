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
	Simulation *Welt = nullptr;
	Creator *kp = nullptr;

	std::cout << "Simulation #\t"<< "Futter verbleibend\t" << "Ameisen verbleibend\t" << "Runden ueberlebt" << std::endl;

	for (long double NumberOfSimulations_counter = 0; NumberOfSimulations_counter < data.NumberOfSimulations; NumberOfSimulations_counter++) {
		
		srand((unsigned)time(NULL));

		//Wenn die Welt nicht zum ersten mal erschaffen wird: vorher zuruecksetzen in Grundzustand
		if (Welt != nullptr) {
			Welt->reset_instance();
		}

		Welt = Simulation::getInstance();	//statischer Funktionsaufruf, Doppelpunkt verwenden!
		//std::cout << "Pointer " << Welt << std::endl;
		

		//Grundlegende Dinge im Ameisen Universum erschaffen...
		kp = Creator::getInstance();			//statischer Funktionsaufruf, Doppelpunkt verwenden!
		Welt->create_environment(data.EnvironmentSizeCols, data.EnvironmentSizeRows);

		for(long int ah=0; ah < data.NumberOfAnthills;ah++) kp->createItem("Anthill");	//x Ameisenhuegel erzeugen
		for (long int ah = 0; ah < data.NumberOfFood;ah++) kp->createItem("Food");		//x Food erzeugen

		long int cycle_counter = 0;
		long int futterzaehler = 0;
		long int ameisenzaehler = 0;

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
				std::cout << "\t" << NumberOfSimulations_counter;
				std::cout << "\t\t" << futterzaehler;
				std::cout << "\t\t\t" << ameisenzaehler;
				std::cout << "\t\t\t" << cycle_counter << std::endl;
				break;
			}
		}
		//std::cout << "cycles survived: " << cycle_counter << std::endl;
	}

	int c;
	puts("Hit \"return\" to exit.");
	do {
		c = getchar();
		putchar(c);
	} while (c != '\n');

	return 0;
}


