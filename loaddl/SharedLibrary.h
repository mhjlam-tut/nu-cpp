#pragma once

#if defined(_WIN32)
#include <windows.h>
#elif defined(__linux__)
#include <dlfnc.h>
#endif
#include <stdexcept>

class SharedLibrary
{
private:
	void* libHandle = nullptr;

public:
	SharedLibrary(const char* libname);
	~SharedLibrary();

	template<typename R, typename... A>
	R Call(const char* procname, A... arguments);
};

template<typename R, typename... A>
R SharedLibrary::Call(const char* procname, A... arguments)
{
	using Proc = R(__stdcall*)(A...);

#if defined(_WIN32)
	FARPROC fp = GetProcAddress((HMODULE)(libHandle), procname);

	if (fp == nullptr)
	{
		LPVOID buffer;
		DWORD bufferLength = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&buffer, 0, nullptr);

		if (bufferLength > 0)
		{
			std::string msg((LPCSTR)buffer, ((LPCSTR)buffer) + bufferLength);
			HeapFree(GetProcessHeap(), 0, buffer);
			throw std::runtime_error("Unable to find module function \"" + std::string(procname) + "\": " + msg);
		}

		throw std::runtime_error("Unable to find module function \"" + std::string(procname) + "\": Unknown error.");
	}

	Proc proc = (Proc)fp;
#elif defined(__linux__)
	Proc proc = (Proc)dlsym(libhandle, procname);

	if (dlerror() != 0)
	{
		throw std::runtime_error(dlerror());
	}
#endif

	return proc(std::forward<A>(arguments)...);
}
