/*
 * A struct that functions as an array holding miscellaneous
 * pointers.
 * Dynamically allocates more memory on the heap when a new element
 * does not fit in the current allocation.
 */

#include <stdlib.h>
#include "dynamicArray.h"

#define EXPANSION_FACTOR 2



void * dyArr_getElement(dynamicArray *array, unsigned int index) {
  if(index >= array->count) {
    return 0;
  }
  return array->elements[index];
}


unsigned char dyArr_setElement(dynamicArray *array, unsigned int index,
  void *element) {
  if(index >= array->count) {
    return 0;
  }
  array->elements[index] = element;
}


void dyArr_appendElement(dynamicArray *array, void *element) {
  unsigned int i;
  void **elements_trans;

  // Resize allocation if necessary (double the size)
  if(array->count >= array->alloc_size) {
    elements_trans = malloc(EXPANSION_FACTOR * array->alloc_size
      * sizeof(void*));
    for(i = 0; i < array->count; i++) {
      elements_trans[i] = array->elements[i];
    }
    free(array->elements);
    array->elements = elements_trans;
    array->alloc_size *= EXPANSION_FACTOR;
  }

  // Append new element
  array->elements[array->count] = element;
  array->count++;
}


unsigned int dyArr_getCount(dynamicArray *array) {
  return array->count;
}


void dyArr_initialize(dynamicArray *array) {
  array->elements = malloc(sizeof(void*));
  array->count = 0;
  array->alloc_size = 1;
}


void dyArr_deinitialize(dynamicArray *array) {
  if(array->alloc_size > 0) {
    free(array->elements);
  }
}