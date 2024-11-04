#ifndef STRINGSORT_H
#define STRINGSORT_H

#include "Errors.h"
#include "StoringData.h"

#define leftNode(index)  (2 * (index) + 1);
#define rightNode(index) (2 * (index) + 2);

typedef int (*Compare_func)(const void*, const void*);

Status heapSort(SmartArray array, Compare_func comparator);

//TODO: delete from header?
void heapPushDown(SmartArray array, const size_t size, size_t index, Compare_func comparator);
void swapStrings(SmartString* str1, SmartString* str2);

int lexicograficStringComparator(const void* elem_1, const void* elem_2);
int rhymeStringComparator(const void* elem_1, const void* elem_2);

#endif //STRINGSORT_H
