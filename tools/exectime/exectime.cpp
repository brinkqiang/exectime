
#include "execute.h"

int main( int argc, char* argv[] )
{
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

    Iexecute* execute = executeGetModule();

    if (NULL != execute)
    {
        execute->exec(strArgs);

        execute->Release();
    }

    return 0;
}
