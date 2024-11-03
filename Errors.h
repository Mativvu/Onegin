#ifndef ERRORCODES_H
#define ERRORCODES_H

#define checkStatus(status) \
if (isError(status))        \
{                           \
    describeError(status);  \
    return status;          \
};

//TODO: delete irrelevant flags

enum Status {
    OK              = 0,  /**< Function finished without errors. */
    INPUT_ERR       = 1,  /**< The input was wrong. */
    COEFF_ERR       = 2,  /**< Coefficient was invalid number. */
    SOLVER_ERR      = 3,  /**< Error in SolveQuadEquation function. */
    OUTPUT_ERR      = 4,  /**< Trying to print invalid solutions. */
    END_TEST        = 5,  /**< Unit testing finished. */
    MAXLEN_REACHED  = 6,  /**< Too many characters in one line. */
    UNKNOWN_ARG     = 7,  /**< Found unknown argument. */
    COMMAND_ERR     = 8,  /**< Forbidden combination of flags was typed. */
    FILE_ERR        = 9,  /**< Cannot open/find file. */
    DUPLICATION_ERR = 10, /**< Identical flags were typed. */
    HELP_FLAG       = 11, /**< "--help" command was typed, stops program. */
    ALLOC_ERR       = 12,
    SEEK_ERR        = 13,
    READ_ERR        = 14
};

bool isError(Status status);
void describeError(Status status);

#endif //ERRORCODES_H
