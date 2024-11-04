#ifndef ERRORCODES_H
#define ERRORCODES_H

#define checkStatus(status)     \
    if (isError(status))        \
    {                           \
        describeError(status);  \
        return status;          \
    };

#define returnIfError(status)     \
    if (isError(status))          \
    {                             \
        return status;            \
    };

//TODO: delete irrelevant flags

enum Status
{
    OK              = 0, /*< Function finished without errors. */
    HELP_FLAG       = 1, /*< "--help" command was typed, stops program. */
    UNKNOWN_ARG     = 2, /*< Found unknown argument. */
    FILE_ERR        = 3, /*< Cannot open/find file. */
    DUPLICATION_ERR = 4, /*< Identical flags were typed. */
    ALLOC_ERR       = 5, /*< Failed allocating memory. */
    SEEK_ERR        = 6, /*< Cannot find end of file. */
    READ_ERR        = 7, /*< Cannot read all data from file. */
    STREAM_ERR      = 8, /*< Repeated opening of the same stream. */
    ALGORITHM_ERR   = 9  /*< Sorting method is unknown or wasn`t inputted. */
};

bool isError(Status status);
void describeError(Status status);

#endif //ERRORCODES_H
