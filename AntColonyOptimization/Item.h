#pragma once

class Area;

class Item
{
public:
	Item();
	~Item();
	virtual void whoAmI();
	virtual void act();

private:
	Area* position;

};

