#include <stdio.h>

#include "Errors.h"
#include "Color.h"

#define printIfMatch(status, code, text)               \
    if (status == code) printf(_RED text _RESET, code);

bool isError(Status status)
{
    return (status != OK);
}

void describeError(Status status)
{
    printIfMatch(status, OK,              "Err %d: "
                                          "Function DescribeError() called with OK status. \n");
    printIfMatch(status, HELP_FLAG,       "Err %d: "
                                          "Flag \"--help\" was inputted, program ended. \n");
    printIfMatch(status, UNKNOWN_ARG,     "Err %d: "
                                          "Error, found unknown command. \n");
    printIfMatch(status, FILE_ERR,        "Err %d: "
                                          "Error, cannot find/open file. \n");
    printIfMatch(status, DUPLICATION_ERR, "Err %d: "
                                          "Error, command duplication is forbidden. \n");
    printIfMatch(status, ALLOC_ERR,       "Err %d: "
                                          "Error, cannot allocate memory. \n");
    printIfMatch(status, SEEK_ERR,        "Err %d: "
                                          "Error, cannot find size of the file. \n");
    printIfMatch(status, READ_ERR,        "Err %d: "
                                          "Error, fail to read all data from file. \n");
    printIfMatch(status, STREAM_ERR,      "Err %d: "
                                          "Error, repeated opening of the same stream. \n");
    printIfMatch(status, ALGORITHM_ERR,   "Err %d: "
                                          "Error, name of the method is unknown or wasn`t inputted. \n");
    printIfMatch(status, NAME_LEN_ERR,    "Err %d: "
                                          "Error, file/algorithm name is too long. \n");
    colorPrintf(RED, "Error, unknown status. \n");
}
