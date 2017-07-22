#include "SharedLibrary.h"

SharedLibrary::SharedLibrary(const char* libname)
{
#ifdef _WIN32
	HINSTANCE handle = LoadLibrary(libname);
	
	if (handle == nullptr)
	{
		LPVOID buffer;
		DWORD bufferLength = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&buffer, 0, nullptr);

		if (bufferLength > 0)
		{
			std::string msg((LPCSTR)buffer, ((LPCSTR)buffer) + bufferLength);
			HeapFree(GetProcessHeap(), 0, buffer);
			throw std::runtime_error("Unable to load library \"" + std::string(libname) + "\": " + msg);
		}

		throw std::runtime_error("Unable to load library \"" + std::string(libname) + "\": Unknown error.");
	}

	libHandle = (void*)LoadLibraryA(libname);
#elif __linux__
	libhandle = dlopen(libname, RTLD_LAZY);

	if (dlerror() != 0)
	{
		throw std::runtime_error(dlerror());
	}
#endif
}

SharedLibrary::~SharedLibrary()
{
#ifdef _WIN32
	FreeLibrary((HMODULE)(libHandle));
#elif __linux__
	dlclose(libhandle);
#endif
	libHandle = nullptr;
}
