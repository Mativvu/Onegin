#ifndef STRINGSORT_H
#define STRINGSORT_H

#include "Errors.h"
#include "StoringData.h"

#define leftNode(index)  (2 * (index) + 1);
#define rightNode(index) (2 * (index) + 2);

typedef int    (*Compare_func)(const void*, const void*);
typedef Status (*Sorting_func)(MyArray* array, Compare_func comparator);

Status sortArray(Sorting_func sorter, MyArray* array, Compare_func comparator);
Status heapSort (MyArray* array, Compare_func comparator);
Status quickSort(MyArray* array, Compare_func comparator);

int  splitArray   (MyArray* array, int left_index, int right_index, Compare_func comparator);
void sortSubArrays(MyArray* array, int left_index, int right_index, Compare_func comparator);
void heapPushDown (MyArray* array, const size_t size, size_t index, Compare_func comparator);
void swapStrings  (MyString* str1, MyString* str2);

int lexicographicStringComparator(const void* elem_1, const void* elem_2);
int rhymeStringComparator(const void* elem_1, const void* elem_2);

#endif //STRINGSORT_H
