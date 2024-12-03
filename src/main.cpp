#include <stdio.h>
#include <time.h>

#include "Errors.h"
#include "Commands.h"
#include "FlagParser.h"
#include "StringSort.h"
#include "StoringData.h"
#include "Color.h"
#include "Debug.h"

int main(const int argc, const char** argv)
{
    int modes_bitset = 0;
    Status status    = OK;

    FlagParseData ParsedData = {};
    status = parseFlags(argc, argv, &modes_bitset, &ParsedData, commands_array, commands_array_size);
    checkStatus(status);
    debugPrintString("#1 Initialization completed, files opened successfully \n");

    FILE* stream_in  = ParsedData.input_stream;
    FILE* stream_out = ParsedData.output_stream;

    MyString File_text = {};
    status = readDataFromFile(stream_in, &File_text);
    checkStatus(status);
    debugPrintString("#2 File reading finished \n");

    MyArray String_array = {};
    status = linkStringPointers(&File_text, &String_array);
    checkStatus(status);
    debugPrintString("#3 Pointers linked successfully \n");

    status = sortArray(ParsedData.sorter, &String_array, lexicographicStringComparator);
    checkStatus(status);
    debugPrintString("#4 Lexicographic sorting finished \n");

    status = printStringArray(stream_out, &String_array);
    checkStatus(status);
    debugPrintString("#5 Finished printing array \n");

    status = sortArray(ParsedData.sorter, &String_array, rhymeStringComparator);
    checkStatus(status);
    debugPrintString("#6 Rhyme sorting finished \n");

    status = printStringArray(stream_out, &String_array);
    checkStatus(status);
    debugPrintString("#7 Finished printing array \n");

    freeMyString(&File_text);
    freeMyArray (&String_array);
    fclose(ParsedData.input_stream);
    fclose(ParsedData.output_stream);
    debugPrintString("#8 Memory cleared, files closed, all done \n");
}
