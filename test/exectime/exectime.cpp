
#include "exectime.h"


int main( int argc, char* argv[] ) {
    if (1 == argc)
    {
        return -1;
    }

    std::string strArgs;
    for (int i=1; i < argc; ++i)
    {
        if (1 != i)
        {
            strArgs += " ";
        }
        strArgs += argv[i];
    }

    IExectime* poModule = ExectimeGetModule();
    if (NULL == poModule)
    {
        return -1;
    }
    
    uint32_t start = poModule->GetTickCount32();
    std::string strRet = poModule->DMExecute(strArgs.c_str());
    uint32_t end = poModule->GetTickCount32();
    std::cout << strRet << std::endl;
    std::cout << end - start << " ms" << std::endl;

    poModule->Release();
    return 0;
}
