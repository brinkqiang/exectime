
#include "exectime.h"

int main( int argc, char* argv[] ) {

    Iexectime* module = exectimeGetModule();
    if (module)
    {
        module->Test();
        module->Release();
    }
    return 0;
}
