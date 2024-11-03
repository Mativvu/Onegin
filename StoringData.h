#ifndef STORINGDATA_H
#define STORINGDATA_H

#include <stdio.h>
#include <stdlib.h>

#include "Errors.h"

typedef struct SmartString
{
    char* string;
    int length;
} smartString;

Status readDataFromFile(const FILE* stream_in, char** array, size_t* size);
Status linkTheFuckingPointers(const FILE* stream_in, char** data_array, const size_t data_arr_size,
                                              smartString** string_array,    size_t* string_arr_size);

Status printStringArray(const FILE* stream_out, const smartString* array, const size_t size);

#endif //STORINGDATA_H
