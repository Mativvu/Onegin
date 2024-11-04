#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "StringSort.h"
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
    {SORT,    setSortingMethod,  "--sort",  "-s", "type \"quick\" to sort strings using QuickSort algorithm"
                                                  " or \"heap\" to use HeapSort \n"}
};
size_t commands_array_size = sizeof(commands_array)/sizeof(commands_array[0]);

Status setSortingMethod (const int argc, const char** argv, int* arg_index, FlagParseData* ParsedData)
{
    myAssert(arg_index != nullptr);
    myAssert(ParsedData != nullptr);

    char algorithm_name[MAX_ALGO_NAME] = {0};
    if (*arg_index + 1 < argc)
    {
        (*arg_index)++;
        strncpy(algorithm_name, argv[*arg_index], MAX_ALGO_NAME);
    }

    if (strcmp(algorithm_name, "quick") == 0)
    {
        ParsedData->sorter = quickSort;
    }
    else if (strcmp(algorithm_name, "heap") == 0)
    {
        ParsedData->sorter = heapSort;
    }
    else
    {
        return ALGORITHM_ERR;
    }
    return OK;
}

Status setInputStream(const int argc, const char** argv, int* arg_index, FlagParseData* ParsedData)
{
    myAssert(arg_index != nullptr);
    myAssert(ParsedData != nullptr);

    FILE** stream_in = &ParsedData->input_stream.stream;

    if (*stream_in != nullptr)
    {
        return STREAM_ERR;
    }

    if (*arg_index + 1 < argc)
    {
        (*arg_index)++;
        ParsedData->input_stream.file_name = allocStringLiteral(argv[*arg_index]);
    }
    else
    {
        return FILE_ERR;
    }
    *stream_in = fopen(ParsedData->input_stream.file_name, "r");
    if (*stream_in == nullptr)
    {
        return FILE_ERR;
    }
    return OK;
}

Status setOutputStream(const int argc, const char** argv, int* arg_index, FlagParseData* ParsedData)
{
    myAssert(arg_index != nullptr);
    myAssert(ParsedData  != nullptr);

    FILE** stream_out = &ParsedData->output_stream.stream;

    if (*stream_out != nullptr)
    {
        return STREAM_ERR;
    }

    if (*arg_index + 1 < argc)
    {
        (*arg_index)++;
        ParsedData->output_stream.file_name = allocStringLiteral(argv[*arg_index]);
    }
    else
    {
        return FILE_ERR;
    }
    *stream_out = fopen(ParsedData->output_stream.file_name, "w");
    if (*stream_out == nullptr)
    {
        return FILE_ERR;
    }
    return OK;
}

Status setDefaultStreams(const int argc, const char** argv, int* arg_index, FlagParseData* ParsedData)
{
    unused(argc);
    unused(argv);
    unused(arg_index);
    myAssert(ParsedData  != nullptr);

    FILE** stream_in  = &ParsedData->input_stream.stream;
    FILE** stream_out = &ParsedData->output_stream.stream;

    if (*stream_in != nullptr || *stream_out != nullptr)
    {
        return STREAM_ERR;
    }

    ParsedData->input_stream.file_name  = allocStringLiteral("output.txt");
    ParsedData->output_stream.file_name = allocStringLiteral("input.txt");

    *stream_in  = fopen("input.txt", "r");
    *stream_out = fopen("output.txt", "w");
    if (*stream_in == nullptr || *stream_out == nullptr)
    {
        return FILE_ERR;
    }
    return OK;
}

Status printCommands(const int argc, const char** argv, int* arg_index, FlagParseData* ParsedData)
{
    unused(argc);
    unused(argv);
    unused(arg_index);
    unused(ParsedData);

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

void freeAndCloseStream(MyStream* stream)
{
    free(stream->file_name);
    fclose(stream->stream);
}
