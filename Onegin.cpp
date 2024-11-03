#include <stdio.h>

#include "Errors.h"
#include "FlagsAndFiles.h"
#include "StringSort.h"
#include "StoringData.h"
#include "Color.h"
#include "Debug.h"

int main(const int argc, const char* argv[])
{
    int mode_field = 0;

    const char* fin_name = "input.txt";
    const char* fout_name = "output.txt";
    Status status = processMainArgs(argc, argv, &mode_field, &fin_name, &fout_name);
    checkStatus(status);

    status = performPrintingCommands(mode_field);
    checkStatus(status);

    FILE* fin  = nullptr;
    FILE* fout = nullptr;
    status = fileManager(mode_field, &fin, &fout, fin_name, fout_name);
    checkStatus(status);
    debugPrintStr("#1 Initialization completed, files opened successfully \n");

    size_t data_arr_size = 0;
    char* data_array = nullptr;

    status = readDataFromFile(fin, &data_array, &data_arr_size);
    checkStatus(status);
    debugPrintStr("#2 File reading finished \n");

    colorPrintf(YELLOW, "Data array size is %zu symbols \n", data_arr_size);

    size_t string_arr_size = 0;
    smartString* string_array = nullptr;

    status = linkTheFuckingPointers(fin, &data_array,    data_arr_size,
                                         &string_array, &string_arr_size);
    checkStatus(status);
    debugPrintStr("#3 Pointers linked successfully \n");

    colorPrintf(YELLOW, "String array size is %zu lines \n", string_arr_size);

    status = heapSort(string_array, string_arr_size, lexicograficStringComparator);
    checkStatus(status);
    debugPrintStr("#4 Lexicografic sorting finished \n");

    status = printStringArray(fout, string_array, string_arr_size);
    checkStatus(status);
    debugPrintStr("#5 Finished printing array \n");

    status = heapSort(string_array, string_arr_size, rhymeStringComparator);
    checkStatus(status);
    debugPrintStr("#6 Rhyme sorting finished \n");

    status = printStringArray(fout, string_array, string_arr_size);
    checkStatus(status);
    debugPrintStr("#7 Finished printing array \n");

    free(string_array);
    free(data_array);
    fclose(fin);
    fclose(fout);
    debugPrintStr("#8 Memory cleared, files closed, all done \n");
}
