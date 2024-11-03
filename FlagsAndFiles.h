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

struct Command {
    Mode mode;
    const char* name;
    const char* short_name;
    const char* describtion;
};

Status processMainArgs(const int argc, const char* argv[], int* mode_field,
                       const char** stream_in_name, const char** stream_out_name);

Status fileManager(int mode_field, FILE** stream_in_p, FILE** stream_out_p,
                   const char* stream_in_name, const char* stream_out_name);

Status performPrintingCommands(const int mode_field);
void   printCommands();

bool isAllModesSet(const int mode_field, const int modes);
bool isAnyModesSet(const int mode_field, const int modes);
bool isModeSet(const int mode_field, const int mode);
bool isCommand(const char* str, const Command* command);


#endif //FLAGSANDFILES_H
