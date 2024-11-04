#include <stdio.h>

#include "Errors.h"
#include "Commands.h"
#include "FlagParser.h"
#include "StringSort.h"
#include "StoringData.h"
#include "Color.h"
#include "Debug.h"

//TODO: rename structures
//TODO: rename ParsedData
//TODO: rename error names, make`em longer
//TODO: add commands
//TODO: print at the end of the input file?

int main(const int argc, const char** argv)
{
    int modes_bitset = 0;
    Status status  = OK;

    FlagParseData ParsedData = {nullptr, {nullptr, nullptr}, {nullptr, nullptr}};
    status = parseFlags(argc, argv, &modes_bitset, &ParsedData);
    checkStatus(status);
    debugPrintString("#1 Initialization completed, files opened successfully \n");

    FILE* stream_in  = ParsedData.input_stream.stream;
    FILE* stream_out = ParsedData.output_stream.stream;

    CharArray File_text = {nullptr, 0};
    status = readDataFromFile(stream_in, &File_text);
    checkStatus(status);
    debugPrintString("#2 File reading finished \n");

    colorPrintf(YELLOW, "Data array size is %zu symbols \n", File_text.size);

    SmartArray String_array = {nullptr, 0};
    status = linkStringPointers(&File_text, &String_array);
    checkStatus(status);
    debugPrintString("#3 Pointers linked successfully \n");

    colorPrintf(YELLOW, "String array size is %zu lines \n", String_array.size);

    status = sortArray(ParsedData.sorter, &String_array, lexicograficStringComparator);
    checkStatus(status);
    debugPrintString("#4 Lexicografic sorting finished \n");

    status = printStringArray(stream_out, &String_array);
    checkStatus(status);
    debugPrintString("#5 Finished printing array \n");

    status = sortArray(ParsedData.sorter, &String_array, rhymeStringComparator);
    checkStatus(status);
    debugPrintString("#6 Rhyme sorting finished \n");

    status = printStringArray(stream_out, &String_array);
    checkStatus(status);
    debugPrintString("#7 Finished printing array \n");

    freeCharArray (&File_text);
    freeSmartArray(&String_array);
    freeAndCloseStream(&ParsedData.input_stream);
    freeAndCloseStream(&ParsedData.output_stream);
    debugPrintString("#8 Memory cleared, files closed, all done \n");
}
