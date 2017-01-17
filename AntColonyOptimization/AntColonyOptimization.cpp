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

const int verbose = 1;

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
	
	long double cycle_counter;
	for (long double NumberOfSimulations_counter = 0; NumberOfSimulations_counter < data.NumberOfSimulations; NumberOfSimulations_counter++) {
			for (cycle_counter = 0; cycle_counter < data.MaxCycles; cycle_counter++) {
				if (verbose==1) std::cout << "Runde #:" << cycle_counter << std::endl;
				Welt->ActAll();
			}
		std::cout << "cycles survived: " << cycle_counter << std::endl;
	}
	return 0;
}


