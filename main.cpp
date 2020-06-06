#include <iostream>
#include "Interface.h"
#include "CPU.h"

int main()
{
    Interface shell;
    for (;;) { shell.shell(); }
    return 0;
}