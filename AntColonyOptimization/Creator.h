#pragma once
class Creator
{
public:
	static Creator *getInstance();
	~Creator();

	Item* createItem(std::string);

private:
		Creator();
		static Creator *_instance;
		Item *AnthillReference;
};

