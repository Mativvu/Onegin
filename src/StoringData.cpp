#include <string.h>
#include <ctype.h>

#include "StringSort.h"
#include "Errors.h"
#include "Debug.h"

Status readDataFromFile(FILE* stream_in, MyString* File_text)
{
    myAssert(stream_in != nullptr);
    myAssert(File_text != nullptr);

    Status status = getFileSize(stream_in, &File_text->length);
    returnIfError(status);

    File_text->string = (char*)calloc(File_text->length, sizeof(char));
    if (File_text->string == nullptr)
    {
        return ALLOC_ERR;
    }

    size_t read = fread(File_text->string, sizeof(char), File_text->length, stream_in);
    if (read != File_text->length)
    {
        return READ_ERR;
    }
    return OK;
}

Status getFileSize(FILE* stream_in, size_t* file_size)
{
    myAssert(stream_in != nullptr);
    myAssert(file_size != nullptr);

    long initial_position = ftell(stream_in);

    fseek(stream_in, 0, SEEK_END);
    long end_position = ftell(stream_in);
    if (end_position < 0 || end_position - initial_position < 0)
    {
        return SEEK_ERR;
    }
    fseek(stream_in, initial_position, SEEK_SET);

    *file_size = (size_t)(end_position - initial_position);
    return OK;
}

Status linkStringPointers(MyString* File_text, MyArray* string_array)
{
    myAssert(File_text != nullptr);
    myAssert(File_text->string != nullptr);
    myAssert(string_array != nullptr);

    myStringReplace(File_text, '\n', '\0');

    for (size_t index = 0; index < File_text->length; ++index)
    {
        if (File_text->string[index] == '\0')
        {
            string_array->size++;
        }
    }

    string_array->data = (MyString*)calloc(string_array->size, sizeof(MyString));
    if (string_array->data == nullptr)
    {
        return ALLOC_ERR;
    }

    size_t current_length = 0;
    size_t string_index   = 0;
    for (size_t file_index = 0; file_index < File_text->length; ++file_index)
    {
        if (File_text->string[file_index] == '\0')
        {
            if (current_length != 0)
            {
                string_array->data[string_index].string = (File_text->string + (file_index - current_length));
                string_array->data[string_index].length = current_length;
                string_index++;
                current_length = 0;
            }
        }
        else
        {
            current_length++;
        }
    }
    string_array->size = string_index;
    return OK;
}

Status printStringArray(FILE* stream_out, const MyArray* array)
{
    myAssert(stream_out != nullptr);
    myAssert(array != nullptr);
    myAssert(array->data != nullptr);

    fprintf(stream_out, "\n");
    for (size_t index = 0; index < array->size; ++index)
    {
        fprintf(stream_out, "%s \n", array->data[index].string);
    }
    return OK;
}

void myStringReplace(MyString* string, char old_symbol, char new_symbol)
{
    myAssert(string != nullptr);
    myAssert(string->string != nullptr);

    for (size_t index = 0; index < string->length; ++index)
    {
        if (string->string[index] == old_symbol)
        {
            string->string[index] = new_symbol;
        }
    }
    return;
}

void freeMyArray(MyArray* array)
{
    free(array->data);
    array->data = nullptr;
}

void freeMyString(MyString* string)
{
    free(string->string);
    string->string = nullptr;
}
