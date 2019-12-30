# dynamicArray

A run-time flexible array that holds pointers to arbitrary data.

A `dynamicArray` instance holds the *memory addresses* of data stored elsewhere
in memory, *not the data itself*.<br/>
The type of the data does not matter (the array holds `void *` pointers). This
allows for flexible usage but requires type-casting upon retrieving
elements.

Do *not* access/modify the members of the struct `dynamicArray` directly;
behavior is undefined. Utilize the provided functions instead.

## Functions

All functions take in the memory address of a `dynamicArray` instance as their
first argument. The library is structured to imitate dynamic object-oriented
programming.<br/>
Take a peek inside `dynamicArray.h` for more details on each function.

#### `dyArr_getElement()`
Access the pointer stored at the specified index.

#### `dyArr_setElement()`
Store a pointer at the specified index.

#### `dyArr_appendElement()`
Append a pointer to the back, as the last element.

#### `dyArr_removeElement()`
Remove the pointer at the specified index. This does not free the memory held by
the element itself at the address inside the removed pointer.

#### `dyArr_removeAllElements()`
Remove all pointers. This does not free the memory held by the elements
themselves at the addresses inside the removed pointers.

#### `dyArr_getCount()`
Get the total number of elements stored.

#### `dyArr_initialize()`
Initialize the array. This prepares it for usage. It must be called first.

#### `dyArr_deinitialize()`
De-initialize the array. This frees any memory allocated by the array. It must
be called if `dyArr_initialize()` was called previously. To avoid a memory
leak, make the call before reference to the array is lost. Note that this does
not free the `dynamicArray` instance itself but any memory that it had allocated
in its lifetime. If the array was created on the heap, the user must still
manually free that memory. This also does not free the memory used by the data
itself.

## Flags

Flags are global scope `unsigned char` values.<br/>
`0` means unset. Any other value means set.

#### `DYARR_OUT_OF_BOUNDS`
Set when a function takes in an index that is not less than the number of
elements.

## Build

1. Clone this repository.
2. Run `make`. This generates the file `libdynamicArray.a`, which is a static
library that contains the implementation for the functions declared in
`dynamicArray.h`.
3. You may remove all files from this repository besides `libdynamicArray.a`
and `dynamicArray.h`. The two files can be placed anywhere.

When using this library, make sure to have in your C source code:
```c
#include "dynamicArray.h"
```
When compiling your code, include `libdynamicArray.a` as such:
```shell
gcc [your files] -I [path to dynamicArray.h] -L [path to libdynamicArray.a] -l dynamicArray
```
Otherwise, the structure is simple enough where you may avoid the makefile
altogether. Just compile the `.c` file and link the `.o` file manually.

## Example usage

The following C code creates an array of ints then iterates through it and
prints the contents. Note that `dynamicArray` instances can not hold the data
itself, but the addresses of the data stored elsewhere in memory.

Code:
```c
unsigned int i;
dynamicArray arr;

// Initialize array
dyArr_initialize(&arr);

// Create array of ints
for(i = 0; i < 5; i++) {
  // Append a new pointer to an int on the heap
  dyArr_appendElement(&arr, malloc(sizeof(int)));
  // Set the value of the newly appended int to i (0 ~ 4)
  // Don't forget to cast and dereference address returned by getElement()
  // getCount() - 1 gets the index of the last appended element
  *((int *) dyArr_getElement(&arr, dyArr_getCount(&arr) - 1)) = i;
}

// Print all elements
for(i = 0; i < dyArr_getCount(&arr); i++) {
  printf("%d\n", *((int *) dyArr_getElement(&arr, i)));
}

// Free memory allocated for each int element
for(i = 0; i < dyArr_getCount(&arr); i++) {
  free(dyArr_getElement(&arr, i));
}

// Deinitialize array
dyArr_deinitialize(&arr);
```
Output:
```
0
1
2
3
4
```
