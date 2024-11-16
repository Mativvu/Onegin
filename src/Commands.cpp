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

Status setSortingMethod (const int argc, const char** argv, int* arg_index, FlagParseData* ParsedData)
{
    myAssert(arg_index != nullptr);
    myAssert(ParsedData != nullptr);

    char algorithm_name[MAX_NAME_LEN] = {0};
    if (*arg_index + 1 < argc)
    {
        (*arg_index)++;
        strncpy(algorithm_name, argv[*arg_index], MAX_NAME_LEN);
    }
    //FIXME
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

    Status status = OK;

    FILE** stream_in = &ParsedData->input_stream.stream;
    char** file_path = &ParsedData->input_stream.file_path;

    if (*stream_in != nullptr)
    {
        return STREAM_ERR;
    }

    if (*arg_index + 1 < argc)
    {
        (*arg_index)++;
        const char* file_name = argv[*arg_index];

        createFilePath(file_path, FILE_INPUT_PATH, file_name);
        returnIfError(status);
    }
    else
    {
        return FILE_ERR;
    }
    *stream_in = fopen(*file_path, "r");
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

    Status status = OK;

    FILE** stream_out = &ParsedData->output_stream.stream;
    char** file_path  = &ParsedData->output_stream.file_path;

    if (*stream_out != nullptr)
    {
        return STREAM_ERR;
    }

    if (*arg_index + 1 < argc)
    {
        (*arg_index)++;
        const char* file_name = argv[*arg_index];

        status = createFilePath(file_path, FILE_OUTPUT_PATH, file_name);
        returnIfError(status);
    }
    else
    {
        return FILE_ERR;
    }
    *stream_out = fopen(*file_path, "w");
    if (*stream_out == nullptr)
    {
        return FILE_ERR;
    }
    return OK;
}

Status setAppendStream(const int argc, const char** argv, int* arg_index, FlagParseData* ParsedData)
{
    myAssert(arg_index != nullptr);
    myAssert(ParsedData  != nullptr);

    Status status = OK;

    FILE** stream_in =  &ParsedData->input_stream.stream;
    FILE** stream_out = &ParsedData->output_stream.stream;

    char** file_path   = &ParsedData->input_stream.file_path;

    if (*stream_out != nullptr || *stream_in != nullptr)
    {
        return STREAM_ERR;
    }

    if (*arg_index + 1 < argc)
    {
        (*arg_index)++;
        const char* file_name = argv[*arg_index];

        status = createFilePath(file_path, FILE_INPUT_PATH, file_name);
        returnIfError(status);
    }
    else
    {
        return FILE_ERR;
    }
    *stream_in  = fopen(*file_path, "a+");
    *stream_out = fopen(*file_path, "a+");
    if (*stream_out == nullptr || *stream_in == nullptr)
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

    Status status = OK;

    FILE** stream_in  = &ParsedData->input_stream.stream;
    FILE** stream_out = &ParsedData->output_stream.stream;

    char** file_in_path   = &ParsedData->input_stream.file_path;
    char** file_out_path  = &ParsedData->output_stream.file_path;

    if (*stream_in != nullptr || *stream_out != nullptr)
    {
        return STREAM_ERR;
    }

    status = createFilePath(file_in_path,  FILE_INPUT_PATH,  DEFAULT_INPUT_FILE_NAME);
    returnIfError(status);
    status = createFilePath(file_out_path, FILE_OUTPUT_PATH, DEFAULT_OUTPUT_FILE_NAME);
    returnIfError(status);

    *stream_in  = fopen(*file_in_path, "r");
    *stream_out = fopen(*file_out_path, "w");
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
        colorPrintf(MAGENTA, "%s\n", commands_array[i].description);
    }
    return HELP_FLAG;
}

Status createFilePath(char** file_path, const char* path, const char* file_name)
{
    myAssert(file_path != nullptr);
    myAssert(file_name != nullptr);
    myAssert(path != nullptr);

    long path_length = snprintf(NULL, 0, "%s%s", path, file_name) + 1;
    if (path_length <= 0 || (size_t)path_length >= MAX_NAME_LEN * 2)
    {
        return NAME_LEN_ERR;
    }

    *file_path = (char*)calloc(MAX_NAME_LEN * 2, sizeof(char));
    if (*file_path == nullptr)
    {
        return ALLOC_ERR;
    }
    long res = snprintf(*file_path, (size_t)path_length, "%s%s", path, file_name) + 1;
    if (res != path_length)
    {
        return NAME_LEN_ERR;
    }
    return OK;
}

void freeAndCloseStream(MyStream* stream)
{
    free(stream->file_path);
    fclose(stream->stream);
}
