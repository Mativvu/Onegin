#include <string.h>
#include <stdlib.h>

#include "Files.h"

char* allocStringLiteral(const char string[])
{
    char* dynamic_string = nullptr;

    size_t length = strlen(string) + 1;

    dynamic_string = (char*)calloc(length, sizeof(char));
    if (dynamic_string == nullptr)
    {
        return nullptr;
    }

    dynamic_string[--length] = '\0';
    while (--length >= 0)
    {
        dynamic_string[length] = string[length];
        if (length == 0)
        {
            break;
        }
    }
    return dynamic_string;
}

void freeAndClose(MyStream* stream)
{
    free(stream->file_name);
    fclose(stream->stream);
}
