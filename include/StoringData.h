#ifndef STORINGDATA_H
#define STORINGDATA_H

#include <stdio.h>

#include "Errors.h"

typedef struct MyString
{
    char*  string;
    size_t length;
} MyString;

typedef struct MyArray
{
    MyString* data;
    size_t    size;
} MyArray;

Status readDataFromFile(FILE* stream_in, MyString* File_text);
Status getFileSize     (FILE* stream_in, size_t*    file_size);

Status linkStringPointers(MyString* File_text, MyArray* String_array);
Status printStringArray(FILE* stream_out, const MyArray* array);

void myStringReplace(MyString* string, char old_symbol, char    new_symbol);
void myStringCount  (MyString* string, char symbol,     size_t* count);

void freeMyArray(MyArray* array);
void freeMyString (MyString*  array);

#endif //STORINGDATA_H
