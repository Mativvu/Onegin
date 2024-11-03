#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "StringSort.h"
#include "StoringData.h"
#include "Color.h"
#include "Errors.h"
#include "Debug.h"

//TODO: Change isalpha() in comparators?
//TODO: Catch errors in sort functions?
//TODO: Change tolower() in comparators?

//static const char skip_symbols[] = {' ', '!', '?', '.', ',', '"', '\'', '-', '`'};

Status heapSort(smartString* array, const size_t size, Compare_func comparator)
{
    for (size_t index = (size-1)/2; index >= 0; --index)
    {
        heapPushDown(array, size, index, comparator);
        //simple solution to "size_t >= 0"
        if (index == 0) break;
    }
    for (size_t index = size-1; index > 0; --index)
    {
        swapStrings(&array[0], &array[index]);
        heapPushDown(array, index, 0, comparator);
        //simple solution to "size_t >= 0"
        if (index == 0) break;
    }
    return OK;
}

void heapPushDown(smartString* array, const size_t size, size_t index, Compare_func comparator)
{
    size_t minimal_index = index;
    size_t left_index = 2*index + 1;
    size_t right_index = 2*index + 2;
    if (left_index < size && comparator(&array[left_index], &array[minimal_index]) > 0)
    {
        minimal_index = left_index;
    }
    if (right_index < size && comparator(&array[right_index], &array[minimal_index]) > 0)
    {
        minimal_index = right_index;
    }
    if (index != minimal_index)
    {
        swapStrings(&array[index], &array[minimal_index]);
        heapPushDown(array, size, minimal_index, comparator);
    }
    return;
}

void swapStrings(smartString* str_1, smartString* str_2)
{
    char* temp_str = str_1->string;
    str_1->string = str_2->string;
    str_2->string = temp_str;

    int temp_len = str_1->length;
    str_1->length = str_2->length;
    str_2->length = temp_len;
}

int lexicograficStringComparator(const void* elem_1, const void* elem_2)
{
    char* str_1 = ((const smartString*)elem_1)->string;
    char* str_2 = ((const smartString*)elem_2)->string;

    int len_1 = ((const smartString*)elem_1)->length - 1;
    int len_2 = ((const smartString*)elem_2)->length - 1;

    int offset_1 = 0;
    int offset_2 = 0;
    char ch_1 = ' ';
    char ch_2 = ' ';
    while (offset_1 < len_1 && offset_2 < len_2)
    {
        ch_1 = str_1[offset_1];
        ch_2 = str_2[offset_2];
        if (isalpha(ch_1) && isalpha(ch_2))
        {
            if (tolower(ch_1) != tolower(ch_2))
            {
                break;
            }
            offset_1++;
            offset_2++;
        }
        if (!isalpha(ch_1))
        {
            offset_1++;
        }
        if (!isalpha(ch_2))
        {
            offset_2++;
        }
    }
    return (tolower(str_1[offset_1]) - tolower(str_2[offset_2]));
}

int rhymeStringComparator(const void* elem_1, const void* elem_2)
{
    char* str_1 = ((const smartString*)elem_1)->string;
    char* str_2 = ((const smartString*)elem_2)->string;

    int len_1 = ((const smartString*)elem_1)->length - 1;
    int len_2 = ((const smartString*)elem_2)->length - 1;

    char ch_1 = ' ';
    char ch_2 = ' ';
    while (len_1 > 0 && len_2 > 0)
    {
        ch_1 = str_1[len_1];
        ch_2 = str_2[len_2];
        if (isalpha(ch_1) && isalpha(ch_2))
        {
            if (tolower(ch_1) != tolower(ch_2))
            {
                break;
            }
            len_1--;
            len_2--;
        }
        if (!isalpha(ch_1))
        {
            len_1--;
        }
        if (!isalpha(ch_2))
        {
            len_2--;
        }
    }
    return (tolower(str_1[len_1]) - tolower(str_2[len_2]));
}



