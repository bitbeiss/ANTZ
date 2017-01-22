#include "Parameter.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>



Parameter::Parameter() {
	this->Lifetime = 20;				//Lebenszeit einer Ameise in Runden
	this->FoodCapacity = 1;				//Menge an Futter, die eine Ameise gleichzeitig transportieren kann
	this->PheromoneQuantity = 10;		//Staerke der Pheromonspur, die von der Ameise pro Feld gesetzt wird.
	this->PheromoneEvaporate = 1;		//Abnahme der Pheromonspur pro Runde
	this->ForwardProbability = 50;
	this->RightProbability = 25;
	this->LeftProbability = 25;
	this->BackwardProbability = 0;		
	this->MaximumMovementRetries = 500;	//Maximale Anzahl an neuerlichen Versuchen, wenn Bewegung der Ameise nicht moeglich ist.

	this->EnvironmentSizeCols = 15;		//Spielfeld Spalten
	this->EnvironmentSizeRows = 15;		//Spielfeld Zeilen

	this->NumberOfAnthills = 2;			//Anzahl der Ameisenhuegel
	this->NumberOfFood = 3;				//Anzahl der Futterdepots

	this->AnthillFood = 10;				//Startwert fuer Futter im Ameisenhuegel
	this->FoodQuantity = 30;			//Futtereinheiten pro Depot
	this->MaxCycles = 1500;
	this->NumberOfSimulations=100; 
}

Parameter::~Parameter() {
}

void Parameter::set_parameter(std::string) {
}

//read params from xml formatted parameter file
void load_parameters(std::string path) {
	std::vector<std::string> paramvec{
		"ant_food_capacity",
		"ant_forward_probability",
		"ant_left_probability",
		"ant_right_probability",
		"ant_backward_probability",
		"env_size_cols",
		"env_size_rows",
		"start_anthill_food",
		"start_food_quantity"
	};

	std::string line;
	std::stringstream sstream;
	int param_type_id=0;
	double param_value;

	std::ifstream paramfile;						//input file stream
	paramfile.open(path);
	if (paramfile.is_open()) {
		while (std::getline(sstream, line)) {
			if (std::size_t found = line.find(paramvec[param_type_id]) != std::string::npos) {
				sstream << line << std::endl;
				sstream >> param_value;
				std::cout << param_value << std::endl;
			}
			param_type_id++;
		}
	}
	paramfile.close();
}
