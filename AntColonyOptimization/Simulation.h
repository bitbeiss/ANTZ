#pragma once
//#include "Area.h"
#include "Item.h"
#include <vector>
#include <algorithm>
#include <list>
#include "Singleton.h"
#include <string>

class Area;

class Simulation
{
public:
	~Simulation();
	static Simulation *getInstance();
	void reset_instance();
	void create_environment(int,int);
	Area *getSpielfeldArea(int, int);
	void ActAll();
	
	std::list<Item*> Gesamt_Item_Liste;
	std::list<Item*> Gesamt_Item_Liste_tmp; //temporaere Liste zum Puffern von neuen Items waehrend Act-Iterationen
	std::list<Item*> Gesamt_Item_Liste_entf; //Austragliste von Objekten die aus der globalen Liste nach Act-Iterationen entfernt werden muessen.
	int Rows;
	int Colls;
	
private:
	Simulation();

	static Simulation *_instance;
	std::vector<std::vector<Area *>> Spielfeld;
};

