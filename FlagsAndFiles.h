#ifndef FLAGSANDFILES_H
#define FLAGSANDFILES_H

#include <stdio.h>

#include "Errors.h"

//TODO: add modes to commands
enum Mode {
    ModeTest   = 1U << 0, /**< Unit testing mode. */
    ModeFile   = 1U << 1, /**< Mode to use default "input.txt" and "output.txt" files. */
    ModeDebug  = 1U << 2, /**< Prints what to do to enable debug mode. */
    ModeHelp   = 1U << 3, /**< Prints describtion to each available flag and stops program. */
    ModeInput  = 1U << 4, /**< Activates input from file that user inputted. */
    ModeOutput = 1U << 5, /**< Activates output to file that user inputted. */
    ModeRT     = 1U << 6  /**< Prints "РТ" sign and shouts "РТ" from speakers. */
};

typedef struct MyStream
{
    char* file_name;
    FILE* stream;
} myStream;

typedef struct FlagableData
{
    myStream input_stream;
    myStream output_stream;
} flagableData;

typedef Status (*Command_function)(const int argc, const char** argv, int* arg_index,
                                   flagableData** mainData);

struct Command
{
    const Mode       mode;
    Command_function function;
    const char*      name;
    const char*      short_name;
    const char*      describtion;
};

Status processMainArgs(const int argc, const char** argv, int* mode_field, flagableData* mainData);

Status setDefaultStreams(const int argc, const char** argv, int* arg_index, flagableData** mainData);
Status setOutputStream  (const int argc, const char** argv, int* arg_index, flagableData** mainData);
Status setInputStream   (const int argc, const char** argv, int* arg_index, flagableData** mainData);
Status printCommands    (const int argc, const char** argv, int* arg_index, flagableData** mainData);

bool isAllModesSet(const int mode_field, const int modes);
bool isAnyModesSet(const int mode_field, const int modes);
bool isModeSet(const int mode_field, const int mode);
bool isCommand(const char* str, const Command* command);

char* allocStringLiteral(const char string[]);

void freeAndClose(myStream* stream);

#endif //FLAGSANDFILES_H
