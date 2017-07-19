#include "DynamicLibrary.h"
#include <stdexcept>
#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <dlfnc.h>
#endif

DynamicLibrary::DynamicLibrary(const char* libname)
{
#ifdef _WIN32
	HINSTANCE handle = LoadLibrary(libname);

	if (handle == nullptr)
	{
		char errmsg[512];
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, nullptr, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), errmsg, 256, nullptr);
		throw std::runtime_error(errmsg);
	}

	libhandle = (void*)LoadLibraryA(libname);
#elif __linux__
	libhandle = dlopen(libname, RTLD_LAZY);

	if (dlerror() != 0)
	{
		throw std::runtime_error(dlerror());
	}
#endif
}

DynamicLibrary::~DynamicLibrary()
{
#ifdef _WIN32
	FreeLibrary((HMODULE)(libhandle));
#elif __linux__
	dlclose(libhandle);
#endif
}

void DynamicLibrary::CallFunc(const char* funcname) // todo: arguments
{
#ifdef _WIN32
	FARPROC proc = GetProcAddress((HMODULE)(libhandle), funcname);

	if (proc == nullptr)
	{
		char errmsg[512];
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, nullptr, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), errmsg, 256, nullptr);
		throw std::runtime_error(errmsg);
	}

	proc();
#elif __linux__
	void* proc = dlsym(libhandle, funcname);

	if (dlerror() != 0)
	{
		throw std::runtime_error(dlerror());
	}

	proc();
#endif
}
