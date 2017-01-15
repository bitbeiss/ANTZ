#pragma once
class Singleton {
public:
	static Singleton* Instance();
	~Singleton();
protected:
	Singleton();
	
private:
	static Singleton* _instance;
	
	
};


