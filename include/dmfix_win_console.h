// Copyright (c) 2018 brinkqiang (brink.qiang@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

// cmake env
// add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

#ifndef __DMFIX_WIN_CONSOLE_H_INCLUDE__
#define __DMFIX_WIN_CONSOLE_H_INCLUDE__

#ifdef _WIN32
#include <windows.h>
#if !defined(__cplusplus) && defined(_WIN32)
#include <stdbool.h>
#endif
#endif
static inline bool dm_win_console_internal_do_setup(void) {
#ifdef _WIN32
    bool any_console_handle_successfully_configured = false;
    bool at_least_one_console_handle_targeted = false;
    HANDLE handles_to_check[2] = {GetStdHandle(STD_OUTPUT_HANDLE), GetStdHandle(STD_ERROR_HANDLE)};

    for (int i = 0; i < 2; ++i) {
        HANDLE hCurrent = handles_to_check[i];
        if (hCurrent != INVALID_HANDLE_VALUE && GetFileType(hCurrent) == FILE_TYPE_CHAR) {
            at_least_one_console_handle_targeted = true;
            DWORD dwOriginalMode = 0;
            if (GetConsoleMode(hCurrent, &dwOriginalMode)) {
                if (!(dwOriginalMode & ENABLE_VIRTUAL_TERMINAL_PROCESSING)) {
                    if (!SetConsoleMode(hCurrent, dwOriginalMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING)) {
                        return false;
                    }
                }

                any_console_handle_successfully_configured = true;
            } else {
                return false;
            }
        }
    }

    if (!at_least_one_console_handle_targeted) {
        return false;
    }
    
    return any_console_handle_successfully_configured;
#else
    return true;
#endif
}


#ifdef __cplusplus

namespace DmInternal {
    struct DmWinConsoleInitializer {
        DmWinConsoleInitializer() {
            dm_win_console_internal_do_setup();
        }
    };

    static inline DmWinConsoleInitializer g_dm_win_console_auto_initializer_instance;
} // namespace DmInternal

extern "C" bool dm_win_console_init() {
    return dm_win_console_internal_do_setup();
}

#else
static inline bool dm_win_console_init(void) {
    return dm_win_console_internal_do_setup();
}

#endif // __cplusplus

#endif // __DMFIX_WIN_CONSOLE_H_INCLUDE__