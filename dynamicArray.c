/*
 * A struct that functions as an array holding miscellaneous
 * pointers.
 * Dynamically allocates more memory on the heap when a new element
 * does not fit in the current allocation.
 */

#include <stdlib.h>
#include "dynamicArray.h"

#define EXPANSION_FACTOR 2

/************************************************************/

unsigned char DYARR_OUT_OF_BOUNDS;

/************************************************************/

void * dyArr_getElement(dynamicArray *array, unsigned int index) {

  DYARR_OUT_OF_BOUNDS = 0;

  // Check for out-of-bounds
  if(index >= array->count) {
    DYARR_OUT_OF_BOUNDS = 1;
    return 0;
  }

  // Get element
  return array->elements[index];

}

/************************************************************/

unsigned char dyArr_setElement(dynamicArray *array, unsigned int index,
  void *element) {

  DYARR_OUT_OF_BOUNDS = 0;

  // Check for out-of-bounds
  if(index >= array->count) {
    DYARR_OUT_OF_BOUNDS = 1;
    return 0;
  }

  // Set element
  array->elements[index] = element;

}

/************************************************************/

void dyArr_appendElement(dynamicArray *array, void *element) {

  unsigned int i;
  void **elements_trans;

  DYARR_OUT_OF_BOUNDS = 0;

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

/************************************************************/

void dyArr_removeElement(dynamicArray *array, unsigned int index) {

  unsigned int i;

  DYARR_OUT_OF_BOUNDS = 0;

  // Check for out-of-bounds
  if(index >= array->count) {
    DYARR_OUT_OF_BOUNDS = 1;
    return;
  }

  // Shift down elements
  for(i = index; i < array->count - 1; i++) {
    array->elements[i] = array->elements[i + 1];
  }

  // Decrement count
  (array->count)--;

}

/************************************************************/

void dyArr_removeAllElements(dynamicArray *array) {

  DYARR_OUT_OF_BOUNDS = 0;

  // Set count to 0
  array->count = 0;

}

/************************************************************/

unsigned int dyArr_getCount(dynamicArray *array) {

  DYARR_OUT_OF_BOUNDS = 0;

  // Get count
  return array->count;

}

/************************************************************/

void dyArr_initialize(dynamicArray *array) {

  DYARR_OUT_OF_BOUNDS = 0;

  // Start with array capacity 1, empty
  array->elements = malloc(sizeof(void*));
  array->count = 0;
  array->alloc_size = 1;

}

/************************************************************/

void dyArr_deinitialize(dynamicArray *array) {

  DYARR_OUT_OF_BOUNDS = 0;

  // Free memory used by pointer array
  if(array->alloc_size > 0) {
    free(array->elements);
  }

}

/************************************************************/
