#include "Parameter.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>



Parameter::Parameter() {
	this->Lifetime = 50;
	this->FoodCapacity = 1;
	this->PheromoneQuantity = 10;
	this->PheromoneEvaporate = 1;
	this->ForwardProbability = 50;
	this->RightProbability = 25;
	this->LeftProbability = 25;
	this->BackwardProbability = 0;
	this->MaximumMovementRetries = 500;
	this->EnvironmentSizeCols = 4;
	this->EnvironmentSizeRows = 4;
	this->AnthillFood = 10;
	this->FoodQuantity = 30;
	this->MaxCycles = 30000000;
	this->NumberOfSimulations=200;
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
