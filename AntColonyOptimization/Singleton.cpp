#include "Singleton.h"

Singleton* Singleton::_instance = 0;


Singleton::Singleton()
{

}


Singleton::~Singleton()
{

}



Singleton* Singleton::Instance() {

	

	if (_instance == 0) {
		_instance = new Singleton;
	}
	return _instance;
}