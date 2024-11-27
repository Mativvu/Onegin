#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdio.h>

#include "Errors.h"
#include "StringSort.h"

const size_t MAX_NAME_LEN = 16;

const char* const DEFAULT_INPUT_FILE_NAME  = "files/input/input.txt";
const char* const DEFAULT_OUTPUT_FILE_NAME = "files/output/output.txt";

#define unused(param) do { (void)(param); } while (0)

enum Mode_bit
{
    DEFAULT = 1U << 0,
    DEBUG   = 1U << 1,
    HELP    = 1U << 2,
    INPUT   = 1U << 3,
    OUTPUT  = 1U << 4,
    SORT    = 1U << 5,
    APPEND  = 3U << 3
};

typedef struct Sorter
{
    Sorting_func sorter;
    const char*  name;
} Sorter;

typedef struct FlagParseData
{
    Sorting_func  sorter;
    FILE*         input_stream;
    FILE*         output_stream;
} FlagParseData;

typedef Status (*Command_function)(const int argc, const char** argv, int* arg_index,
                                   FlagParseData* ParsedData);

typedef struct Command
{
    const Mode_bit    mode_bit;
    Command_function  function;
    const char*       name;
    const char*       short_name;
    const char*       description;
} Command;

extern Command commands_array[];
extern size_t  commands_array_size;

Status setSortingMethod (const int argc, const char** argv, int* arg_index, FlagParseData* ParsedData);
Status setDefaultStreams(const int argc, const char** argv, int* arg_index, FlagParseData* ParsedData);
Status setAppendStream  (const int argc, const char** argv, int* arg_index, FlagParseData* ParsedData);
Status setOutputStream  (const int argc, const char** argv, int* arg_index, FlagParseData* ParsedData);
Status setInputStream   (const int argc, const char** argv, int* arg_index, FlagParseData* ParsedData);
Status printCommands    (const int argc, const char** argv, int* arg_index, FlagParseData* ParsedData);

#endif //COMMANDS_H
