#include <stdio.h>
#include <time.h>

#include "Errors.h"
#include "Commands.h"
#include "FlagParser.h"
#include "StringSort.h"
#include "StoringData.h"
#include "Color.h"
#include "Debug.h"

//NOTE: Color.h: leave only defines or constants, maybe enum?
//NOTE: Commands.cpp: rework createFilePath: add error type?
//NOTE: rename error names, make`em longer
//NOTE: print at the end of the input file?
//NOTE: delete irrelevant functions from sort header
//NOTE: Change isalpha() in comparators?
//NOTE: Catch errors in sort functions?
//NOTE: Change tolower() in comparators?

int main(const int argc, const char** argv)
{
    int modes_bitset = 0;
    Status status    = OK;

    FlagParseData ParsedData = {};
    status = parseFlags(argc, argv, &modes_bitset, &ParsedData);
    checkStatus(status);
    debugPrintString("#1 Initialization completed, files opened successfully \n");

    FILE* stream_in  = ParsedData.input_stream.stream;
    FILE* stream_out = ParsedData.output_stream.stream;

    CharArray File_text = {};
    status = readDataFromFile(stream_in, &File_text);
    checkStatus(status);
    debugPrintString("#2 File reading finished \n");

    colorPrintf(YELLOW, "Data array size is %zu symbols \n", File_text.size);

    SmartArray String_array = {};
    status = linkStringPointers(&File_text, &String_array);
    checkStatus(status);
    debugPrintString("#3 Pointers linked successfully \n");

    colorPrintf(YELLOW, "String array size is %zu lines \n", String_array.size);

    //clock_t start = clock();
    //FILE* stream_graph = fopen("files/output/data.txt", "a");

    status = sortArray(ParsedData.sorter, &String_array, lexicographicStringComparator);
    checkStatus(status);
    debugPrintString("#4 Lexicographic sorting finished \n");

    //clock_t finish = clock();
    //double sorting_time = (double)(finish - start) / CLOCKS_PER_SEC;
    //fprintf(stream_graph, "%zu \t %lg \n", String_array.size, sorting_time);
    //colorPrintf(YELLOW, "Time sorting: %lg \n", sorting_time);

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
