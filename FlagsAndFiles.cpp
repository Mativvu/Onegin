#include <string>
#include <stdio.h>

#include "Errors.h"
#include "FlagsAndFiles.h"
#include "Color.h"
#include "Debug.h"

//TODO: Add file flags
//TODO: add commands

static Command Commands[] = {
    {ModeHelp,   "--help",  "-h", "you already know, don`t you?)\n"},
    {ModeInput,  "--in",    "-i", "type \"filename\" after it to input from filename\n"},
    {ModeOutput, "--out",   "-o", "type \"filename\" after it to output to filename\n"}
};

//TODO: change insides

Status processMainArgs(const int argc, const char* argv[], int* mode_field,
                       const char** stream_in_name, const char** stream_out_name)
{
    myAssert(mode_field != nullptr);
    myAssert(stream_in_name != nullptr);
    myAssert(stream_out_name != nullptr);

    for (int i = 1; i < argc; i++)
    {
        bool found = false;
        for (size_t j = 0; j < (sizeof(Commands)/sizeof(Commands[0])); j++)
        {
            if (isCommand(argv[i], &Commands[j]))
            {
                if (isModeSet(*mode_field, Commands[j].mode))
                {
                    return DUPLICATION_ERR;
                }
                *mode_field |= Commands[j].mode;

                /* Simple solution to process commands "--in" and "--out".
                if (isCommand(argv[i], &Commands[FLAG_IN_INDEX])
                    && i+1 < argc)
                {
                    *stream_in_name = argv[++i];
                }
                else if (isCommand(argv[i], &Commands[FLAG_OUT_INDEX])
                         && i+1 < argc)
                {
                    *stream_out_name = argv[++i];
                }
                */
                found = true;
                break;
            }
        }
        if (!found)
        {
            colorPrintf(MAGENTA, "Found unknown argument: %s\n", argv[i]);
            return UNKNOWN_ARG;
        }
    }
    return OK;
}

//TODO: change function
Status fileManager(int mode_field, FILE** stream_in_ptr, FILE** stream_out_ptr,
                   const char* stream_in_name, const char* stream_out_name)
{
    myAssert(stream_in_ptr != nullptr);
    myAssert(stream_out_ptr != nullptr);

    /*
    if (   isAllModesSet(mode_field, (ModeFile | ModeOutput))
        || isAllModesSet(mode_field, (ModeFile | ModeInput)))
    {
        return COMMAND_ERR;
    }
    if (isModeSet(mode_field, ModeFile))
    {
        *stream_in_ptr  = fopen("input.txt",  "r");
        *stream_out_ptr = fopen("output.txt", "w");
        if (*stream_in_ptr == nullptr || *stream_out_ptr == nullptr)
        {
            return FILE_ERR;
        }
    }
    */
    if (stream_in_name != nullptr)
    {
        *stream_in_ptr = fopen(stream_in_name, "r");
        if (*stream_in_ptr == nullptr)
        {
            return FILE_ERR;
        }
    }
    if (stream_out_name != nullptr)
    {
        *stream_out_ptr = fopen(stream_out_name, "w");
        if (*stream_out_ptr == nullptr)
        {
            return FILE_ERR;
        }
    }
    return OK;
}

bool isAllModesSet(const int mode_field, const int modes)
{
    return ((mode_field & modes) == modes);
}

bool isAnyModesSet(const int mode_field, const int modes)
{
    return (mode_field & modes);
}

bool isModeSet(const int mode_field, const int mode)
{
    return (mode_field & mode);
}

bool isCommand(const char* str, const Command* command)
{
    return (strcmp(str, command->name)       == 0 ||
            strcmp(str, command->short_name) == 0);
}

void printCommands()
{
    printf("\n");
    for (size_t i = 0; i < (sizeof(Commands)/sizeof(Commands[0])); i++)
    {
        colorPrintf(CYAN, "%s ", Commands[i].name);
        colorPrintf(MAGENTA, "or ");
        colorPrintf(CYAN, "%s ", Commands[i].short_name);
        colorPrintf(MAGENTA, "%s\n", Commands[i].describtion);
    }
}

Status performPrintingCommands(const int mode_field)
{
    if (isModeSet(mode_field, ModeHelp))
    {
        printCommands();
        return HELP_FLAG;
    }
    else
    {
        colorPrintf(MAGENTA, "Type --help to see commands\n");
    }
    return OK;
}

