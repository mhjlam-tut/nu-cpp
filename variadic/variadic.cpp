#include <string>
#include <iostream>

template<typename T>
T adder(T v)
{
	return v;
}

template<typename T, typename... A>
T adder(T first, A... args)
{
	return first + adder(args...);
}

int main(int argc, char* argv[])
{
	long summation = adder(1, 2, 3);
	std::string s1 = "a", s2 = "b", s3 = "c";
	std::string concatenation = adder(s1, s2, s3);

	std::cout << "summation: " << summation << std::endl;
	std::cout << "concatenation: " << concatenation << std::endl;

	return 0;
}
