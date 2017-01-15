#pragma once
#include "Item.h"
#include <iostream>

void Item::whoAmI() {
	std::cout << "Ich bin ein Item" << std::endl;

}

void Item::act() {
	std::cout << "Ich bin ein Item" << std::endl;

}

Item::Item()
{
}


Item::~Item()
{
}
