#include <stdio.h>
#include <stdlib.h>

#define NULL_ITEM 0

typedef struct {
  int length;  // length of the Array object
  int items[]; // items in Array object
} Array;

/*
 * is a constructor for Array object
 * initializes the Array object with an initial length of 1
 * and setting its first element as a NULL_ITEM
 */
Array *create_array() {
  Array *_tmp_array = (Array *)malloc(sizeof(Array));

  // check if '_tmp_array' is allocated successfully
  if (_tmp_array == NULL) {
    printf("Array allocation failed!\n");
    exit(EXIT_FAILURE);
  }

  _tmp_array->length = 1;
  _tmp_array->items[0] = NULL_ITEM;
  return _tmp_array;
}

void print_array(Array *_array) {
  int _array_length = _array->length;
  printf("Array: { ");
  for (int i = 0; i < _array_length; i++) {
    if (i == _array_length)
      printf("");
    if (_array->items[i] == NULL_ITEM)
      printf("NULL, ");
    else
      printf("%d, ", _array->items[i]);
  }
  printf("}\n");
}

// returns the index of the key in the array
// if key not present returns -1.
int search(Array *_array, int key) {
  for (int index = 0; index < _array->length; index++) {
    if (_array->items[index] == key) {
      return index;
    }
  }
  return -1;
}

// copies all the items of '_old_array' and declares them
// to the '_new_array' which is twice in size of the former.
void copy(Array *_old_array, Array *_new_array) {
  for (int index = 0; index < _old_array->length; index++) {
    _new_array->items[index] = _old_array->items[index];
  }
}

// fills the array with 'NULL_ITEM'
void allocate_null(Array *_array) {
  for (int index = 0; index < _array->length; index++) {
    _array->items[index] = NULL_ITEM;
  }
}

// inserts key at the end of '_array'
void insert(Array *_array, int key) {
  if (_array->items[_array->length - 1] != NULL_ITEM) {
    Array *_double_array = malloc(sizeof(Array));
    if (_double_array == NULL) {
      printf("array allocation failed!");
      exit(EXIT_FAILURE);
    }
    _double_array->length = 2 * _array->length;
    allocate_null(_double_array);
    copy(_array, _double_array);
    insert(_double_array, key);

    // FIX: the _array at this point is Array: { 8, }
    // and the _double_array is Array: { 8, 7, }
    *_array = *_double_array;
    // at this point: _array = Array: { 8, NULL, }
    // at this point: _double_array = Array: { 8, 7, }
  } else {
    _array->items[search(_array, NULL_ITEM)] = key;
  }
}

int main(int argc, char *argv[]) {
  Array *array = create_array();
  insert(array, 8);
  insert(array, 7);
  exit(EXIT_SUCCESS);
}
