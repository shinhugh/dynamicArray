/*
 * Refer to dynamicArray.h for description.
 */

#include <stdlib.h>
#include "dynamicArray.h"

#define EXPANSION_FACTOR 2

// ------------------------------------------------------------

unsigned char DYARR_OUT_OF_BOUNDS;

// ------------------------------------------------------------

void * dyArr_getElement(const dynamicArray *array, unsigned int index) {

  DYARR_OUT_OF_BOUNDS = 0;

  // Check for out-of-bounds
  if(index >= array->count) {
    DYARR_OUT_OF_BOUNDS = 1;
    return 0;
  }

  // Get element
  return array->elements[index];

}

// ------------------------------------------------------------

void dyArr_setElement(dynamicArray *array, unsigned int index,
  const void *element) {

  DYARR_OUT_OF_BOUNDS = 0;

  // Check for out-of-bounds
  if(index >= array->count) {
    DYARR_OUT_OF_BOUNDS = 1;
    return;
  }

  // Set element
  array->elements[index] = element;

}

// ------------------------------------------------------------

void dyArr_appendElement(dynamicArray *array, const void *element) {

  unsigned int i;
  void **elements_trans;
  const unsigned int array_count = array->count;

  DYARR_OUT_OF_BOUNDS = 0;

  // Resize allocation if necessary
  if(array_count >= array->alloc_size) {
    elements_trans = malloc(EXPANSION_FACTOR * array->alloc_size
      * sizeof(void*));
    for(i = 0; i < array_count; i++) {
      elements_trans[i] = array->elements[i];
    }
    free(array->elements);
    array->elements = elements_trans;
    array->alloc_size *= EXPANSION_FACTOR;
  }

  // Append new element
  array->elements[array_count] = element;
  array->count++;

}

// ------------------------------------------------------------

dynamicArray * dyArr_concatenate(const dynamicArray *arrayA, const dynamicArray *arrayB) {

  unsigned int i;
  dynamicArray *result;
  unsigned int alloc_size;
  const unsigned int arrayA_count = arrayA->count;
  const unsigned int arrayB_count = arrayB->count;

  DYARR_OUT_OF_BOUNDS = 0;

  // Allocate memory for new dynamicArray instance with enough capacity to hold contents of both arrayA and arrayB
  result = malloc(sizeof(dynamicArray));
  alloc_size = 1;
  while(alloc_size < arrayA_count + arrayB_count) {
    alloc_size *= EXPANSION_FACTOR;
  }
  result->elements = malloc(alloc_size * sizeof(void*));
  result->alloc_size = alloc_size;

  // Add contents of both arrayA and arrayB into new array
  for(i = 0; i < arrayA_count; i++) {
    result->elements[i] = arrayA->elements[i];
  }
  for(i = 0; i < arrayB_count; i++) {
    result->elements[i + arrayA_count] = arrayB->elements[i];
  }
  result->count = arrayA_count + arrayB_count;

  return result;

}

// ------------------------------------------------------------

void dyArr_removeElement(dynamicArray *array, unsigned int index) {

  unsigned int i;
  const unsigned int array_count = array->count;

  DYARR_OUT_OF_BOUNDS = 0;

  // Check for out-of-bounds
  if(index >= array_count) {
    DYARR_OUT_OF_BOUNDS = 1;
    return;
  }

  // Shift down elements
  for(i = index; i < array_count - 1; i++) {
    array->elements[i] = array->elements[i + 1];
  }

  // Decrement count
  (array->count)--;

}

// ------------------------------------------------------------

void dyArr_removeAllElements(dynamicArray *array) {

  DYARR_OUT_OF_BOUNDS = 0;

  // Set count to 0
  array->count = 0;

}

// ------------------------------------------------------------

unsigned int dyArr_getCount(const dynamicArray *array) {

  DYARR_OUT_OF_BOUNDS = 0;

  // Get count
  return array->count;

}

// ------------------------------------------------------------

void dyArr_initialize(dynamicArray *array) {

  DYARR_OUT_OF_BOUNDS = 0;

  // Start with array capacity 1, empty
  array->elements = malloc(sizeof(void*));
  array->count = 0;
  array->alloc_size = 1;

}

// ------------------------------------------------------------

void dyArr_deinitialize(dynamicArray *array) {

  DYARR_OUT_OF_BOUNDS = 0;

  // Free memory used by pointer array
  if(array->alloc_size > 0) {
    free(array->elements);
  }

}

// ------------------------------------------------------------
