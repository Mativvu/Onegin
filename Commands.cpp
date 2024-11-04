#include <stdio.h>

#include "Commands.h"
#include "Color.h"
#include "Debug.h"

Command commands_array[] =
{
    {HELP,    printCommands,     "--help",  "-h", "you already know, don`t you?)\n"},
    {DEFAULT, setDefaultStreams, "--file",  "-f", "default working mode, extracts data from \"input.txt\""
                                                  "and prints in \"output.txt\" \n"},
    {INPUT,   setInputStream,    "--in",    "-i", "type \"filename\" after it to input from \"filename\" \n"},
    {OUTPUT,  setOutputStream,   "--out",   "-o", "type \"filename\" after it to output in \"filename\" \n"},
};
size_t commands_array_size = sizeof(commands_array)/sizeof(commands_array[0]);

Status setInputStream(const int argc, const char** argv, int* arg_index, FlagableData** mainData)
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

Status setOutputStream(const int argc, const char** argv, int* arg_index, FlagableData** mainData)
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

Status setDefaultStreams(const int argc, const char** argv, int* arg_index, FlagableData** mainData)
{
    unused(argc);
    unused(argv);
    unused(arg_index);
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

Status printCommands(const int argc, const char** argv, int* arg_index, FlagableData** mainData)
{
    unused(argc);
    unused(argv);
    unused(arg_index);
    unused(mainData);
    
    printf("\n");
    for (size_t i = 0; i < commands_array_size; i++)
    {
        colorPrintf(CYAN, "%s ", commands_array[i].name);
        colorPrintf(MAGENTA, "or ");
        colorPrintf(CYAN, "%s ", commands_array[i].short_name);
        colorPrintf(MAGENTA, "%s\n", commands_array[i].describtion);
    }
    return OK;
}
