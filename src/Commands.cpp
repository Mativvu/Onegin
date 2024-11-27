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
    {INPUT,   setInputStream,    "--in",    "-i", "type \"filename\" after it to input from \"filename\","
                                                  "file must exist in folder \"files/input\" \n"},
    {OUTPUT,  setOutputStream,   "--out",   "-o", "type \"filename\" after it to output in \"filename\","
                                                  "file must exist in folder \"files/output\" \n"},
    {APPEND,  setAppendStream,   "--app",   "-a", "type \"filename\" after it to input from \"filename\""
                                                  " and output in the end of it, file must exist in"
                                                  "folder \"files/input\" \n"},
    {SORT,    setSortingMethod,  "--sort",  "-s", "type \"quick\" to sort strings using QuickSort algorithm"
                                                  " or \"heap\" to use HeapSort \n"}
};
size_t commands_array_size = sizeof(commands_array)/sizeof(commands_array[0]);

Sorter sorters_array[] =
{
    {quickSort, "quick"},
    {heapSort,  "heap"}
};

Status setSortingMethod (const int argc, const char** argv, int* arg_index, FlagParseData* ParsedData)
{
    myAssert(arg_index != nullptr);
    myAssert(ParsedData != nullptr);

    char algorithm_name[MAX_NAME_LEN] = "";
    if (*arg_index + 1 < argc)
    {
        (*arg_index)++;
        strncpy(algorithm_name, argv[*arg_index], MAX_NAME_LEN);
    }

    for (size_t index = 0; index < sizeof(sorters_array)/sizeof(sorters_array[0]); ++index)
    {
        if (strcmp(algorithm_name, sorters_array[index].name) == 0)
        {
            ParsedData->sorter = sorters_array[index].sorter;
        }
    }
    if (ParsedData->sorter == nullptr)
    {
        return ALGORITHM_ERR;
    }
    return OK;
}

Status setInputStream(const int argc, const char** argv, int* arg_index, FlagParseData* ParsedData)
{
    myAssert(arg_index != nullptr);
    myAssert(ParsedData != nullptr);

    if (ParsedData->input_stream != nullptr)
    {
        return STREAM_ERR;
    }

    const char* file_path;
    if (*arg_index + 1 < argc)
    {
        (*arg_index)++;
        file_path = argv[*arg_index];
    }
    else
    {
        return FILE_ERR;
    }
    ParsedData->input_stream = fopen(file_path, "r");
    if (ParsedData->input_stream == nullptr)
    {
        return FILE_ERR;
    }
    return OK;
}

Status setOutputStream(const int argc, const char** argv, int* arg_index, FlagParseData* ParsedData)
{
    myAssert(arg_index != nullptr);
    myAssert(ParsedData  != nullptr);

    if (ParsedData->output_stream != nullptr)
    {
        return STREAM_ERR;
    }

    const char* file_path;
    if (*arg_index + 1 < argc)
    {
        (*arg_index)++;
        file_path = argv[*arg_index];
    }
    else
    {
        return FILE_ERR;
    }
    ParsedData->output_stream = fopen(file_path, "w");
    if (ParsedData->output_stream == nullptr)
    {
        return FILE_ERR;
    }
    return OK;
}

Status setAppendStream(const int argc, const char** argv, int* arg_index, FlagParseData* ParsedData)
{
    myAssert(arg_index  != nullptr);
    myAssert(ParsedData != nullptr);

    if (ParsedData->input_stream != nullptr || ParsedData->output_stream != nullptr)
    {
        return STREAM_ERR;
    }

    const char* file_path;
    if (*arg_index + 1 < argc)
    {
        (*arg_index)++;
        file_path = argv[*arg_index];
    }
    else
    {
        return FILE_ERR;
    }
    ParsedData->output_stream = fopen(file_path, "a+");
    ParsedData->input_stream  = fopen(file_path, "a+");
    if (ParsedData->input_stream == nullptr || ParsedData->output_stream == nullptr)
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

    if (ParsedData->output_stream != nullptr || ParsedData->input_stream != nullptr)
    {
        return STREAM_ERR;
    }

    ParsedData->input_stream  = fopen(DEFAULT_INPUT_FILE_NAME,  "r");
    ParsedData->output_stream = fopen(DEFAULT_OUTPUT_FILE_NAME, "w");
    if (ParsedData->input_stream == nullptr || ParsedData->output_stream == nullptr)
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
        colorPrintf(MAGENTA, "%s\n", commands_array[i].description);
    }
    return HELP_FLAG;
}
