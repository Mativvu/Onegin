#include <string>
#include <stdio.h>

#include "Errors.h"
#include "FlagsAndFiles.h"
#include "Color.h"
#include "Debug.h"

//TODO: Add FILE structures
//TODO: Add file flags
//TODO: add commands

static Command Commands[] =
{
    {ModeHelp,   printCommands,     "--help",  "-h", "you already know, don`t you?)\n"},
    {ModeFile,   setDefaultStreams, "--file",  "-f", "default working mode, extracts data from \"input.txt\""
                                                     "and prints in \"output.txt\" \n"},
    {ModeInput,  setInputStream,    "--in",    "-i", "type \"filename\" after it to input from \"filename\" \n"},
    {ModeOutput, setOutputStream,   "--out",   "-o", "type \"filename\" after it to output in \"filename\" \n"},
};

//TODO: change insides

Status processMainArgs(const int argc, const char** argv, int* mode_field, flagableData* mainData)
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
        for (size_t command_index = 0; command_index < (sizeof(Commands)/sizeof(Commands[0])); command_index++)
        {
            if (isCommand(argv[arg_index], &Commands[command_index]))
            {
                if (isModeSet(*mode_field, Commands[command_index].mode))
                {
                    return DUPLICATION_ERR;
                }
                *mode_field |= Commands[command_index].mode;

                Commands[command_index].function(argc, argv, &arg_index, &mainData);
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

Status setInputStream(const int argc, const char** argv, int* arg_index, flagableData** mainData)
{
    myAssert(arg_index != nullptr);
    myAssert(mainData != nullptr);
    myAssert(*mainData != nullptr);

    FILE** stream_in = &(*mainData)->input_stream.stream;

    if (*stream_in != nullptr)
    {
        return STREAM_ERR;
    }

    if (*arg_index + 1 < argc)
    {
        (*arg_index)++;
        (*mainData)->input_stream.file_name = allocStringLiteral(argv[*arg_index]);
    }
    else
    {
        return FILE_ERR;
    }
    *stream_in = fopen((*mainData)->input_stream.file_name, "r");
    if (*stream_in == nullptr)
    {
        return FILE_ERR;
    }
    return OK;
}

Status setOutputStream(const int argc, const char** argv, int* arg_index, flagableData** mainData)
{
    myAssert(arg_index != nullptr);
    myAssert(mainData  != nullptr);
    myAssert(*mainData != nullptr);

    FILE** stream_out = &(*mainData)->output_stream.stream;

    if (*stream_out != nullptr)
    {
        return STREAM_ERR;
    }

    if (*arg_index + 1 < argc)
    {
        (*arg_index)++;
        (*mainData)->output_stream.file_name = allocStringLiteral(argv[*arg_index]);
    }
    else
    {
        return FILE_ERR;
    }
    *stream_out = fopen((*mainData)->output_stream.file_name, "w");
    if (*stream_out == nullptr)
    {
        return FILE_ERR;
    }
    return OK;
}

Status setDefaultStreams(const int argc, const char** argv, int* arg_index, flagableData** mainData)
{
    myAssert(mainData  != nullptr);
    myAssert(*mainData != nullptr);

    FILE** stream_in  = &(*mainData)->input_stream.stream;
    FILE** stream_out = &(*mainData)->output_stream.stream;

    if (*stream_in != nullptr || *stream_out != nullptr)
    {
        return STREAM_ERR;
    }

    (*mainData)->input_stream.file_name  = allocStringLiteral("output.txt");
    (*mainData)->output_stream.file_name = allocStringLiteral("input.txt");

    *stream_in  = fopen("input.txt", "r");
    *stream_out = fopen("output.txt", "w");
    if (*stream_in == nullptr || *stream_out == nullptr)
    {
        return FILE_ERR;
    }
    return OK;
}

Status printCommands(const int argc, const char** argv, int* arg_index, flagableData** mainData)
{
    printf("\n");
    for (size_t i = 0; i < (sizeof(Commands)/sizeof(Commands[0])); i++)
    {
        colorPrintf(CYAN, "%s ", Commands[i].name);
        colorPrintf(MAGENTA, "or ");
        colorPrintf(CYAN, "%s ", Commands[i].short_name);
        colorPrintf(MAGENTA, "%s\n", Commands[i].describtion);
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

char* allocStringLiteral(const char string[])
{
    char* dynamic_string = nullptr;

    size_t length = strlen(string) + 1;

    dynamic_string = (char*)calloc(length, sizeof(char));
    if (dynamic_string == nullptr)
    {
        return nullptr;
    }

    dynamic_string[--length] = '\0';
    while (--length >= 0)
    {
        dynamic_string[length] = string[length];
        if (length == 0)
        {
            break;
        }
    }
    return dynamic_string;
}

void freeAndClose(myStream* stream)
{
    free(stream->file_name);
    fclose(stream->stream);
}
