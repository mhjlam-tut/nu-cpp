#include <iostream>
#include <stdexcept>
#include "SharedLibrary.h"

int main(int argc, char* argv[])
{
	try
	{
		SharedLibrary sl("plugin.dll");

		sl.Call<void>("void_function");
		sl.Call<void, const char*>("void_function_str", "Sup?");

		int i = sl.Call<int>("int_function");
		std::cout << i << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}
