#include <string.h>
#include <ctype.h>

#include "StringSort.h"
#include "Errors.h"
#include "Debug.h"

Status readDataFromFile(FILE* stream_in, CharArray* File_text)
{
    myAssert(stream_in != nullptr);
    myAssert(File_text != nullptr);

    fseek(stream_in, 0, SEEK_END);
    long res = ftell(stream_in);
    if (res < 0)
    {
        return SEEK_ERR;
    }
    File_text->size = res;
    fseek(stream_in, 0, SEEK_SET);

    File_text->data = (char*)calloc(File_text->size, sizeof(char));
    if (File_text->data == nullptr)
    {
        return ALLOC_ERR;
    }

    size_t read = fread(File_text->data, sizeof(char), File_text->size, stream_in);
    if (read != File_text->size)
    {
        return READ_ERR;
    }
    return OK;
}

Status linkStringPointers(CharArray* File_text, SmartArray* String_array)
{
    myAssert(File_text != nullptr);
    myAssert(File_text->data != nullptr);
    myAssert(String_array != nullptr);

    for (size_t index = 0; index < File_text->size; ++index)
    {
        if (File_text->data[index] == '\n')
        {
            File_text->data[index] = '\0';
            String_array->size++;
        }
    }

    String_array->data = (SmartString*)calloc(String_array->size, sizeof(SmartString));
    if (String_array->data == nullptr)
    {
        return ALLOC_ERR;
    }

    size_t current_length = 0;
    size_t string_index   = 0;
    for (size_t file_index = 0; file_index < File_text->size; ++file_index)
    {
        if (File_text->data[file_index] == '\0' && current_length != 0)
        {
            char* string = (File_text->data + (file_index - current_length));
            stripString(&string, &current_length);

            if (string != nullptr)
            {
                String_array->data[string_index].string = string;
                String_array->data[string_index].length = current_length;
                string_index++;
            }
            current_length = 0;
        }
        else
        {
            current_length++;
        }
    }
    if (string_index != String_array->size)
    {
        String_array->data = (SmartString*)realloc(String_array->data, sizeof(SmartString) * string_index);
        if (String_array->data == nullptr)
        {
            return ALLOC_ERR;
        }
        String_array->size = string_index;
    }
    return OK;
}

Status printStringArray(FILE* stream_out, const SmartArray* array)
{
    myAssert(stream_out != nullptr);
    myAssert(array != nullptr);
    myAssert(array->data != nullptr);

    for (size_t index = 0; index < array->size; ++index)
    {
        fprintf(stream_out, "%s \n", array->data[index].string);
    }
    return OK;
}

void stripString(char** string, size_t* length)
{
    myAssert(string != nullptr);
    myAssert(length != nullptr);

    size_t offset = 0;
    while (!isalpha((*string)[offset]))
    {
        offset++;
        if (offset >= *length)
        {
            break;
        }
    }
    *string += offset;
    *length -= offset;

    offset = *length - 1;
    while (!isalpha((*string)[offset]))
    {
        offset -= 1;
        if (offset < 0)
        {
            break;
        }
    }
    *length = offset + 1;

    if (*length == 0)
    {
        *string = nullptr;
    }
}

void freeSmartArray(SmartArray* array)
{
    free(array->data);
}

void freeCharArray (CharArray*  array)
{
    free(array->data);
}
