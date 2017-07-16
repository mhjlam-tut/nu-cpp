#include <fstream>
#include <iostream>
#include <filesystem>
#include <memory>

int main()
{
	namespace fs = std::experimental::filesystem;

	for (auto& de : fs::directory_iterator("C:\\"))
	{
		if (fs::is_regular_file(de.path()))
		{
			fs::path p = de.path();

			if (p.has_filename()) std::cout << "filename: " << p.filename() << std::endl;
			if (p.has_stem()) std::cout << "stem: " << p.stem() << std::endl;
			if (p.has_extension()) std::cout << "extension: " << p.extension() << std::endl;
			if (p.has_root_name()) std::cout << "root name: " << p.root_name() << std::endl;
			if (p.has_root_directory()) std::cout << "root directory: " << p.root_directory() << std::endl;
			if (p.has_root_path()) std::cout << "root path: " << p.root_path() << std::endl;
			if (p.has_relative_path()) std::cout << "relative path: " << p.relative_path() << std::endl;
			if (p.has_parent_path()) std::cout << "parent path: " << p.parent_path() << std::endl;

			if (p.is_absolute()) std::cout << "path is absolute" << std::endl;
			if (p.is_relative()) std::cout << "path is relative" << std::endl;
			std::cout << std::endl;
		}
	}
}
