#include "l0-infra/tools/EnvHelper.h"
#include <stdio.h>

void showVersionTime()
{
    printf("Current version building time :%s %s.\n", __DATE__,  __TIME__);
}