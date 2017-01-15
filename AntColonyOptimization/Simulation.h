#pragma once
//#include "Area.h"
#include "Item.h"
#include <vector>
#include <list>
#include "Singleton.h"
#include <string>

class Area;

class Simulation
{
public:
	~Simulation();
	static Simulation *getInstance();
	void create_environment(int,int);
	Area *getSpielfeldArea(int, int);
	void ActAll();
	
	std::list<Item*> Gesamt_Item_Liste;
	int Rows;
	int Colls;
	
private:
	Simulation();

	static Simulation *_instance;
	std::vector<std::vector<Area *>> Spielfeld;
};

