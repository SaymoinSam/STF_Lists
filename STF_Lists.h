////////////////////////////////////////////////////////////////////////////////
//
// STF_Lists - simple library to create and manipulate array lists
// Copyright (C) 2020 Toumi Fouad Saadi (saaditoumifouad@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the
// use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef STF_LISTS_H
#define STF_LISTS_H

////////////////////////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef char * String;

////////////////////////////////////////////////////////////////////////////////
/// \brief node class with one node and the address of the next one
///
////////////////////////////////////////////////////////////////////////////////
typedef struct CN {
  char value;
  struct CN *next;
} CN;

typedef struct BN {
  bool value;
  struct BN *next;
} BN;

typedef struct IN {
  int value;
  struct IN *next;
} IN;

typedef struct DN {
  double value;
  struct DN *next;
} DN;

////////////////////////////////////////////////////////////////////////////////
/// \brief node list class with the first and last nodes and the size of the list
///
////////////////////////////////////////////////////////////////////////////////
typedef struct {
  CN *start;
  CN *end;
  int size;
} CL;

typedef struct SN {
  CL *value;
  struct SN *next;
} SN;

typedef struct {
  BN *start;
  BN *end;
  int size;
} BL;

typedef struct {
  IN *start;
  IN *end;
  int size;
} IL;

typedef struct {
  DN *start;
  DN *end;
  int size;
} DL;

typedef struct {
  SN *start;
  SN *end;
  int size;
} SL;

////////////////////////////////////////////////////////////////////////////////
/// \brief Delete a string node
///
/// \param stringNode The node to delete
///
////////////////////////////////////////////////////////////////////////////////
static void SN_delete(SN *stringNode);

////////////////////////////////////////////////////////////////////////////////
/// \brief Create a new stringNode object from a charList
///
/// \param charList The charlist to create from
///
/// \return A new CharNode object, or NULL if it failed
///
////////////////////////////////////////////////////////////////////////////////
static SN * SN_createFromList(CL *charList);

////////////////////////////////////////////////////////////////////////////////
/// \brief Create a new node object
///
/// \param v The value of the node
///
/// \return A new node object, or NULL if it failed
///
////////////////////////////////////////////////////////////////////////////////
static BN * BN_create(bool v);
static CN * CN_create(char v);
static IN * IN_create(int v);
static DN * DN_create(double v);
static SN * SN_create(String v);

////////////////////////////////////////////////////////////////////////////////
/// \brief Get the node address of the given index
///
/// \param list  The list to get from
/// \param index The index of the node
///
/// \return The address of the node, or NULL if it failed
///
////////////////////////////////////////////////////////////////////////////////
static BN * BL_getNode(BL *list, int index);
static CN * CL_getNode(CL *list, int index);
static IN * IL_getNode(IL *list, int index);
static DN * DL_getNode(DL *list, int index);
static SN * SL_getNode(SL *list, int index);

////////////////////////////////////////////////////////////////////////////////
/// \brief Create a new list object
///
/// \return A new list object, or NULL if it failed
///
////////////////////////////////////////////////////////////////////////////////
BL * BL_create(void);
CL * CL_create(void);
IL * IL_create(void);
DL * DL_create(void); 
SL * SL_create(void);

////////////////////////////////////////////////////////////////////////////////
/// \brief Add a new node to the list
///
/// \param list The list to add to
/// \param v    The value of the node
///
/// \return false if it failed and true otherwise
///
////////////////////////////////////////////////////////////////////////////////
bool BL_add(BL *list, bool v);
bool CL_add(CL *list, char v);
bool IL_add(IL *list, int v);
bool DL_add(DL *list, double v); 
bool SL_addArray(SL *list, String v);
bool SL_addList(SL *list, CL *v);

////////////////////////////////////////////////////////////////////////////////
/// \brief Adds a new node at the beginning of the list
///
/// \param list The list to unshift
/// \param v    The value of the node
///
/// \return false if it failed and true otherwise
///
////////////////////////////////////////////////////////////////////////////////
bool BL_unshift(BL *list, bool v);
bool CL_unshift(CL *list, char v);
bool IL_unshift(IL *list, int v);
bool DL_unshift(DL *list, double v); 
bool SL_unshiftArray(SL *list, String v);
bool SL_unshiftList(SL *list, CL *v);

////////////////////////////////////////////////////////////////////////////////
/// \brief Remove the last node in the list
///
/// \param list The list to pop
///
/// \return The removed value, in case of SL object no return
///
////////////////////////////////////////////////////////////////////////////////
bool BL_pop(BL *list);
char CL_pop(CL *list);
int IL_pop(IL *list);
double DL_pop(DL *list); 
void SL_pop(SL *list);

////////////////////////////////////////////////////////////////////////////////
/// \brief Remove the first node in the list
///
/// \param list The list to shift
///
/// \return The removed value, in case of SL object no return
///
////////////////////////////////////////////////////////////////////////////////
bool BL_shift(BL *list);
char CL_shift(CL *list);
int IL_shift(IL *list);
double DL_shift(DL *list);
void SL_shift(SL *list);

////////////////////////////////////////////////////////////////////////////////
/// \brief Inserts a node in a given index
///
/// \param list  The list to insert in
/// \param v     The value to insert
/// \param index The index in the list
///
/// \return false if it failed and true otherwise
///
////////////////////////////////////////////////////////////////////////////////
bool BL_insert(BL *list, bool v, int index);
bool CL_insert(CL *list, char v, int index);
bool IL_insert(IL *list, int v, int index);
bool DL_insert(DL *list, double v, int index);
bool SL_insertList(SL *list, CL *v, int index);
bool SL_insertArray(SL *list, String v, int index);

////////////////////////////////////////////////////////////////////////////////
/// \brief Remove the node of the given index from the list
///
/// \param list  The list to remove from
/// \param index The index of the node
///
/// \return The removed value, in case of SL object no return
///
////////////////////////////////////////////////////////////////////////////////
bool BL_remove(BL *list, int index);
char CL_remove(CL *list, int index);
int IL_remove(IL *list, int index);
double DL_remove(DL *list, int index);
void SL_remove(SL *list, int index);

////////////////////////////////////////////////////////////////////////////////
/// \brief Clear the list
///
/// \param list The list to clear
///
////////////////////////////////////////////////////////////////////////////////
void BL_clear(BL *list);
void CL_clear(CL *list);
void IL_clear(IL *list);
void DL_clear(DL *list);
void SL_clear(SL *list);

////////////////////////////////////////////////////////////////////////////////
/// \brief Delete the list
///
/// \param list The list to delete
///
////////////////////////////////////////////////////////////////////////////////
void BL_delete(BL *list);
void CL_delete(CL *list);
void IL_delete(IL *list);
void DL_delete(DL *list);
void SL_delete(SL *list);

////////////////////////////////////////////////////////////////////////////////
/// \brief Set the value of the given node index
///
/// \param list  The list to set in
/// \param index The index of the node
/// \param v     The value of the node
///
/// \return false if it failed and true otherwise
///
////////////////////////////////////////////////////////////////////////////////
bool BL_set(BL * list, bool v, int index);
bool CL_set(CL * list, char v, int index);
bool IL_set(IL * list, int v, int index);
bool DL_set(DL * list, double v, int index);
bool SL_setArray(SL * list, String v, int index);
bool SL_setList(SL * list, CL *v, int index);

////////////////////////////////////////////////////////////////////////////////
/// \brief Get the value of the given node index
///
/// \param list  The list to get from
/// \param index The index of the node
///
/// \return The value of the node
///
////////////////////////////////////////////////////////////////////////////////
bool BL_get(BL * list, int index);
char CL_get(CL * list, int index);
int IL_get(IL * list, int index);
double DL_get(DL * list, int index);
String SL_get(SL * list, int index);

////////////////////////////////////////////////////////////////////////////////
/// \brief Create an array from the list
///
/// \param list The list to create from
///
/// \return The address of the created array
///
////////////////////////////////////////////////////////////////////////////////
bool * BL_toBoolArray(BL *list);
String CL_toCharArray(CL *list);
int * IL_toIntArray(IL *list);
double * DL_toDoubleArray(DL *list); 

////////////////////////////////////////////////////////////////////////////////
/// \brief Convert the list to lowercase
///
/// \param list The list to convert
///
////////////////////////////////////////////////////////////////////////////////
void CL_toLowerCase(CL *list);
void SL_toLowerCase(SL *list);

////////////////////////////////////////////////////////////////////////////////
/// \brief Convert the list to uppercase
///
/// \param list The list to convert
///
////////////////////////////////////////////////////////////////////////////////
void CL_toUpperCase(CL *list);
void SL_toUpperCase(SL *list);

////////////////////////////////////////////////////////////////////////////////
/// \brief Convert the first node in the list to uppercase
///
/// \param list The list to capitalize
///
////////////////////////////////////////////////////////////////////////////////
void CL_capitalize(CL *list);
void SL_capitalize(SL *list);

////////////////////////////////////////////////////////////////////////////////
/// \brief sort the given list
///
/// \param list The list to sort
/// \param isReversed The sorting direction if it's true(descending) or false(ascending)
///
////////////////////////////////////////////////////////////////////////////////
static void _BL_sort(BL *list, bool isReversed);
static void _CL_sort(CL *list, bool isReversed);
static void _IL_sort(IL *list, bool isReversed);
static void _DL_sort(DL *list, bool isReversed);
static void _SL_sort(SL *list, bool isReversed);

////////////////////////////////////////////////////////////////////////////////
/// \brief sort the given list (ascending)
///
/// \param list The list to sort
///
////////////////////////////////////////////////////////////////////////////////
void BL_sort(BL *list);
void CL_sort(CL *list);
void IL_sort(IL *list);
void DL_sort(DL *list);
void SL_sort(SL *list);

////////////////////////////////////////////////////////////////////////////////
/// \brief sort the given list (descending)
///
/// \param list The list to sort
///
///////////////////////////////////////////////////////////////////////////////
void BL_rsort(BL *list);
void CL_rsort(CL *list);
void IL_rsort(IL *list);
void DL_rsort(DL *list);
void SL_rsort(SL *list);

////////////////////////////////////////////////////////////////////////////////
/// \brief Create a list from an array
///
/// \param array The address of the array
/// \param len   The length of the array, in case of char array no len param
///
/// \return The new list, or NULL if it failed
///
////////////////////////////////////////////////////////////////////////////////
BL * BL_createFrom(bool *array, int len);
CL * CL_createFrom(String array);
IL * IL_createFrom(int *array, int len);
DL * DL_createFrom(double *array, int len);
SL * SL_createFrom(String *array, int len);

////////////////////////////////////////////////////////////////////////////////
/// \brief Create a new list from another list
///
/// \param list The list to copy
///
/// \return The new list copy, or NULL if it failed
///
////////////////////////////////////////////////////////////////////////////////
BL * BL_copy(BL *list);
CL * CL_copy(CL *list);
IL * IL_copy(IL *list);
DL * DL_copy(DL *list);
SL * SL_copy(SL *list);

////////////////////////////////////////////////////////////////////////////////
/// \brief Merge the list with an array
///
/// \param list  The list to concat
/// \param array The address of the array
///
/// \return false if it failed and true otherwise
///
////////////////////////////////////////////////////////////////////////////////
bool BL_concatArray(BL *list, bool *array, int len);
bool CL_concatArray(CL *list, String array);
bool IL_concatArray(IL *list, int *array, int len);
bool DL_concatArray(DL *list, double *array, int len); 

////////////////////////////////////////////////////////////////////////////////
/// \brief Merge the list with another list
///
/// \param listA The first list
/// \param listB The second list
///
/// \return false if it failed and true otherwise
///
////////////////////////////////////////////////////////////////////////////////
bool BL_concatList(BL *listA, BL *listB);
bool CL_concatList(CL *listA, CL *listB);
bool IL_concatList(IL *listA, IL *listB);
bool DL_concatList(DL *listA, DL *listB);
bool SL_concat(SL *listA, SL *listB);

////////////////////////////////////////////////////////////////////////////////
/// \brief Reverse the list
///
/// \param list The list to reverse
///
/// \return false if it failed and true otherwise
///
////////////////////////////////////////////////////////////////////////////////
bool BL_reverse(BL *list);
bool CL_reverse(CL *list);
bool IL_reverse(IL *list);
bool DL_reverse(DL *list);
bool SL_reverse(SL *list);

////////////////////////////////////////////////////////////////////////////////
/// \brief Create a new list which is a piece from the original one
///
/// \param list  The list to create from
/// \param start The index to start from
/// \param end   The index to stop at (not included)
///
/// \return The sublist, or NULL if it failed
///
////////////////////////////////////////////////////////////////////////////////
BL * BL_slice(BL *list, int start, int end);
CL * CL_slice(CL *list, int start, int end);
IL * IL_slice(IL *list, int start, int end);
DL * DL_slice(DL *list, int start, int end);
SL * SL_slice(SL *list, int start, int end);

////////////////////////////////////////////////////////////////////////////////
/// \brief Create a new list which is a piece from the original one
///
/// \param list   The list to create from
/// \param start  The index to start from
/// \param length The length of the sub list 
///
/// \return The sublist, or NULL if it failed
///
////////////////////////////////////////////////////////////////////////////////
BL * BL_sub(BL *list, int start, int length);
CL * CL_sub(CL *list, int start, int length);
IL * IL_sub(IL *list, int start, int length);
DL * DL_sub(DL *list, int start, int length);
SL * SL_sub(SL *list, int start, int length);

////////////////////////////////////////////////////////////////////////////////
/// \brief Check if the list starts with the given value
///
/// \param list The list to be checked
/// \param v    The value to check against
///
/// \return true if it's true and false otherwise
///
////////////////////////////////////////////////////////////////////////////////
bool BL_startsWith(BL *list, bool v);
bool CL_startsWith(CL *list, char v);
bool IL_startsWith(IL *list, int v);
bool DL_startsWith(DL *list, double v);
bool SL_startsWithArray(SL *list, String v);
bool SL_startsWithList(SL *list, CL *v);

////////////////////////////////////////////////////////////////////////////////
/// \brief Check if the list ends with the given value
///
/// \param list The list to be checked
/// \param v    The value to check against
///
/// \return true if it's true and false otherwise
///
////////////////////////////////////////////////////////////////////////////////
bool BL_endsWith(BL *list, bool v);
bool CL_endsWith(CL *list, char v);
bool IL_endsWith(IL *list, int v);
bool DL_endsWith(DL *list, double v);
bool SL_endsWithArray(SL *list, String v);
bool SL_endsWithList(SL *list, CL *v); 

////////////////////////////////////////////////////////////////////////////////
/// \brief Check if the list contains the given value
///
/// \param list The list to be checked
/// \param v    The value to check against
///
/// \return true if it's true and false otherwise
///
////////////////////////////////////////////////////////////////////////////////
bool BL_contains(BL * list, bool v);
bool CL_contains(CL * list, char v);
bool IL_contains(IL * list, int v);
bool DL_contains(DL * list, double v);
bool SL_containsArray(SL * list, String v);
bool SL_containsList(SL * list, CL *v);

////////////////////////////////////////////////////////////////////////////////
/// \brief Check if the list is empty
///
/// \param list The list to be checked
///
/// \return true if it's true and false otherwise
///
////////////////////////////////////////////////////////////////////////////////
bool BL_isEmpty(BL *list);
bool CL_isEmpty(CL *list);
bool IL_isEmpty(IL *list);
bool DL_isEmpty(DL *list);
bool SL_isEmpty(SL *list);

////////////////////////////////////////////////////////////////////////////////
/// \brief Compare two lists 
///
/// \param listA The list to be compared
/// \param listB The list to be compare with
///
/// \return 0 if both are equal, 1 if the first list comes first, -1 instead
///
////////////////////////////////////////////////////////////////////////////////
int BL_compare(BL *listA, BL *listB);
int CL_compare(CL *listA, CL *listB);
int IL_compare(IL *listA, IL *listB);
int DL_compare(DL *listA, DL *listB); 

////////////////////////////////////////////////////////////////////////////////
/// \brief Check if both lists are equal 
///
/// \param listA The first list to be checked
/// \param listB The second list to be checked against
///
/// \return true if it's true and false otherwise
///
////////////////////////////////////////////////////////////////////////////////
bool BL_equalsList(BL *listA, BL *listB);
bool CL_equalsList(CL *listA, CL *listB);
bool IL_equalsList(IL *listA, IL *listB);
bool DL_equalsList(DL *listA, DL *listB);
bool SL_equals(SL *listA, SL *listB);

////////////////////////////////////////////////////////////////////////////////
/// \brief Check if both the list and the array have the same items
///
/// \param list  The list to be checked
/// \param array The array to be checked against
///
/// \return true if it's true and false otherwise
///
////////////////////////////////////////////////////////////////////////////////
bool BL_equalsArray(BL *list, bool *array, int len);
bool CL_equalsArray(CL *list, String array);
bool IL_equalsArray(IL *list, int *array, int len);
bool DL_equalsArray(DL *list, double *array, int len); 

////////////////////////////////////////////////////////////////////////////////
/// \brief Check if both lists are the same (the same address)
///
/// \param listA The first list to be checked
/// \param listB The second list to be checked against
///
/// \return true if it's true and false otherwise
///
////////////////////////////////////////////////////////////////////////////////
bool BL_isSame(BL *listA, BL *listB);
bool CL_isSame(CL *listA, CL *listB);
bool IL_isSame(IL *listA, IL *listB);
bool DL_isSame(DL *listA, DL *listB);
bool SL_isSame(SL *listA, SL *listB);

////////////////////////////////////////////////////////////////////////////////
/// \brief Get the first index of the given value
///
/// \param list The list to get from
/// \param v    The value to check against
///
/// \return The index of the first match in the list, -1 if none
///
////////////////////////////////////////////////////////////////////////////////
int BL_indexOf(BL * list, bool v);
int CL_indexOf(CL * list, char v);
int IL_indexOf(IL * list, int v);
int DL_indexOf(DL * list, double v);
int SL_indexOfArray(SL * list, String v);
int SL_indexOfList(SL * list, CL *v);

////////////////////////////////////////////////////////////////////////////////
/// \brief Get the last index of the given value
///
/// \param list The list to get from
/// \param v    The value to check against
///
/// \return The index of the last match in the list, -1 if none
///
////////////////////////////////////////////////////////////////////////////////
int BL_lastIndexOf(BL * list, bool v);
int CL_lastIndexOf(CL * list, char v);
int IL_lastIndexOf(IL * list, int v);
int DL_lastIndexOf(DL * list, double v);
int SL_lastIndexOfArray(SL * list, String v);
int SL_lastIndexOfList(SL * list, CL *v);

////////////////////////////////////////////////////////////////////////////////
/// \brief Count how many times a value has occured in the list
///
/// \param list The list to count in
/// \param v    The value to check against
///
/// \return The number of occurences
///
////////////////////////////////////////////////////////////////////////////////
int BL_count(BL *list, bool v);
int CL_count(CL *list, char v);
int IL_count(IL *list, int v);
int DL_count(DL *list, double v);
int SL_countArray(SL *list, String v);
int SL_countList(SL *list, CL *v);

////////////////////////////////////////////////////////////////////////////////
/// \brief Replace all list items with a given value
///
/// \param list The list to replace in
/// \param v    The value to replace with
///
/// \return false if it failed and true otherwise only in case of SL object otherwise no return
///
////////////////////////////////////////////////////////////////////////////////
void BL_fill(BL *list, bool v);
void CL_fill(CL *list, char v);
void IL_fill(IL *list, int v);
void DL_fill(DL *list, double v);
bool SL_fillArray(SL *list, String v);
bool SL_fillList(SL *list, CL *v);

////////////////////////////////////////////////////////////////////////////////
/// \brief Replace a given value with a new one in the whole list
///
/// \param list     The list to replace in
/// \param oldValue The value to replace
/// \param newValue The new value to replace with
///
/// \return false if it failed and true otherwise only in case of SL object otherwise no return
///
////////////////////////////////////////////////////////////////////////////////
void BL_replace(BL *list, bool oldValue, bool newValue);
void CL_replace(CL *list, char oldValue, char newValue);
void IL_replace(IL *list, int oldValue, int newValue);
void DL_replace(DL *list, double oldValue, double newValue);
bool SL_replaceArray(SL *list, String oldValue, String newValue);
bool SL_replaceList(SL *list, String oldValue, CL *newValue);

////////////////////////////////////////////////////////////////////////////////
/// \brief Print the list to the Console
///
/// \param list The list to print
///
////////////////////////////////////////////////////////////////////////////////
void BL_print(BL *list);
void CL_print(CL *list);
void IL_print(IL *list);
void DL_print(DL *list);
void SL_print(SL *list);

////////////////////////////////////////////////////////////////////////////////
/// \brief Call the callback function on each node of the list
///
/// \param list The list to call on
/// \param cb   The address of the callback function
///
////////////////////////////////////////////////////////////////////////////////
void BL_forEach(BL *list, void (*cb)(BL *, BN *, int));
void CL_forEach(CL *list, void (*cb)(CL *, CN *, int));
void IL_forEach(IL *list, void (*cb)(IL *, IN *, int));
void DL_forEach(DL *list, void (*cb)(DL *, DN *, int));
void SL_forEach(SL *list, void (*cb)(SL *, SN *, int));

////////////////////////////////////////////////////////////////////////////////
/// \brief Call the callback function on each node of the list and then returns a new list
///
/// \param list The list to call on
/// \param cb   The address of the callback function
///
/// \return The new list of the returned values from each time the callback runs
///
////////////////////////////////////////////////////////////////////////////////
BL * BL_map(BL *list, bool (*cb)(BL *, BN *, int));
CL * CL_map(CL *list, char (*cb)(CL *, CN *, int));
IL * IL_map(IL *list, int (*cb)(IL *, IN *, int));
DL * DL_map(DL *list, double (*cb)(DL *, DN *, int));
SL * SL_map(SL *list, CL * (*cb)(SL *, SN *, int));

////////////////////////////////////////////////////////////////////////////////
/// \brief Call the callback function on each node of the list and then returns a new filtered list
///
/// \param list The list to call on
/// \param cb   The address of the callback function
///
/// \return The new list of each node if the callback returns true
///
////////////////////////////////////////////////////////////////////////////////
BL * BL_filter(BL *list, bool (*cb)(BL *, BN *, int));
CL * CL_filter(CL *list, bool (*cb)(CL *, CN *, int));
IL * IL_filter(IL *list, bool (*cb)(IL *, IN *, int));
DL * DL_filter(DL *list, bool (*cb)(DL *, DN *, int));
SL * SL_filter(SL *list, bool (*cb)(SL *, SN *, int));

////////////////////////////////////////////////////////////////////////////////
/// \brief Call the callback function on each node of the list if it satisfies a certain condition
///
/// \param list The list to call on
/// \param cb   The address of the callback function
///
/// \return If all nodes satisfie the condition returns true, false otherwise
///
////////////////////////////////////////////////////////////////////////////////
bool BL_every(BL *list, bool (*cb)(BL *, BN *, int));
bool CL_every(CL *list, bool (*cb)(CL *, CN *, int));
bool IL_every(IL *list, bool (*cb)(IL *, IN *, int));
bool DL_every(DL *list, bool (*cb)(DL *, DN *, int));
bool SL_every(SL *list, bool (*cb)(SL *, SN *, int));

////////////////////////////////////////////////////////////////////////////////
/// \brief Split the CL object into a SL object depending on a separator(char)
///
/// \param charList List to split
/// \param sep      The separator
///
/// \return A new SL object
///
////////////////////////////////////////////////////////////////////////////////
static SL * CL_splitc(CL *charList, char sep);

////////////////////////////////////////////////////////////////////////////////
/// \brief Get a piece of a CL object as a String
///
/// \param charList The List to substr
/// \param start    The starting index
/// \param length   The length of the sub string
///
/// \return The sub string 
///
////////////////////////////////////////////////////////////////////////////////
static String _CL_substr(CL *charList, int start, int length);

////////////////////////////////////////////////////////////////////////////////
/// \brief Split the CL object into a SL object depending on a separator(String)
///
/// \param charList List to split
/// \param sep      The separator
///
/// \return A new SL object
///
////////////////////////////////////////////////////////////////////////////////
SL * CL_split(CL *charList, String sep);

////////////////////////////////////////////////////////////////////////////////
/// \brief Insert a given value between each two chars in the list
///
/// \param list The CL object to insert in
/// \param sep  The value to insert
///
/// \return false if it failed and true otherwise
///
////////////////////////////////////////////////////////////////////////////////
bool CL_join(CL *list, char sep);

#endif //STF_LISTS_H