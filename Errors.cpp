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
    printIfMatch(status, INPUT_ERR,       "Err %d: "
                                          "Wrong input, try again. \n");
    printIfMatch(status, COEFF_ERR,       "Err %d: "
                                          "Coefficients are not valid, enter again. \n");
    printIfMatch(status, SOLVER_ERR,      "Err %d: "
                                          "Wrong input, try again. \n");
    printIfMatch(status, OUTPUT_ERR,      "Err %d: "
                                          "Number of roots is not valid. \n");
    printIfMatch(status, END_TEST,        "Err %d: "
                                          "Testing finished. \n");
    printIfMatch(status, MAXLEN_REACHED,  "Err %d: "
                                          "Error, input line too long. \n");
    printIfMatch(status, UNKNOWN_ARG,     "Err %d: "
                                          "Error, found unknown command. \n");
    printIfMatch(status, COMMAND_ERR,     "Err %d: "
                                          "Error, cannot use --file and --input or --output together. \n");
    printIfMatch(status, FILE_ERR,        "Err %d: "
                                          "Error, cannot find/open file. \n");
    printIfMatch(status, DUPLICATION_ERR, "Err %d: "
                                          "Error, command duplication is forbidden. \n");
    printIfMatch(status, HELP_FLAG,       "Err %d: "
                                          "Flag \"--help\" was inputted. \n");
    printIfMatch(status, ALLOC_ERR,       "Err %d: "
                                          "Fail when allocating memory. \n");
    printIfMatch(status, OK,              "Err %d: "
                                          "Function DescribeError() called with OK status. \n");
    colorPrintf(RED, "Error, unknown status. \n");
}
