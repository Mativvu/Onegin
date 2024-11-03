#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "StringSort.h"
#include "Errors.h"
#include "Debug.h"

Status readDataFromFile(const FILE* stream_in, char** array, size_t* size)
{
    myAssert(stream_in != nullptr);
    myAssert(size != nullptr);
    myAssert(array != nullptr);

    fseek(stream_in, 0, SEEK_END);
    long res = ftell(stream_in);
    if (res < 0)
    {
        return SEEK_ERR;
    }
    *size = res;
    fseek(stream_in, 0, SEEK_SET);

    *array = (char*)calloc(*size, sizeof(char));
    if (*array == nullptr)
    {
        return ALLOC_ERR;
    }

    size_t read = fread(*array, sizeof(char), *size, stream_in);
    if (read != *size)
    {
        return READ_ERR;
    }
    return OK;
}

Status linkTheFuckingPointers(const FILE* stream_in, char** data_array, const size_t data_arr_size,
                                              smartString** string_array,    size_t* string_arr_size)
{
    myAssert(stream_in != nullptr);
    myAssert(data_array != nullptr);
    myAssert(*data_array != nullptr);
    myAssert(string_arr_size != nullptr);
    myAssert(string_array != nullptr);

    for (size_t index = 0; index < data_arr_size; ++index)
    {
        if ((*data_array)[index] == '\n')
        {
            (*data_array)[index] = '\0';
            (*string_arr_size)++;
        }
    }

    *string_array = (smartString*)calloc(*string_arr_size, sizeof(smartString));
    if (*string_array == nullptr)
    {
        return ALLOC_ERR;
    }

    int current_length = 0;
    size_t string_index = 0;
    for (size_t data_index = 0; data_index < data_arr_size; ++data_index)
    {
        if ((*data_array)[data_index] == '\0')
        {
            (*string_array)[string_index].string = (*data_array + (data_index - current_length));
            (*string_array)[string_index].length = current_length;
            string_index++;
            current_length = 0;
        }
        else
        {
            current_length++;
        }
    }
    return OK;
}

Status printStringArray(const FILE* stream_out, const smartString* array, const size_t size)
{
    myAssert(stream_out != nullptr);
    myAssert(array != nullptr);
    
    for (size_t index = 0; index < size; ++index)
    {
        fprintf(stream_out, "%s \n", array[index].string);
    }
    return OK;
}
