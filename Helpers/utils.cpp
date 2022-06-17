#include "utils.hpp"

#include <Windows.h>
#include <string>
#include <vector>

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

        ConsolePrint("Attached");
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

        return !!WriteConsoleA(h_out, buf, static_cast<DWORD>(strlen(buf)), nullptr, nullptr); //!! normalizes result to 0 or 1
    }

    char ConsoleReadKey()
    {
        if (!h_in)
            return false;

        auto key = char{ 0 };
        auto keysread = DWORD{ 0 };
        ReadConsoleA(h_in, &key, 1, &keysread, nullptr);
        
        return key;
    }

    std::uint8_t* PatternScan(void* module, const char* signature)
    {
        static auto pattern_to_byte = [](const char* pattern) {
            auto bytes = std::vector<int>{};
            auto start = const_cast<char*>(pattern);
            auto end = const_cast<char*>(pattern) + strlen(pattern);

            for (auto current = start; current < end; ++current) {
                if (*current == '?') {
                    ++current;
                    if (*current == '?') {
                        ++current;
                        bytes.push_back(-1);
                    }
                    else {
                        bytes.push_back(strtoul(current, &current, 16));
                    }
                }
            }
            return bytes;
        };

        auto dosHeader = (PIMAGE_DOS_HEADER)module;
        auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)module + dosHeader->e_lfanew);

        auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
        auto patternBytes = pattern_to_byte(signature);
        auto scanBytes = reinterpret_cast<std::uint8_t*>(module);

        auto s = patternBytes.size();
        auto d = patternBytes.data();

        for (auto i = 0ul; i < sizeOfImage - s; ++i) {
            bool found = true;
            for (auto j = 0ul; j < s; ++j) {
                if (scanBytes[i + j] != d[j] && d[j] != -1) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return &scanBytes[i];
            }
        }
        return nullptr;
    }

    unsigned int FindInDataMap(datamap_t* pMap, const char* name) {
        while (pMap) {
            for (int i = 0; i < pMap->dataNumFields; i++) {
                if (pMap->dataDesc[i].fieldName == NULL)
                    continue;

                if (strcmp(name, pMap->dataDesc[i].fieldName) == 0)
                    return pMap->dataDesc[i].fieldOffset[TD_OFFSET_NORMAL];

                if (pMap->dataDesc[i].fieldType == FIELD_EMBEDDED) {
                    if (pMap->dataDesc[i].td) {
                        unsigned int offset;

                        if ((offset = FindInDataMap(pMap->dataDesc[i].td, name)) != 0)
                            return offset;
                    }
                }
            }
            pMap = pMap->baseMap;
        }
        return 0;
    }
}