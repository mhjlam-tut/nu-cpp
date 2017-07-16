#include <string>
#include <iostream>
#include "getopt.hpp"

int main(int argc, char* argv[])
{
	// - No initialization required: (argc, argv) pair automatically retrieved.
	// - First argument is default option value, then all option indentifiers follow.
	bool help = getarg(false, "-h", "--help", "-?");
	int version = getarg(0, "-v", "--version", "--show-version");
	int depth = getarg(1, "-d", "--depth", "--max-depth");
	std::string file = getarg("", "-f", "--file");
	// [...]
	std::cout << help << ',' << file << ',' << version << std::endl;
}
