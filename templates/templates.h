#pragma once

template<typename T> T Get() { return T; }

template<> int Get<int>()
{
	return 1;
}

template<> double Get<double>()
{
	return 1.0f;
}

template<> std::string Get<std::string>()
{
	return std::string("text");
}
