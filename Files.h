#ifndef FILES_H
#define FILES_H

#include <stdio.h>

typedef struct MyStream
{
    char* file_name;
    FILE* stream;
} MyStream;

typedef struct FlagableData
{
    MyStream input_stream;
    MyStream output_stream;
} FlagableData;

char* allocStringLiteral(const char string[]);

void freeAndClose(MyStream* stream);

#endif //FILES_H
