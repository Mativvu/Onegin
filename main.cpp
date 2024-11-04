#include <stdio.h>

#include "Errors.h"
#include "FlagsAndFiles.h"
#include "StringSort.h"
#include "StoringData.h"
#include "Color.h"
#include "Debug.h"

//TODO: add commands
//TODO: print at the end of the input file?

int main(const int argc, const char** argv)
{
    int mode_field = 0;

    FlagableData mainData = {{nullptr, nullptr}, {nullptr, nullptr}};
    Status status = processMainArgs(argc, argv, &mode_field, &mainData);
    checkStatus(status);
    debugPrintStr("#1 Initialization completed, files opened successfully \n");

    FILE* stream_in =  mainData.input_stream.stream;
    FILE* stream_out = mainData.output_stream.stream;

    CharArray file_text = {nullptr, 0};
    status = readDataFromFile(stream_in, &file_text);
    checkStatus(status);
    debugPrintStr("#2 File reading finished \n");

    colorPrintf(YELLOW, "Data array size is %zu symbols \n", file_text.size);

    SmartArray string_array = {nullptr, 0};
    status = linkStringPointers(&file_text, &string_array);
    checkStatus(status);
    debugPrintStr("#3 Pointers linked successfully \n");

    colorPrintf(YELLOW, "String array size is %zu lines \n", string_array.size);

    status = heapSort(string_array, lexicograficStringComparator);
    checkStatus(status);
    debugPrintStr("#4 Lexicografic sorting finished \n");

    status = printStringArray(stream_out, string_array);
    checkStatus(status);
    debugPrintStr("#5 Finished printing array \n");

    status = heapSort(string_array, rhymeStringComparator);
    checkStatus(status);
    debugPrintStr("#6 Rhyme sorting finished \n");

    status = printStringArray(stream_out, string_array);
    checkStatus(status);
    debugPrintStr("#7 Finished printing array \n");

    freeSmartArray(&string_array);
    freeCharArray (&file_text);
    freeAndClose(&mainData.input_stream);
    freeAndClose(&mainData.output_stream);
    debugPrintStr("#8 Memory cleared, files closed, all done \n");
}
