#pragma once
//#include "Area.h"
#include "Item.h"
#include <stack>

class Area;
class Futter;

class Ameise : public Item {

public:
	Ameise(Area* startpos);
	~Ameise();
	virtual void whoAmI();
	void act();					//virtual act ueberschreiben
	double life_time;

private:
	Area* position;
	std::string provenience;
	int food_quantity_loaded;
	std::stack<Area *> backtrack_stack;

	//Methoden
	std::string get_direction_of_last_area();
	void move();
	Area* check_food(Area* areaptr);
	Area* checkFoodSourrounding(); //Return Area* (Futter-Location) falls Futter in Umgebung, ansonsten nullptr
	void take_food(Futter *futterptr);
	void reduceLifeTime();
	void unloadFood();
};

