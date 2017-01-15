#pragma once
#include "Futter.h"

//Gibt den Klassennamen aus
void Futter::whoAmI() {
	std::cout << "Ich bin ein Futter" << std::endl;
}

void Futter::act()
{
}

//Erzeugt ein Futter an der angegebenen Stelle im Spielfeld
Futter::Futter(Area* position):position(position) {
}

//Destruktor
Futter::~Futter() {
}
