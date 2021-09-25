#include "utils.hpp"
#include <Windows.h>
#include <string>

HANDLE h_out, h_in, h_err;
HANDLE old_out, old_in, old_err;

namespace Utils {
    void AttachConsole() 
    {
        //get handles to stdin and stdout
        old_out = GetStdHandle(STD_OUTPUT_HANDLE);
        old_in = GetStdHandle(STD_INPUT_HANDLE);
        old_err = GetStdHandle(STD_ERROR_HANDLE);

        AllocConsole() && ::AttachConsole(GetCurrentProcessId());

        h_out = GetStdHandle(STD_OUTPUT_HANDLE);
        h_in = GetStdHandle(STD_INPUT_HANDLE);
        h_err = GetStdHandle(STD_ERROR_HANDLE);

        SetConsoleMode(h_out,
            ENABLE_PROCESSED_OUTPUT | ENABLE_WRAP_AT_EOL_OUTPUT);

        SetConsoleMode(h_in,
            ENABLE_INSERT_MODE | ENABLE_EXTENDED_FLAGS |
            ENABLE_PROCESSED_INPUT | ENABLE_QUICK_EDIT_MODE);
    }

    void DetachConsole() 
    {
        if (h_out && h_in && h_err) {
            FreeConsole();

            if (old_out)
                SetStdHandle(STD_OUTPUT_HANDLE, old_out);
            if (old_in)
                SetStdHandle(STD_OUTPUT_HANDLE, old_in);
            if (old_err)
                SetStdHandle(STD_OUTPUT_HANDLE, old_err);
        }
    }

    bool ConsolePrint(const char* msg, ...)
    {
        if (!h_out)
            return false;

        char buf[1024];
        va_list va;

        va_start(va, msg);
        _vsnprintf_s(buf, 1024, msg, va);
        va_end(va);

        return WriteConsoleA(h_out, buf, static_cast<DWORD>(strlen(buf)), nullptr, nullptr);
    }
}