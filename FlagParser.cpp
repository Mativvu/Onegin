#include <string>

#include "FlagParser.h"
#include "Commands.h"
#include "Color.h"
#include "Debug.h"

Status processMainArgs(const int argc, const char** argv, int* mode_field, FlagableData* mainData)
{
    myAssert(mode_field != nullptr);
    myAssert(mainData != nullptr);

    if (argc == 1)
    {
        colorPrintf(MAGENTA, "Type --help to see commands\n");
    }
    for (int arg_index = 1; arg_index < argc; arg_index++)
    {
        bool found = false;
        for (size_t command_index = 0; command_index < commands_array_size; command_index++)
        {
            if (isCommand(argv[arg_index], &commands_array[command_index]))
            {
                if (isModeSet(*mode_field, commands_array[command_index].mode))
                {
                    return DUPLICATION_ERR;
                }
                *mode_field |= commands_array[command_index].mode;

                commands_array[command_index].function(argc, argv, &arg_index, &mainData);
                found = true;
                break;
            }
        }
        if (!found)
        {
            colorPrintf(MAGENTA, "Found unknown argument: %s\n", argv[arg_index]);
            return UNKNOWN_ARG;
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
