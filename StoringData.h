#ifndef STORINGDATA_H
#define STORINGDATA_H

#include <stdio.h>

#include "Errors.h"

typedef struct SmartString
{
    char*  string;
    size_t length;
} SmartString;

typedef struct SmartArray
{
    SmartString* data;
    size_t       size;
} SmartArray;

typedef struct CharArray
{
    char*  data;
    size_t size;
} CharArray;

Status readDataFromFile(FILE* stream_in, CharArray* file_text);

Status linkStringPointers(CharArray* file_text, SmartArray* string_array);

void stripString(char** string, size_t* length);

Status printStringArray(FILE* stream_out, const SmartArray array);

void freeSmartArray(SmartArray* array);
void freeCharArray (CharArray*  array);

#endif //STORINGDATA_H
