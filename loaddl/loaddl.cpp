#include <string>

#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <dlfnc.h>
#endif

struct DynamicLibrary
{
	void* libhandle = nullptr;
	char* error = nullptr;

	DynamicLibrary() { error = new char[256]; }
	~DynamicLibrary() { delete libhandle; delete[] error; }
};


DynamicLibrary LoadPlugin(std::string lib_name)
{
	DynamicLibrary dl;
	HINSTANCE handle = LoadLibrary(lib_name.c_str());

	if (handle == nullptr)
	{
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, nullptr, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), dl.error, 256, nullptr);
	}

	dl.error = GetLastError(void);

	return p_ptr;
}

void UnLoadPlugin(Plugin* p_ptr)
{
	FreeLibrary((HMODULE)(*(p_ptr->data));
	free(p_ptr);
}

FARPROC FunctionFromPlugin(Plugin* p_ptr, const char* name)
{
	void* handle = GetProcAddress((HMODULE)(*(p_ptr->data)), name);
	p_ptr->error = GetLastError(void);

	return handle;
}

int main(int argc, char* argv[])
{


	return 0;
}
