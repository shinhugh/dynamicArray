/*
 * A struct that functions as an array holding miscellaneous pointers.
 * Dynamically allocates more memory on the heap when a new element does not fit
 * in the current allocation.
 * Members of the struct should not be accessed/modified directly.
 */

#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

// ------------------------------------------------------------

// Global flags
// Flags are all reset at the start of every function call.

extern unsigned char DYARR_OUT_OF_BOUNDS;

// ------------------------------------------------------------

// Type definitions

typedef struct dynamicArray {
  void **elements;
  unsigned int count;
  unsigned int alloc_size;
} dynamicArray;

// ------------------------------------------------------------

// Functions

/*
 * Get an element.
 * Return: Element at specified index
 *         0 on out-of-bounds; set DYARR_OUT_OF_BOUNDS
 */
void * dyArr_getElement(const dynamicArray *array, unsigned int index);

/*
 * Set an element.
 */
void dyArr_setElement(dynamicArray *array,
  unsigned int index, void *element);

/*
 * Append an element at the end.
 */
void dyArr_appendElement(dynamicArray *array, void *element);

/*
 * Concatenate two arrays.
 * The contents of array A come previous to those of array B.
 * Allocates memory for new dynamicArray. Make sure to deinitialize and free.
 * Return: Address of newly allocated memory for the result dynamicArray
 */
dynamicArray * dyArr_concatenate(const dynamicArray *arrayA,
const dynamicArray *arrayB);

/*
 * Remove the element at the specified index.
 * Shift all following elements down by 1 index to fill the hole.
 * Does not free the memory held by the element itself.
 * Set DYARR_OUT_OF_BOUNDS on out-of-bounds
 */
void dyArr_removeElement(dynamicArray *array, unsigned int index);

/*
 * Remove all elements.
 * Does not free the memory held by the elements themselves.
 */
void dyArr_removeAllElements(dynamicArray *array);

/*
 * Get the number of elements.
 * Return: Number of elements
 */
unsigned int dyArr_getCount(const dynamicArray *array);

/*
 * Initialize an array.
 * Must be called a single time before array is used.
 * Every call should be followed by a dyArr_free() call before reference to
 * array is lost.
 */
void dyArr_initialize(dynamicArray *array);

/*
 * Deinitialize an array.
 * Array should not be used after call, unless dyArr_initialize() is called
 * again.
 * Must be called a single time before reference to array is lost to avoid
 * memory leaks.
 * Must be preceded by a dyArr_initialize() call.
 * Does not free the memory held by the elements themselves.
 */
void dyArr_deinitialize(dynamicArray *array);

// ------------------------------------------------------------

#endif
