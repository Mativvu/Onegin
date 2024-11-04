#ifndef COMMANDS_H
#define COMMANDS_H

#include "Errors.h"
#include "Files.h"

#define unused(param) (void)(param);

//TODO: add modes to commands
enum Mode {
    DEFAULT = 1U << 0, /*< Mode to use default "input.txt" and "output.txt" files. */
    DEBUG   = 1U << 1, /*< Prints what to do to enable debug mode. */
    HELP    = 1U << 2, /*< Prints describtion to each available flag and stops program. */
    INPUT   = 1U << 3, /*< Activates input from file that user inputted. */
    OUTPUT  = 1U << 4  /*< Activates output to file that user inputted. */
};

typedef Status (*Command_function)(const int argc, const char** argv, int* arg_index,
                                   FlagableData** mainData);

typedef struct Command
{
    const Mode       mode;
    Command_function function;
    const char*      name;
    const char*      short_name;
    const char*      describtion;
} Command;

extern Command commands_array[];
extern size_t  commands_array_size;

Status setDefaultStreams(const int argc, const char** argv, int* arg_index, FlagableData** mainData);
Status setOutputStream  (const int argc, const char** argv, int* arg_index, FlagableData** mainData);
Status setInputStream   (const int argc, const char** argv, int* arg_index, FlagableData** mainData);
Status printCommands    (const int argc, const char** argv, int* arg_index, FlagableData** mainData);

#endif //COMMANDS_H
