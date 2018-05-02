#include "Application.h"

#include <stdexcept>
#include <iostream>
#include <ctime>

int main()
{
	srand(time(nullptr));
	try
	{
		Application app;
		app.run();
	}
	catch(std::exception &e)
	{
		std::cout << "\nEXCEPTION: " << e.what() <<std::endl;
	}
	//std::cin.get();
	return 0;
}