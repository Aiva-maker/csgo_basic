#pragma once

#include <Windows.h>


namespace Utils {
	unsigned int FindInDataMap(datamap_t* pMap, const char* name);


	void AttachConsole();
	void DetachConsole();
	bool ConsolePrint(const char* msg, ...);
	char ConsoleReadKey();
	std::uint8_t* PatternScan(void* module, const char* signature);
	
}