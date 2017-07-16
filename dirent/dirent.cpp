#include <string>
#include "dirent.h"

static bool find_directory(const std::string dirname, bool recursive = false);

int main(int argc, char* argv[])
{
	// List current working directory if no arguments on command line
	if (argc == 1)
	{
		find_directory(".");
	}
	// For each directory in command line
	else
	{
		for (int i = 1; i < argc; ++i)
		{
			if (!find_directory(argv[i]))
			{
				continue;
			}
		}
	}

	return 0;
}

// Find files and subdirectories recursively
static bool find_directory(std::string rootpath, bool recursive)
{
	// Open directory stream
	DIR* directory = opendir(rootpath.c_str());
	dirent* ent;

	if (directory == nullptr)
	{
		printf("Cannot open directory %s\n", rootpath.c_str());
		return false;
	}

	// Append directory separator if not already there
	if (rootpath.back() != ':' && rootpath.back() != '/' && rootpath.back() != '\\')
	{
		rootpath += '/';
	}

	// Print all files and directories within the directory
	while ((ent = readdir(directory)) != nullptr)
	{
		// Decide what to do with the directory entry
		switch (ent->d_type)
		{
			case DT_LNK: // symbolic link
			case DT_REG: // regular file
				printf("%s\n", (rootpath + ent->d_name).c_str());
				break;

			case DT_DIR: // Scan sub-directory recursively
				if (recursive && (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0))
				{
					find_directory(rootpath + ent->d_name);
				}
				break;
		}
	}

	closedir(directory);

	return true;
}
