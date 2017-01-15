#pragma once
#include "Item.h"
#include <list>

class Ameisenhuegel : public Item
{
public:
	Ameisenhuegel(Area *position, int FutterStartwert); 
	~Ameisenhuegel();
	void whoAmI();
	void act();
	void add_food(int);
	Area* position;

private:
	int Futterlager;
	void createAnt();
};

