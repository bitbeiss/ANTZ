#pragma once
#include "Item.h"
#include "Area.h"


class Futter : public Item
{
public:
	int Naehrstoffe;
	Futter(Area*);
	~Futter();
	void whoAmI();
	Area* position;
public:
	void act();
};

