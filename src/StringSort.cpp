#include <string.h>
#include <ctype.h>

#include "StringSort.h"
#include "StoringData.h"
#include "Color.h"
#include "Errors.h"
#include "Debug.h"

Status sortArray(Sorting_func sorter, MyArray* array, Compare_func comparator)
{
    myAssert(array != nullptr);
    myAssert(comparator != nullptr);

    if (sorter == nullptr)
    {
        return ALGORITHM_ERR;
    }
    return sorter(array, comparator);
}

Status quickSort(MyArray* array, Compare_func comparator)
{
    myAssert(array != nullptr);

    sortSubArrays(array, 0, (int)array->size - 1, comparator);
    return OK;
}

void sortSubArrays(MyArray* array, int left_index, int right_index, Compare_func comparator)
{
    myAssert(array != nullptr);

    if (left_index < right_index)
    {
        int pivot_index = splitArray(array, left_index, right_index, comparator);

        sortSubArrays(array, left_index, pivot_index - 1, comparator);
        sortSubArrays(array, pivot_index + 1, right_index, comparator);
    }
    return;
}

int splitArray(MyArray* array, int left_index, int right_index, Compare_func comparator)
{
    myAssert(array != nullptr);

    MyString* pivot_element_ptr = &array->data[right_index];
    int pivot_index = left_index - 1;

    for (int index = left_index; index < right_index; ++index)
    {
        if (comparator(&array->data[index], pivot_element_ptr) < 0)
        {
            pivot_index++;
            swapStrings(&array->data[index], &array->data[pivot_index]);
        }
    }
    swapStrings(&array->data[pivot_index + 1], pivot_element_ptr);
    return pivot_index + 1;
}

Status heapSort(MyArray* array, Compare_func comparator)
{
    myAssert(array != nullptr);

    size_t data_size = array->size;

    for (size_t index = (data_size - 1) / 2; index >= 0; --index)
    {
        heapPushDown(array, data_size, index, comparator);
        if (index == 0)
        {
            break;
        }
    }
    for (size_t index = data_size - 1; index > 0; --index)
    {
        swapStrings(&array->data[0], &array->data[index]);
        heapPushDown(array, index, 0, comparator);
        if (index == 0)
        {
            break;
        }
    }
    return OK;
}

void heapPushDown(MyArray* array, const size_t size, size_t index, Compare_func comparator)
{
    myAssert(array != nullptr);

    size_t minimal_index = index;
    size_t left_index  = leftNode(index);
    size_t right_index = rightNode(index);

    if (left_index < size && comparator(&array->data[left_index], &array->data[minimal_index]) > 0)
    {
        minimal_index = left_index;
    }
    if (right_index < size && comparator(&array->data[right_index], &array->data[minimal_index]) > 0)
    {
        minimal_index = right_index;
    }
    if (index != minimal_index)
    {
        swapStrings(&array->data[index], &array->data[minimal_index]);
        heapPushDown(array, size, minimal_index, comparator);
    }
    return;
}

void swapStrings(MyString* str_1, MyString* str_2)
{
    myAssert(str_1 != nullptr);
    myAssert(str_2 != nullptr);

    char* temp_str = str_1->string;
    str_1->string = str_2->string;
    str_2->string = temp_str;

    size_t temp_len = str_1->length;
    str_1->length = str_2->length;
    str_2->length = temp_len;
}

int lexicographicStringComparator(const void* elem_1, const void* elem_2)
{
    myAssert(elem_1 != nullptr);
    myAssert(elem_2 != nullptr);

    char* str_1 = ((const MyString*)elem_1)->string;
    char* str_2 = ((const MyString*)elem_2)->string;

    size_t len_1 = ((const MyString*)elem_1)->length - 1;
    size_t len_2 = ((const MyString*)elem_2)->length - 1;

    size_t offset_1 = 0;
    size_t offset_2 = 0;
    char letter_1 = ' ';
    char letter_2 = ' ';

    while (offset_1 <= len_1 && offset_2 <= len_2)
    {
        letter_1 = str_1[offset_1];
        letter_2 = str_2[offset_2];
        if (isalpha(letter_1) && isalpha(letter_2))
        {
            if (tolower(letter_1) != tolower(letter_2))
            {
                break;
            }
            offset_1++;
            offset_2++;
        }
        else
        {
            if (!isalpha(letter_1))
            {
                offset_1++;
            }
            if (!isalpha(letter_2))
            {
                offset_2++;
            }
        }
    }
    if (offset_1 > len_1 && offset_2 <= len_2)
    {
        return -str_2[offset_2];
    }
    else if (offset_1 <= len_1 && offset_2 > len_2)
    {
        return str_1[offset_1];
    }
    else if (offset_1 > len_1 && offset_2 > len_2)
    {
        return 0;
    }
    return (tolower(str_1[offset_1]) - tolower(str_2[offset_2]));
}

int rhymeStringComparator(const void* elem_1, const void* elem_2)
{
    myAssert(elem_1 != nullptr);
    myAssert(elem_2 != nullptr);

    char* str_1 = ((const MyString*)elem_1)->string;
    char* str_2 = ((const MyString*)elem_2)->string;

    int len_1 = (int)(((const MyString*)elem_1)->length - 1);
    int len_2 = (int)(((const MyString*)elem_2)->length - 1);

    char letter_1 = ' ';
    char letter_2 = ' ';
    while (len_1 >= 0 && len_2 >= 0)
    {
        letter_1 = str_1[len_1];
        letter_2 = str_2[len_2];
        if (isalpha(letter_1) && isalpha(letter_2))
        {
            if (tolower(letter_1) != tolower(letter_2))
            {
                break;
            }
            len_1--;
            len_2--;
        }
        else
        {
            if (!isalpha(letter_1))
            {
                len_1--;
            }
            if (!isalpha(letter_2))
            {
                len_2--;
            }
        }
    }
    if (len_1 < 0 && len_2 >= 0)
    {
        return -str_2[len_2];
    }
    else if (len_1 >= 0 && len_2 < 0)
    {
        return str_1[len_1];
    }
    else if (len_1 < 0 && len_2 < 0)
    {
        return 0;
    }
    return (tolower(str_1[len_1]) - tolower(str_2[len_2]));
}



