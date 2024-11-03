#ifndef STRINGSORT_H
#define STRINGSORT_H

#include "Errors.h"
#include "StoringData.h"

//TODO: delete irrelevant functions(that user doesn`t need to see)

typedef int (*Compare_func)(const void*, const void*);

Status heapSort(smartString* array, const size_t size, Compare_func comparator);
void   heapPushDown(smartString* array, const size_t size, size_t index, Compare_func comparator);

void swapStrings(smartString* str1, smartString* str2);

int lexicograficStringComparator(const void* elem_1, const void* elem_2);
int rhymeStringComparator(const void* elem_1, const void* elem_2);

#endif //STRINGSORT_H
