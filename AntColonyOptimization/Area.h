#pragma once
#include "Item.h"
#include <string>
#include <iostream>
#include <list>
#include "Parameter.h"

class Item;
class Area : public Item
{
public:
	Area(int Zeile=-1, int Spalte=-1);
	~Area();
	Area* getRichtung(std::string);
	void setRichtung(Area*, std::string);
	void act(); //virtual ueberschreiben; Aufgabe: Pheromonspur reduzieren.
	std::list<Item*> ItemList;  //Liste aller Items auf Area.
	void setPheromone(Area* AntPosition);
	long getPheromone(Area* AntPosition);

private:
	long long Duft_Markierungs_Zaheler;
	Area* Nord;
	Area* Sued;
	Area* Ost;
	Area* West;
	int Zeile;
	int Spalte;
	long pheromone;

	

};

