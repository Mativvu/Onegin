#include <stdio.h>
#include <stdarg.h>

#include "Color.h"

void colorPrintf(const char* color, const char* format, ...)
{
    va_list args;
    va_start(args, format);

    printf("%s", color);
    vprintf(format, args);
    printf("%s", RESET);

    va_end(args);
}
