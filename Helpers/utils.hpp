#pragma once

#define NOMINMAX
#include <Windows.h>
#include "../valve_sdk/sdk.hpp"


namespace Utils {
	unsigned int FindInDataMap(datamap_t* pMap, const char* name);


	void AttachConsole();
	void DetachConsole();
	bool ConsolePrint(const char* msg, ...);
	char ConsoleReadKey();
	std::uint8_t* PatternScan(void* module, const char* signature);
	
}