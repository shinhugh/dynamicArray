/*
 * A struct that functions as an array holding miscellaneous
 * pointers.
 * Dynamically allocates more memory on the heap when a new element
 * does not fit in the current allocation.
 * Members of the struct should not be accessed/modified directly.
 */

#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

typedef struct dynamicArray {
  void **elements;
  unsigned int count;
  unsigned int alloc_size;
} dynamicArray;


/*
 * Get an element.
 * Return: Element at specified index
 *         0 on out-of-bounds
 */
void * dyArr_getElement(dynamicArray *array, unsigned int index);

/*
 * Set an element.
 * Return: 1 on success
 *         0 on out-of-bounds
 */
unsigned char dyArr_setElement(dynamicArray *array,
  unsigned int index, void *element);

/*
 * Append an element at the end.
 */
void dyArr_appendElement(dynamicArray *array, void *element);

/*
 * Get the number of elements.
 * Return: Number of elements
 */
unsigned int dyArr_getCount(dynamicArray *array);

/*
 * Initialize an array.
 * Must be called a single time before array is used.
 * Every call should be followed by a dyArr_free() call before
 * reference to array is lost.
 */
void dyArr_initialize(dynamicArray *array);

/*
 * Deinitialize an array.
 * Array should not be used after call, unless dyArr_initialize() is
 * called again.
 * Must be called a single time before reference to array is lost to avoid
 * memory leaks.
 * Must be preceded by a dyArr_initialize() call.
 */
void dyArr_deinitialize(dynamicArray *array);


#endif
