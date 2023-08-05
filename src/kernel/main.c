#include "system.h"

extern void main()
{
    idtInstall();
    isrs_install();
    init_video();

    return;
}