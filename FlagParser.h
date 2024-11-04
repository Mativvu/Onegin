#ifndef FLAGPARSER_H
#define FLAGPARSER_H

#include "Errors.h"
#include "Commands.h"
#include "Files.h"

Status processMainArgs(const int argc, const char** argv, int* mode_field, FlagableData* mainData);

bool isAllModesSet(const int mode_field, const int modes);
bool isAnyModesSet(const int mode_field, const int modes);
bool isModeSet    (const int mode_field, const int mode);
bool isCommand    (const char* str, const Command* command);

#endif //FLAGPARSER_H
