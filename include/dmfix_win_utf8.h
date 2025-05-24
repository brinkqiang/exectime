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

#ifndef __DMFIX_WIN_UTF8_H_INCLUDE__
#define __DMFIX_WIN_UTF8_H_INCLUDE__

#ifdef _WIN32
#include <windows.h>
#if !defined(__cplusplus) && defined(_WIN32)
#include <stdbool.h>
#endif
#else
#include <locale.h>
#if !defined(__cplusplus)
#include <stdbool.h>
#endif
#endif

#define DMFIX_INTERNAL_CODE_PAGE_UTF8 65001

static inline bool dm_win_utf8_internal_do_setup(void) {
#ifdef _WIN32
    BOOL output_cp_set_ok = SetConsoleOutputCP(DMFIX_INTERNAL_CODE_PAGE_UTF8);
    BOOL input_cp_set_ok = SetConsoleCP(DMFIX_INTERNAL_CODE_PAGE_UTF8);
    return (output_cp_set_ok != 0 && input_cp_set_ok != 0);
#else
    if (setlocale(LC_ALL, "en_US.utf8") != NULL) {
        return true;
    }
    else if (setlocale(LC_ALL, "C.UTF-8") != NULL) {
        return true;
    }
    return false;
#endif
}


#ifdef __cplusplus

namespace DmInternal {
    struct DmWinUtf8Initializer {
        DmWinUtf8Initializer() {
            dm_win_utf8_internal_do_setup();
        }
    };
    static inline DmWinUtf8Initializer g_dm_win_utf8_auto_initializer_instance;
} // namespace DmInternal

extern "C" bool dm_win_utf8_init() {
    return dm_win_utf8_internal_do_setup();
}

#else
static inline bool dm_win_utf8_init(void) {
    return dm_win_utf8_internal_do_setup();
}

#endif // __cplusplus

#endif // __DMFIX_WIN_UTF8_H_INCLUDE__