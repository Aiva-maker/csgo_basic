#pragma once
#include <Windows.h>


namespace Utils {
	void AttachConsole();
	void DetachConsole();
	bool ConsolePrint(const char* msg, ...);
	char ConsoleReadKey();
}