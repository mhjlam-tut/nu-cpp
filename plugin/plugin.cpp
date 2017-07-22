#include <ctime>
#include <random>
#include <iomanip>
#include <iostream>

#pragma warning(disable: 4996) // disable std::localtime unsafe/deprecation warning

#define export extern "C" __declspec(dllexport)

export void void_function();
export void void_function_str(const char* str);
export int int_function();

void void_function()
{
	auto t = std::time(nullptr);
	auto tm = std::localtime(&t);
	auto fmt = "%H:%M:%S";

	std::cout << "Plugin says: \"Hello!\" at " << std::put_time(tm, fmt) << std::endl;
}

void void_function_str(const char* str)
{
	auto t = std::time(nullptr);
	auto tm = std::localtime(&t);
	auto fmt = "%H:%M:%S";

	std::cout << "Plugin says: \"" << str << "\" at " << std::put_time(tm, fmt) << std::endl;
}

int int_function()
{
	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_int_distribution<int> dist(1, 100);

	return dist(gen);
}
