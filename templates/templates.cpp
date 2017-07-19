#include <string>
#include <iomanip>
#include <iostream>
#include "templates.h"

int main(int argc, char* argv[])
{
	std::cout << Get<int>() << std::endl;
	std::cout << std::fixed << std::setprecision(1) << Get<double>() << std::endl;
	std::cout << Get<std::string>() << std::endl;

	return 0;
}
