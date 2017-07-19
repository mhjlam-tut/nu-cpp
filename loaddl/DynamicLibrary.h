#pragma once

class DynamicLibrary
{
private:
	void* libhandle = nullptr;

public:
	DynamicLibrary(const char* libname);
	~DynamicLibrary();

	void CallFunc(const char* funcname);
};
