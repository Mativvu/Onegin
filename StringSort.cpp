#include <string.h>
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

Status heapSort(SmartArray array, Compare_func comparator)
{
    size_t data_size = array.size;
    for (size_t index = (data_size - 1) / 2; index >= 0; --index)
    {
        heapPushDown(array, data_size, index, comparator);
        //simple solution to "size_t >= 0"
        if (index == 0)
        {
            break;
        }
    }
    for (size_t index = data_size - 1; index > 0; --index)
    {
        swapStrings(&array.data[0], &array.data[index]);
        heapPushDown(array, index, 0, comparator);
        //simple solution to "size_t >= 0"
        if (index == 0)
        {
            break;
        }
    }
    return OK;
}

void heapPushDown(SmartArray array, const size_t size, size_t index, Compare_func comparator)
{
    size_t minimal_index = index;
    size_t left_index  = leftNode(index);
    size_t right_index = rightNode(index);

    if (left_index < size && comparator(&array.data[left_index], &array.data[minimal_index]) > 0)
    {
        minimal_index = left_index;
    }
    if (right_index < size && comparator(&array.data[right_index], &array.data[minimal_index]) > 0)
    {
        minimal_index = right_index;
    }
    if (index != minimal_index)
    {
        swapStrings(&array.data[index], &array.data[minimal_index]);
        heapPushDown(array, size, minimal_index, comparator);
    }
    return;
}

void swapStrings(SmartString* str_1, SmartString* str_2)
{
    char* temp_str = str_1->string;
    str_1->string = str_2->string;
    str_2->string = temp_str;

    size_t temp_len = str_1->length;
    str_1->length = str_2->length;
    str_2->length = temp_len;
}

int lexicograficStringComparator(const void* elem_1, const void* elem_2)
{
    char* str_1 = ((const SmartString*)elem_1)->string;
    char* str_2 = ((const SmartString*)elem_2)->string;

    size_t len_1 = ((const SmartString*)elem_1)->length - 1;
    size_t len_2 = ((const SmartString*)elem_2)->length - 1;

    size_t offset_1 = 0;
    size_t offset_2 = 0;
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
    char* str_1 = ((const SmartString*)elem_1)->string;
    char* str_2 = ((const SmartString*)elem_2)->string;

    size_t len_1 = ((const SmartString*)elem_1)->length - 1;
    size_t len_2 = ((const SmartString*)elem_2)->length - 1;

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



