#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdio.h>

#include "Errors.h"
#include "StringSort.h"

const size_t MAX_ALGO_NAME = 16;

#define unused(param) (void)(param);

enum Mode_bit
{
    DEFAULT = 1U << 0, /*< Mode to use default "input.txt" and "output.txt" files. */
    DEBUG   = 1U << 1, /*< Prints what to do to enable debug mode. */
    HELP    = 1U << 2, /*< Prints describtion to each available flag and stops program. */
    INPUT   = 1U << 3, /*< Activates input from file that user inputted. */
    OUTPUT  = 1U << 4, /*< Activates output to file that user inputted. */
    SORT    = 1U << 5  /*< To choose which sorting algorithm to use. */
};

typedef struct MyStream
{
    char*  file_name;
    FILE*  stream;
} MyStream;

typedef struct FlagParseData
{
    Sorting_func  sorter;
    MyStream      input_stream;
    MyStream      output_stream;
} FlagParseData;

typedef Status (*Command_function)(const int argc, const char** argv, int* arg_index,
                                   FlagParseData* ParsedData);

typedef struct Command
{
    const Mode_bit    mode_bit;
    Command_function  function;
    const char*       name;
    const char*       short_name;
    const char*       describtion;
} Command;

extern Command commands_array[];
extern size_t  commands_array_size;

Status setSortingMethod (const int argc, const char** argv, int* arg_index, FlagParseData* ParsedData);
Status setDefaultStreams(const int argc, const char** argv, int* arg_index, FlagParseData* ParsedData);
Status setOutputStream  (const int argc, const char** argv, int* arg_index, FlagParseData* ParsedData);
Status setInputStream   (const int argc, const char** argv, int* arg_index, FlagParseData* ParsedData);
Status printCommands    (const int argc, const char** argv, int* arg_index, FlagParseData* ParsedData);

char* allocStringLiteral(const char string[]);

void freeAndCloseStream(MyStream* stream);

#endif //COMMANDS_H
