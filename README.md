# STF_Lists
**Simple library to create and manipulate array lists in c**

## Introduction
STF_Lists are linked lists of data, so the developer can dynamically create, delete, replace, add, concat... and that makes the development process easier.

## Headers
All included headers are C standard header files: `"stdio.h"`, `"stdlib.h"`, `"string.h"`, `"ctype.h"`, `"stdbool.h"`

## Naming
- **BL:** BoolList
- **CL:** CharList
- **IL:** IntList
- **DL:** DoubleList
- **SL:** StringList

## Examples
```c
#include <stdio.h>
#include "STF_Lists.h"

int main() {
  CL *name = CL_createFrom("Toumi Fouad Saadi");
  CL_print(name);
  printf("\n%d", name->size);
  CL_delete(name);
  return 0;
}
```
output:
```
Toumi Fouad Saadi
17
```
## Documentation
[**STF_Lists documentation**](https://github.com/SaymoinSam/STF_Lists/wiki)