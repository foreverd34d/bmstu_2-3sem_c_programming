#ifndef NUMPROC_H
#define NUMPROC_H

#include <stddef.h>

// сортировка пузырьком с флагом
void mysort(void *arr, size_t len, size_t size, int comp(const void *, const void *));
void swap(void *a, void *b, size_t size);
int comp_int(const void *a, const void *b);

#endif // !NUMPROC_H
