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

enum  Status
{
    OK              = 0,
    HELP_FLAG       = 1,
    UNKNOWN_ARG     = 2,
    FILE_ERR        = 3,
    DUPLICATION_ERR = 4,
    ALLOC_ERR       = 5,
    SEEK_ERR        = 6,
    READ_ERR        = 7,
    STREAM_ERR      = 8,
    ALGORITHM_ERR   = 9,
    NAME_LEN_ERR    = 10
};

bool isError(Status status);
void describeError(Status status);

#endif //ERRORCODES_H
