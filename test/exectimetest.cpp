
#include "exectime.h"

#define BUFFER_SIZE 256

#ifdef WIN32
#define popen _popen
#define pclose _pclose

#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>

#endif

std::string DMExecute(const char* cmd)
{
    std::string result;

    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);

    if (!pipe) return result;

    while (!feof(pipe.get())) {
        char szBuf[BUFFER_SIZE+1] = {0};
        if (fgets(szBuf, BUFFER_SIZE, pipe.get()) != nullptr)
        {
            result += szBuf;
        }
    }
    return result;
}

static inline uint32_t GetTickCount32() {
#ifdef _MSC_VER
    return ::GetTickCount();
#else
    struct timespec ts = { 0 };
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
#endif
}

int main( int argc, char* argv[] ) {
    if (1 == argc)
    {
        return -1;
    }

    uint32_t start = GetTickCount32();
    std::string strRet = DMExecute(argv[1]);
    uint32_t end = GetTickCount32();
    std::cout << argv[1] << std::endl;
    std::cout << strRet << std::endl;
    std::cout << start - end << " ms" << std::endl;
    return 0;
}
