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

#include "STF_Lists.h"

/*----------------######################################################################----------------*/
/*----------------#--***** -- **** -- **** --**    ----**    --******--******--******--#----------------*/
/*----------------#--******--******--******--**    ----**    --******--******--******--#----------------*/
/*----------------#--**  **--**  **--**  **--**    ----**    --  **  --**    --  **  --#----------------*/
/*----------------#--******--**  **--**  **--**    ----**    --  **  --******--  **  --#----------------*/
/*----------------#--******--**  **--**  **--**    ----**    --  **  --******--  **  --#----------------*/
/*----------------#--**  **--**  **--**  **--**    ----**    --  **  --    **--  **  --#----------------*/
/*----------------#--******--******--******--******----******--******--******--  **  --#----------------*/
/*----------------#--***** -- **** -- **** --******----******--******--******--  **  --#----------------*/
/*----------------######################################################################----------------*/

static BN * BN_create(bool v) {
  BN *boolNode = (BN *)malloc(sizeof(BN));
  if(boolNode == NULL) {
    return NULL;
  }
  boolNode->value = v;
  boolNode->next = NULL;
  return boolNode;
}

static BN * BL_getNode(BL *list, int index) {
  if(index < 0 || index >= list->size) {
    return NULL;
  }
  BN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(i == index) {
      return tmpNode;
    }
    tmpNode = tmpNode->next;
  }
}

static void _BL_sort(BL *list, bool isReversed) {
  BN *currentNode, *previousNode;
  bool difference;
  loopAgain:
    difference = false;
    currentNode = previousNode = list->start;
    for(int i = 0;i < list->size;i++) {
      currentNode = currentNode->next;
      if(currentNode != NULL && (isReversed ? previousNode->value < currentNode->value :
          previousNode->value > currentNode->value)) {
        bool v = currentNode->value;
        currentNode->value = previousNode->value;
        previousNode->value = v;
        difference = true;
      }
      previousNode = currentNode;
    }
  if(difference) {
    goto loopAgain;
  }
}

BL * BL_create() {
  BL *list = (BL *)malloc(sizeof(BL));
  if(list == NULL) {
    return NULL;
  }
  list->start = list->end = NULL;
  list->size = 0;
  return list;
}

bool BL_add(BL *list, bool v) {
  BN *boolNode = BN_create(v);
  if(boolNode == NULL) {
    return false;
  }
  if(list->size == 0) {
    list->start = list->end = boolNode;
  }else if(list->size == 1) {
    list->start->next = list->end = boolNode;
  }else {
    list->end->next = boolNode;
    list->end = list->end->next;
  }
  list->size++;
  return true;
}

bool BL_unshift(BL *list, bool v) {
  BN *boolNode = BN_create(v);
  if(boolNode == NULL) {
    return false;
  }
  if(list->size == 0) {
    list->start = list->end = boolNode;
  }else if(list->size == 1) {
    list->start = boolNode;
    list->start->next = list->end;
  }else {
    BN *tmpNode = list->start;
    list->start = boolNode;
    list->start->next = tmpNode;
  }
  list->size++;
  return true;
}

bool BL_pop(BL *list) {
  bool v = false;
  if(list->size > 2) {
    v = list->end->value;
    free(list->end);
    list->end = BL_getNode(list, list->size - 2);
    list->end->next = NULL;
    list->size--;
  }else if(list->size == 2) {
    v = list->end->value;
    free(list->end);
    list->start->next = list->end = NULL;
    list->size = 1;
  }else if(list->size == 1) {
    v = list->start->value;
    free(list->start);
    list->start = NULL;
    list->size = 0;
  }
  return v;
}

bool BL_shift(BL *list) {
  bool v = false;
  if(list->size > 1) {
    BN *tmpNode = list->start->next;
    v = list->start->value;
    free(list->start);
    list->start = tmpNode;
    list->size--;
  }else if(list->size == 1) {
    v = list->start->value;
    free(list->start);
    list->start = NULL;
    list->size = 0;
  }
  return v;
}

bool BL_insert(BL *list, bool v, int index) {
  if(index < 0 || index > list->size) {
    return false;
  }
  if(index == 0) {
    if(!BL_unshift(list, v)) return false;
  }else if(index == list->size) {
    if(!BL_add(list, v)) return false;
  }else {
    BN *previousNode = BL_getNode(list, index - 1);
    BN *currentNode = BN_create(v);
    if(currentNode == NULL) return false;
    currentNode->next = previousNode->next;
    previousNode->next = currentNode;
    list->size++;
  }
  return true;
}

bool BL_remove(BL *list, int index) {
  bool v = false;
  if(index >= 0 && index < list->size) {
    if(index == 0) {
      v = BL_shift(list);
    }else if(index == list->size - 1) {
      v = BL_pop(list);
    }else {
      BN *previousBN = BL_getNode(list, index - 1);
      BN *boolNode = previousBN->next;
      v = boolNode->value;
      previousBN->next = boolNode->next;
      free(boolNode);
      list->size--;
    }
  }
  return v;
}

void BL_clear(BL *list) {
  for(int i = 0, size = list->size;i < size;i++) {
    BL_shift(list);
  }
}

void BL_delete(BL *list) {
  BL_clear(list);
  free(list);
}

bool BL_set(BL *list, bool v, int index) {
  if(index >= 0 && index < list->size) {
    BN *tmpNode = list->start;
    for(int i = 0;i < list->size;i++) {
      if(i == index) {
        tmpNode->value = v;
        return true;
      }
      tmpNode = tmpNode->next;
    }
  }
  return false;
}

bool BL_get(BL *list, int index) {
  if(index < 0 || index >= list->size) {
    return false;
  }
  BN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(i == index) {
      return tmpNode->value;
    }
    tmpNode = tmpNode->next;
  }
}

bool * BL_toBoolArray(BL *list) {
  bool *array = (bool*)malloc(list->size * sizeof(bool));
  if(array == NULL) {
    return NULL;
  }
  BN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    array[i] = tmpNode->value;
    tmpNode = tmpNode->next;
  }
  return array;
}

void BL_sort(BL *list) {
  _BL_sort(list, false);  
}

void BL_rsort(BL *list) {
  _BL_sort(list, true);
}

BL * BL_createFrom(bool *array, int len) {
  BL *list = BL_create();
  if(list == NULL) {
    return NULL;
  }
  int i = 0;
  while(i < len) {
    if(!BL_add(list, array[i])) {
      BL_delete(list);
      return NULL;
    }
    i++;
  }
  return list;
}

BL * BL_copy(BL *list) {
  BL *listCopy = BL_create();
  if(listCopy == NULL) {
    return NULL;
  }
  BN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(!BL_add(listCopy, tmpNode->value)) {
      BL_delete(listCopy);
      return NULL;
    }
    tmpNode = tmpNode->next;
  }
  return listCopy;
}

bool BL_concatArray(BL *list, bool *array, int len) {
  int i = 0;
  while(i < len) {
    if(!BL_add(list, array[i])) {
      return false;
    }
    i++;
  }
  return true;
}

bool BL_concatList(BL *listA, BL *listB) {
  BN *tmpNode = listB->start;
  for(int i = 0;i < listB->size;i++) {
    if(!BL_add(listA, tmpNode->value)) {
      return false;
    }
    tmpNode = tmpNode->next;
  }
  return true;
}

bool BL_reverse(BL *list) {
  BL *tmpBL = BL_create();
  if(tmpBL == NULL) {
    return false;
  }
  BN *tmpNode = list->start;
  for(int i = 0;i < list->size; i++) {
    if(!BL_unshift(tmpBL, tmpNode->value)) {
      BL_delete(tmpBL);
      return false;
    }
    tmpNode = tmpNode->next;
  }
  BL_clear(list);
  list->start = tmpBL->start;
  list->end = tmpBL->end;
  list->size = tmpBL->size;
  free(tmpBL);
  return true;
}

BL * BL_slice(BL *list, int start, int end) {
  if(start >= list->size || start < 0 || end <= start) {
    return NULL;
  }
  BL *listSub = BL_create();
  if(listSub == NULL) {
    return NULL;
  }
  BN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(i >= start && i < end) {
      if(!BL_add(listSub, tmpNode->value)) {
        BL_delete(listSub);
        return NULL;
      }
    }
    if(i == end - 1) {
      return listSub;
    }
    tmpNode = tmpNode->next;
  }
  return listSub;
}

BL * BL_sub(BL *list, int start, int length) {
  if(start >= list->size || start < 0 || length < 1) {
    return NULL;
  }
  BL *listSub = BL_create();
  if(listSub == NULL) {
    return NULL;
  }
  BN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(i >= start && i < start + length) {
      if(!BL_add(listSub, tmpNode->value)) {
        BL_delete(listSub);
        return NULL;
      }
    }
    if(i > start + length - 1) {
      return listSub;
    }
    tmpNode = tmpNode->next;
  }
  return listSub;
}

bool BL_startsWith(BL *list, bool v) {
  return list->size > 0 && list->start->value == v;
}

bool BL_endsWith(BL *list, bool v) {
  return list->size == 1 && list->start->value == v ||
    list->size > 0 && list->end->value == v;
}

bool BL_contains(BL *list, bool v) {
  BN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(tmpNode->value == v) {
      return true;
    }
    tmpNode = tmpNode->next;
  }
  return false;
}

bool BL_isEmpty(BL *list) {
  return list->size == 0 ? 1 : 0;
}

int BL_compare(BL *listA, BL *listB) {
  int len = listA->size > listB->size ? listB->size : listA->size;
  BN *tmpNodeA = listA->start;
  BN *tmpNodeB = listB->start;
  for(int i = 0;i < len;i++) {
    if(tmpNodeA->value < tmpNodeB->value) {
      return 1;
    }else if(tmpNodeA->value > tmpNodeB->value) {
      return -1;
    }
    tmpNodeA = tmpNodeA->next;
    tmpNodeB = tmpNodeB->next;
  }
  if(listA->size > listB->size) return -1;
  else if(listA->size < listB->size) return 1;
  return 0;
}

bool BL_equalsList(BL *listA, BL *listB) {
  return BL_compare(listA, listB) == 0;
}

bool BL_equalsArray(BL *list, bool *array, int len) {
  if(list->size != len) {
    return false;
  }
  BN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(tmpNode->value != array[i]) {
      return false;
    }
    tmpNode = tmpNode->next;
  }
  return true;
}

bool BL_isSame(BL *listA, BL *listB) {
  return listA == listB;
}

int BL_indexOf(BL *list, bool v) {
  BN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(tmpNode->value == v) {
      return i;
    }
    tmpNode = tmpNode->next;
  }
  return -1;
}

int BL_lastIndexOf(BL *list, bool v) {
  BN *tmpNode = list->start;
  int index = -1;
  for(int i = 0;i < list->size;i++) {
    if(tmpNode->value == v) {
      index = i;
    }
    tmpNode = tmpNode->next;
  }
  return index;
}

int BL_count(BL *list, bool v) {
  BN *tmpNode = list->start;
  int n = 0;
  for(int i = 0;i < list->size;i++) {
    if(tmpNode->value == v) {
      n++;
    }
    tmpNode = tmpNode->next;
  }
  return n;
}

void BL_fill(BL *list, bool v) {
  BN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    tmpNode->value = v;
    tmpNode = tmpNode->next;
  }
}

void BL_replace(BL *list, bool oldValue, bool newValue) {
  BN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(tmpNode->value == oldValue) {
      tmpNode->value = newValue;
    }
    tmpNode = tmpNode->next;
  }
}

void BL_print(BL *list) {
  BN *tmpNode = list->start;
  printf("{");
  for(int i = 0;i < list->size;i++) {
    printf("%s", tmpNode->value ? "true" : "false");
    tmpNode = tmpNode->next;
    i != list->size - 1 && printf(", ");
  }
  printf("}");
}

void BL_forEach(BL *list, void (*cb)(BL *, BN *, int)) {
  BN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    cb(list, tmpNode, i);
    tmpNode = tmpNode->next;
  }
}

BL * BL_map(BL *list, bool (*cb)(BL *, BN *, int)) {
  BL *newBL = BL_create();
  if(newBL == NULL) {
    return NULL;
  }  
  BN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(!BL_add(newBL, cb(list, tmpNode, i))) {
      BL_delete(newBL);
      return NULL;
    }
    tmpNode = tmpNode->next;
  }
  return newBL;
}

BL * BL_filter(BL *list, bool (*cb)(BL *, BN *, int)) {
  BL *newBL = BL_create();
  if(newBL == NULL) {
    return NULL;
  }
  BN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(!cb(list, tmpNode, i)) {
      tmpNode = tmpNode->next;
      continue;
    }
    if(!BL_add(newBL, tmpNode->value)) {
      BL_delete(newBL);
      return NULL;
    }
    tmpNode = tmpNode->next;
  }
  return newBL;
}

bool BL_every(BL *list, bool (*cb)(BL *, BN *, int)) {
  BN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(!cb(list, tmpNode, i)) {
      return false;
    }
    tmpNode = tmpNode->next;
  }
  return true;
}

/*----------------######################################################################----------------*/
/*----------------#-- **** --**  **-- **** --******----**    --******--******--******--#----------------*/
/*----------------#--******--**  **--******--******----**    --******--******--******--#----------------*/
/*----------------#--**    --**  **--**  **--**  **----**    --  **  --**    --  **  --#----------------*/
/*----------------#--**    --******--**  **--******----**    --  **  --******--  **  --#----------------*/
/*----------------#--**    --******--******--****  ----**    --  **  --******--  **  --#----------------*/
/*----------------#--**    --**  **--******--******----**    --  **  --    **--  **  --#----------------*/
/*----------------#--******--**  **--**  **--**  **----******--******--******--  **  --#----------------*/
/*----------------#-- **** --**  **--**  **--**  **----******--******--******--  **  --#----------------*/
/*----------------######################################################################----------------*/

static CN * CN_create(char v) {
  CN *charNode = (CN *)malloc(sizeof(CN));
  if(charNode == NULL) {
    return NULL;
  }
  charNode->value = v;
  charNode->next = NULL;
  return charNode;
}

static CN * CL_getNode(CL * list, int index) {
  if(index < 0 || index >= list->size) {
    return NULL;
  }
  CN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(i == index) {
      return tmpNode;
    }
    tmpNode = tmpNode->next;
  }
}

static void _CL_sort(CL *list, bool isReversed) {
  CN *currentNode, *previousNode;
  bool difference;
  loopAgain:
    difference = false;
    currentNode = previousNode = list->start;
    for(int i = 0;i < list->size;i++) {
      currentNode = currentNode->next;
      if(currentNode != NULL && (isReversed ? previousNode->value < currentNode->value :
          previousNode->value > currentNode->value)) {
        char v = currentNode->value;
        currentNode->value = previousNode->value;
        previousNode->value = v;
        difference = true;
      }
      previousNode = currentNode;
    }
  if(difference) {
    goto loopAgain;
  }
}

CL * CL_create() {
  CL *list = (CL *)malloc(sizeof(CL));
  if(list == NULL) {
    return NULL;
  }
  list->start = list->end = NULL;
  list->size = 0;
  return list;
}

bool CL_add(CL *list, char v) {
  CN *charNode = CN_create(v);
  if(charNode == NULL) {
    return false;
  }
  if(list->size == 0) {
    list->start = list->end = charNode;
  }else if(list->size == 1) {
    list->start->next = list->end = charNode;
  }else {
    list->end->next = charNode;
    list->end = list->end->next;
  }
  list->size++;
  return true;
}

bool CL_unshift(CL * list, char v) {
  CN *charNode = CN_create(v);
  if(charNode == NULL) {
    return false;
  }
  if(list->size == 0) {
    list->start = list->end = charNode;
  }else if(list->size == 1) {
    list->start = charNode;
    list->start->next = list->end;
  }else {
    CN *tmpNode = list->start;
    list->start = charNode;
    list->start->next = tmpNode;
  }
  list->size++;
  return true;
}

char CL_pop(CL *list) {
  char v = '\0';
  if(list->size > 2) {
    v = list->end->value;
    free(list->end);
    list->end = CL_getNode(list, list->size - 2);
    list->end->next = NULL;
    list->size--;
  }else if(list->size == 2) {
    v = list->end->value;
    free(list->end);
    list->start->next = list->end = NULL;
    list->size = 1;
  }else if(list->size == 1) {
    v = list->start->value;
    free(list->start);
    list->start = NULL;
    list->size = 0;
  }
  return v;
}

char CL_shift(CL * list) {
  char v = '\0';
  if(list->size > 1) {
    CN *tmpNode = list->start->next;
    v = list->start->value;
    free(list->start);
    list->start = tmpNode;
    list->size--;
  }else if(list->size == 1) {
    v = list->start->value;
    free(list->start);
    list->start = NULL;
    list->size = 0;
  }
  return v;
}

bool CL_insert(CL *list, char v, int index) {
  if(index < 0 || index > list->size) {
    return false;
  }
  if(index == 0) {
    if(!CL_unshift(list, v)) return false;
  }else if(index == list->size) {
    if(!CL_add(list, v)) return false;
  }else {
    CN *previousNode = CL_getNode(list, index - 1);
    CN *currentNode = CN_create(v);
    if(currentNode == NULL) return false;
    currentNode->next = previousNode->next;
    previousNode->next = currentNode;
    list->size++;
  }
  return true;
}

char CL_remove(CL *list, int index) {
  char v = '\0';
  if(index >= 0 && index < list->size) {
    if(index == 0) {
      v = CL_shift(list);
    }else if(index == list->size - 1) {
      v = CL_pop(list);
    }else {
      CN *previousCN = CL_getNode(list, index - 1);
      CN *charNode = previousCN->next;
      v = charNode->value;
      previousCN->next = charNode->next;
      free(charNode);
      list->size--;
    }
  }
  return v;
}

void CL_clear(CL *list) {
  for(int i = 0, size = list->size;i < size;i++) {
    CL_shift(list);
  }
}

void CL_delete(CL *list) {
  CL_clear(list);
  free(list);
}

bool CL_set(CL * list, char v, int index) {
  if(index >= 0 && index < list->size) {
    CN *tmpNode = list->start;
    for(int i = 0;i < list->size;i++) {
      if(i == index) {
        tmpNode->value = v;
        return true;
      }
      tmpNode = tmpNode->next;
    }
  }
  return false;
}

char CL_get(CL * list, int index) {
  if(index < 0 || index >= list->size) {
    return '\0';
  }
  CN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(i == index) {
      return tmpNode->value;
    }
    tmpNode = tmpNode->next;
  }
}

String CL_toCharArray(CL *list) {
  String array = (String)malloc(list->size + 1);
  if(array == NULL) {
    return NULL;
  }
  CN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    array[i] = tmpNode->value;
    tmpNode = tmpNode->next;
  }
  array[list->size] = '\0';
  return array;
}

void CL_toLowerCase(CL *list) {
  CN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    tmpNode->value = tolower(tmpNode->value);
    tmpNode = tmpNode->next;
  }
}

void CL_toUpperCase(CL *list) {
  CN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    tmpNode->value = toupper(tmpNode->value);
    tmpNode = tmpNode->next;
  }
}

void CL_capitalize(CL *list) {
  if(list->size > 0) {
    list->start->value = toupper(list->start->value);
  }
}

void CL_sort(CL *list) {
  _CL_sort(list, false);
}

void CL_rsort(CL *list) {
  _CL_sort(list, true);
}

CL * CL_createFrom(String array) {
  CL *list = CL_create();
  if(list == NULL) {
    return NULL;
  }
  int i = 0;
  while(array[i] != '\0') {
    if(!CL_add(list, array[i])) {
      CL_delete(list);
      return NULL;
    }
    i++;
  }
  return list;
}

CL * CL_copy(CL *list) {
  CL *listCopy = CL_create();
  if(listCopy == NULL) {
    return NULL;
  }
  CN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(!CL_add(listCopy, tmpNode->value)) {
      CL_delete(listCopy);
      return NULL;
    }
    tmpNode = tmpNode->next;
  }
  return listCopy;
}

bool CL_concatArray(CL *list, String array) {
  int i = 0;
  while(array[i] != '\0') {
    if(!CL_add(list, array[i])) {
      return false;
    }
    i++;
  }
  return true;
}

bool CL_concatList(CL *listA, CL *listB) {
  CN *tmpNode = listB->start;
  for(int i = 0;i < listB->size;i++) {
    if(!CL_add(listA, tmpNode->value)) {
      return false;
    }
    tmpNode = tmpNode->next;
  }
  return true;
}

bool CL_reverse(CL *list) {
  CL *tmpCL = CL_create();
  if(tmpCL == NULL) {
    return false;
  }
  CN *tmpNode = list->start;
  for(int i = 0;i < list->size; i++) {
    if(!CL_unshift(tmpCL, tmpNode->value)) {
      CL_delete(tmpCL);
      return false;
    }
    tmpNode = tmpNode->next;
  }
  CL_clear(list);
  list->start = tmpCL->start;
  list->end = tmpCL->end;
  list->size = tmpCL->size;
  free(tmpCL);
  return true;
}

CL * CL_slice(CL *list, int start, int end) {
  if(start >= list->size || start < 0 || end <= start) {
    return NULL;
  }
  CL *listSub = CL_create();
  if(listSub == NULL) {
    return NULL;
  }
  CN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(i >= start && i < end) {
      if(!CL_add(listSub, tmpNode->value)) {
        CL_delete(listSub);
        return NULL;
      }
    }
    if(i == end - 1) {
      return listSub;
    }
    tmpNode = tmpNode->next;
  }
  return listSub;
}

CL * CL_sub(CL *list, int start, int length) {
  if(start >= list->size || start < 0 || length < 1) {
    return NULL;
  }
  CL *listSub = CL_create();
  if(listSub == NULL) {
    return NULL;
  }
  CN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(i >= start && i < start + length) {
      if(!CL_add(listSub, tmpNode->value)) {
        CL_delete(listSub);
        return NULL;
      }
    }
    if(i > start + length - 1) {
      return listSub;
    }
    tmpNode = tmpNode->next;
  }
  return listSub;
}

bool CL_startsWith(CL *list, char v) {
  return list->size > 0 && list->start->value == v;
}

bool CL_endsWith(CL *list, char v) {
  return list->size == 1 && list->start->value == v || list->size > 0 && list->end->value == v;
}

bool CL_contains(CL * list, char v) {
  CN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(tmpNode->value == v) {
      return true;
    }
    tmpNode = tmpNode->next;
  }
  return false;
}

bool CL_isEmpty(CL *list) {
  return list->size == 0 ? 1 : 0;
}

int CL_compare(CL *listA, CL *listB) {
  int len = listA->size > listB->size ? listB->size : listA->size;
  CN *tmpNodeA = listA->start;
  CN *tmpNodeB = listB->start;
  for(int i = 0;i < len;i++) {
    if(tmpNodeA->value < tmpNodeB->value) {
      return 1;
    }else if(tmpNodeA->value > tmpNodeB->value) {
      return -1;
    }
    tmpNodeA = tmpNodeA->next;
    tmpNodeB = tmpNodeB->next;
  }
  if(listA->size > listB->size) return -1;
  else if(listA->size < listB->size) return 1;
  return 0;
}

bool CL_equalsList(CL *listA, CL *listB) {
  return CL_compare(listA, listB) == 0;
}

bool CL_equalsArray(CL *list, String array) {
  if(list->size != strlen(array)) {
    return false;
  }
  CN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(tmpNode->value != array[i]) {
      return false;
    }
    tmpNode = tmpNode->next;
  }
  return true;
}

bool CL_isSame(CL *listA, CL *listB) {
  return listA == listB;
}

int CL_indexOf(CL * list, char v) {
  CN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(tmpNode->value == v) {
      return i;
    }
    tmpNode = tmpNode->next;
  }
  return -1;
}

int CL_lastIndexOf(CL * list, char v) {
  CN *tmpNode = list->start;
  int index = -1;
  for(int i = 0;i < list->size;i++) {
    if(tmpNode->value == v) {
      index = i;
    }
    tmpNode = tmpNode->next;
  }
  return index;
}

int CL_count(CL *list, char v) {
  CN *tmpNode = list->start;
  int n = 0;
  for(int i = 0;i < list->size;i++) {
    if(tmpNode->value == v) {
      n++;
    }
    tmpNode = tmpNode->next;
  }
  return n;
}

void CL_fill(CL *list, char v) {
  CN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    tmpNode->value = v;
    tmpNode = tmpNode->next;
  }
}

bool CL_join(CL *list, char sep) {
  String array = CL_toCharArray(list);
  int len = list->size;
  if(array == NULL) {
    return false;
  }
  CL_clear(list);
  for(int i = 0;i < len;i++) {
    if(!CL_add(list, array[i]) || !CL_add(list, sep)) {
      return false;
    }
  }
  CL_pop(list);
  return true;
}

void CL_replace(CL *list, char oldValue, char newValue) {
  CN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(tmpNode->value == oldValue) {
      tmpNode->value = newValue;
    }
    tmpNode = tmpNode->next;
  }
}

void CL_print(CL *list) {
  CN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    printf("%c", tmpNode->value);
    tmpNode = tmpNode->next;
  }
}

void CL_forEach(CL *list, void (*cb)(CL *, CN *, int)) {
  CN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    cb(list, tmpNode, i);
    tmpNode = tmpNode->next;
  }
}

CL * CL_map(CL *list, char (*cb)(CL *, CN *, int)) {
  CL *newCL = CL_create();
  if(newCL == NULL) {
    return NULL;
  }  
  CN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(!CL_add(newCL, cb(list, tmpNode, i))) {
      CL_delete(newCL);
      return NULL;
    }
    tmpNode = tmpNode->next;
  }
  return newCL;
}

CL * CL_filter(CL *list, bool (*cb)(CL *, CN *, int)) {
  CL *newCL = CL_create();
  if(newCL == NULL) {
    return NULL;
  }
  CN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(!cb(list, tmpNode, i)) {
      tmpNode = tmpNode->next;
      continue;
    }
    if(!CL_add(newCL, tmpNode->value)) {
      CL_delete(newCL);
      return NULL;
    }
    tmpNode = tmpNode->next;
  }
  return newCL;
}

bool CL_every(CL *list, bool (*cb)(CL *, CN *, int)) {
  CN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(!cb(list, tmpNode, i)) {
      return false;
    }
    tmpNode = tmpNode->next;
  }
  return true;
}

/*--------------------##############################################################--------------------*/
/*--------------------#--******--**  **--******----**    --******--******--******--#--------------------*/
/*--------------------#--******--**  **--******----**    --******--******--******--#--------------------*/
/*--------------------#--  **  --*** **--  **  ----**    --  **  --**    --  **  --#--------------------*/
/*--------------------#--  **  --******--  **  ----**    --  **  --******--  **  --#--------------------*/
/*--------------------#--  **  --******--  **  ----**    --  **  --******--  **  --#--------------------*/
/*--------------------#--  **  --** ***--  **  ----**    --  **  --    **--  **  --#--------------------*/
/*--------------------#--******--**  **--  **  ----******--******--******--  **  --#--------------------*/
/*--------------------#--******--**  **----**------******--******--******--  **  --#--------------------*/
/*--------------------##############################################################--------------------*/

static IN * IN_create(int v) {
  IN *intNode = (IN *)malloc(sizeof(IN));
  if(intNode == NULL) {
    return NULL;
  }
  intNode->value = v;
  intNode->next = NULL;
  return intNode;
}

static IN * IL_getNode(IL *list, int index) {
  if(index < 0 || index >= list->size) {
    return NULL;
  }
  IN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(i == index) {
      return tmpNode;
    }
    tmpNode = tmpNode->next;
  }
}

static void _IL_sort(IL *list, bool isReversed) {
  IN *currentNode, *previousNode;
  bool difference;
  loopAgain:
    difference = false;
    currentNode = previousNode = list->start;
    for(int i = 0;i < list->size;i++) {
      currentNode = currentNode->next;
      if(currentNode != NULL && (isReversed ? previousNode->value < currentNode->value :
          previousNode->value > currentNode->value)) {
        int v = currentNode->value;
        currentNode->value = previousNode->value;
        previousNode->value = v;
        difference = true;
      }
      previousNode = currentNode;
    }
  if(difference) {
    goto loopAgain;
  }
}

IL * IL_create() {
  IL *list = (IL *)malloc(sizeof(IL));
  if(list == NULL) {
    return NULL;
  }
  list->start = list->end = NULL;
  list->size = 0;
  return list;
}


bool IL_add(IL *list, int v) {
  IN *intNode = IN_create(v);
  if(intNode == NULL) {
    return false;
  }
  if(list->size == 0) {
    list->start = list->end = intNode;
  }else if(list->size == 1) {
    list->start->next = list->end = intNode;
  }else {
    list->end->next = intNode;
    list->end = list->end->next;
  }
  list->size++;
  return true;
}

bool IL_unshift(IL *list, int v) {
  IN *intNode = IN_create(v);
  if(intNode == NULL) {
    return false;
  }
  if(list->size == 0) {
    list->start = list->end = intNode;
  }else if(list->size == 1) {
    list->start = intNode;
    list->start->next = list->end;
  }else {
    IN *tmpNode = list->start;
    list->start = intNode;
    list->start->next = tmpNode;
  }
  list->size++;
  return true;
}

int IL_pop(IL *list) {
  int v = 0;
  if(list->size > 2) {
    v = list->end->value;
    free(list->end);
    list->end = IL_getNode(list, list->size - 2);
    list->end->next = NULL;
    list->size--;
  }else if(list->size == 2) {
    v = list->end->value;
    free(list->end);
    list->start->next = list->end = NULL;
    list->size = 1;
  }else if(list->size == 1) {
    v = list->start->value;
    free(list->start);
    list->start = NULL;
    list->size = 0;
  }
  return v;
}

int IL_shift(IL * list) {
  int v = 0;
  if(list->size > 1) {
    IN *tmpNode = list->start->next;
    v = list->start->value;
    free(list->start);
    list->start = tmpNode;
    list->size--;
  }else if(list->size == 1) {
    v = list->start->value;
    free(list->start);
    list->start = NULL;
    list->size = 0;
  }
  return v;
}

bool IL_insert(IL *list, int v, int index) {
  if(index < 0 || index > list->size) {
    return false;
  }
  if(index == 0) {
    if(!IL_unshift(list, v)) return false;
  }else if(index == list->size) {
    if(!IL_add(list, v)) return false;
  }else {
    IN *previousNode = IL_getNode(list, index - 1);
    IN *currentNode = IN_create(v);
    if(currentNode == NULL) return false;
    currentNode->next = previousNode->next;
    previousNode->next = currentNode;
    list->size++;
  }
  return true;
}

int IL_remove(IL *list, int index) {
  int v = 0;
  if(index >= 0 && index < list->size) {
    if(index == 0) {
      v = IL_shift(list);
    }else if(index == list->size - 1) {
      v = IL_pop(list);
    }else {
      IN *previousIN = IL_getNode(list, index - 1);
      IN *intNode = previousIN->next;
      v = intNode->value;
      previousIN->next = intNode->next;
      free(intNode);
      list->size--;
    }
  }
  return v;
}

void IL_clear(IL *list) {
  for(int i = 0, size = list->size;i < size;i++) {
    IL_shift(list);
  }
}

void IL_delete(IL *list) {
  IL_clear(list);
  free(list);
}

bool IL_set(IL * list, int v, int index) {
  if(index >= 0 && index < list->size) {
    IN *tmpNode = list->start;
    for(int i = 0;i < list->size;i++) {
      if(i == index) {
        tmpNode->value = v;
        return true;
      }
      tmpNode = tmpNode->next;
    }
  }
  return false;
}

int IL_get(IL * list, int index) {
  if(index < 0 || index >= list->size) {
    return 0;
  }
  IN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(i == index) {
      return tmpNode->value;
    }
    tmpNode = tmpNode->next;
  }
}

int * IL_toIntArray(IL *list) {
  int *array = (int*)malloc(list->size * sizeof(int));
  if(array == NULL) {
    return NULL;
  }
  IN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    array[i] = tmpNode->value;
    tmpNode = tmpNode->next;
  }
  return array;
}

void IL_sort(IL *list) {
  _IL_sort(list, false);
}

void IL_rsort(IL *list) {
  _IL_sort(list, true);
}

IL * IL_createFrom(int *array, int len) {
  IL *list = IL_create();
  if(list == NULL) {
    return NULL;
  }
  int i = 0;
  while(i < len) {
    if(!IL_add(list, array[i])) {
      IL_delete(list);
      return NULL;
    }
    i++;
  }
  return list;
}

IL * IL_copy(IL *list) {
  IL *listCopy = IL_create();
  if(listCopy == NULL) {
    return NULL;
  }
  IN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(!IL_add(listCopy, tmpNode->value)) {
      IL_delete(listCopy);
      return NULL;
    }
    tmpNode = tmpNode->next;
  }
  return listCopy;
}

bool IL_concatArray(IL *list, int *array, int len) {
  int i = 0;
  while(i < len) {
    if(!IL_add(list, array[i])) {
      return false;
    }
    i++;
  }
  return true;
}

bool IL_concatList(IL *listA, IL *listB) {
  IN *tmpNode = listB->start;
  for(int i = 0;i < listB->size;i++) {
    if(!IL_add(listA, tmpNode->value)) {
      return false;
    }
    tmpNode = tmpNode->next;
  }
  return true;
}

bool IL_reverse(IL *list) {
  IL *tmpIL = IL_create();
  if(tmpIL == NULL) {
    return false;
  }
  IN *tmpNode = list->start;
  for(int i = 0;i < list->size; i++) {
    if(!IL_unshift(tmpIL, tmpNode->value)) {
      IL_delete(tmpIL);
      return false;
    }
    tmpNode = tmpNode->next;
  }
  IL_clear(list);
  list->start = tmpIL->start;
  list->end = tmpIL->end;
  list->size = tmpIL->size;
  free(tmpIL);
  return true;
}

IL * IL_slice(IL *list, int start, int end) {
  if(start >= list->size || start < 0 || end <= start) {
    return NULL;
  }
  IL *listSub = IL_create();
  if(listSub == NULL) {
    return NULL;
  }
  IN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(i >= start && i < end) {
      if(!IL_add(listSub, tmpNode->value)) {
        IL_delete(listSub);
        return NULL;
      }
    }
    if(i == end - 1) {
      return listSub;
    }
    tmpNode = tmpNode->next;
  }
  return listSub;
}

IL * IL_sub(IL *list, int start, int length) {
  if(start >= list->size || start < 0 || length < 1) {
    return NULL;
  }
  IL *listSub = IL_create();
  if(listSub == NULL) {
    return NULL;
  }
  IN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(i >= start && i < start + length) {
      if(!IL_add(listSub, tmpNode->value)) {
        IL_delete(listSub);
        return NULL;
      }
    }
    if(i > start + length - 1) {
      return listSub;
    }
    tmpNode = tmpNode->next;
  }
  return listSub;
}

bool IL_startsWith(IL *list, int v) {
  return list->size > 0 && list->start->value == v;
}

bool IL_endsWith(IL *list, int v) {
  return list->size == 1 && list->start->value == v ||
    list->size > 0 && list->end->value == v;
}

bool IL_contains(IL * list, int v) {
  IN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(tmpNode->value == v) {
      return true;
    }
    tmpNode = tmpNode->next;
  }
  return false;
}

bool IL_isEmpty(IL *list) {
  return list->size == 0 ? 1 : 0;
}

int IL_compare(IL *listA, IL *listB) {
  int len = listA->size > listB->size ? listB->size : listA->size;
  IN *tmpNodeA = listA->start;
  IN *tmpNodeB = listB->start;
  for(int i = 0;i < len;i++) {
    if(tmpNodeA->value < tmpNodeB->value) {
      return 1;
    }else if(tmpNodeA->value > tmpNodeB->value) {
      return -1;
    }
    tmpNodeA = tmpNodeA->next;
    tmpNodeB = tmpNodeB->next;
  }
  if(listA->size > listB->size) return -1;
  else if(listA->size < listB->size) return 1;
  return 0;
}

bool IL_equalsList(IL *listA, IL *listB) {
  return IL_compare(listA, listB) == 0;
}

bool IL_equalsArray(IL *list, int *array, int len) {
  if(list->size != len) {
    return false;
  }
  IN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(tmpNode->value != array[i]) {
      return false;
    }
    tmpNode = tmpNode->next;
  }
  return true;
}

bool IL_isSame(IL *listA, IL *listB) {
  return listA == listB;
}

int IL_indexOf(IL * list, int v) {
  IN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(tmpNode->value == v) {
      return i;
    }
    tmpNode = tmpNode->next;
  }
  return -1;
}

int IL_lastIndexOf(IL * list, int v) {
  IN *tmpNode = list->start;
  int index = -1;
  for(int i = 0;i < list->size;i++) {
    if(tmpNode->value == v) {
      index = i;
    }
    tmpNode = tmpNode->next;
  }
  return index;
}

int IL_count(IL *list, int v) {
  IN *tmpNode = list->start;
  int n = 0;
  for(int i = 0;i < list->size;i++) {
    if(tmpNode->value == v) {
      n++;
    }
    tmpNode = tmpNode->next;
  }
  return n;
}

void IL_fill(IL *list, int v) {
  IN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    tmpNode->value = v;
    tmpNode = tmpNode->next;
  }
}

void IL_replace(IL *list, int oldValue, int newValue) {
  IN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(tmpNode->value == oldValue) {
      tmpNode->value = newValue;
    }
    tmpNode = tmpNode->next;
  }
}

void IL_print(IL *list) {
  IN *tmpNode = list->start;
  printf("{");
  for(int i = 0;i < list->size;i++) {
    printf("%d", tmpNode->value);
    tmpNode = tmpNode->next;
    i != list->size - 1 && printf(", ");
  }
  printf("}");
}

void IL_forEach(IL *list, void (*cb)(IL *, IN *, int)) {
  IN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    cb(list, tmpNode, i);
    tmpNode = tmpNode->next;
  }
}

IL * IL_map(IL *list, int (*cb)(IL *, IN *, int)) {
  IL *newIL = IL_create();
  if(newIL == NULL) {
    return NULL;
  }  
  IN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(!IL_add(newIL, cb(list, tmpNode, i))) {
      IL_delete(newIL);
      return NULL;
    }
    tmpNode = tmpNode->next;
  }
  return newIL;
}

IL * IL_filter(IL *list, bool (*cb)(IL *, IN *, int)) {
  IL *newIL = IL_create();
  if(newIL == NULL) {
    return NULL;
  }
  IN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(!cb(list, tmpNode, i)) {
      tmpNode = tmpNode->next;
      continue;
    }
    if(!IL_add(newIL, tmpNode->value)) {
      IL_delete(newIL);
      return NULL;
    }
    tmpNode = tmpNode->next;
  }
  return newIL;
}

bool IL_every(IL *list, bool (*cb)(IL *, IN *, int)) {
  IN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(!cb(list, tmpNode, i)) {
      return false;
    }
    tmpNode = tmpNode->next;
  }
  return true;
}

/*--------######################################################################################--------*/
/*--------#--***   -- **** --**  **--***** --**    --******----**    --******--******--******--#--------*/
/*--------#--***** --******--**  **--******--**    --******----**    --******--******--******--#--------*/
/*--------#--** ***--**  **--**  **--**  **--**    --**    ----**    --  **  --**    --  **  --#--------*/
/*--------#--**  **--**  **--**  **--******--**    --***** ----**    --  **  --******--  **  --#--------*/
/*--------#--**  **--**  **--**  **--******--**    --***** ----**    --  **  --******--  **  --#--------*/
/*--------#--**  **--**  **--**  **--**  **--**    --**    ----**    --  **  --    **--  **  --#--------*/
/*--------#--******--******--******--******--******--******----******--******--******--  **  --#--------*/
/*--------#--***** -- **** --******--***** --******--******----******--******--******--  **  --#--------*/
/*--------######################################################################################--------*/

static DN * DN_create(double v) {
  DN *doubleNode = (DN *)malloc(sizeof(DN));
  if(doubleNode == NULL) {
    return NULL;
  }
  doubleNode->value = v;
  doubleNode->next = NULL;
  return doubleNode;
}

static DN * DL_getNode(DL * list, int index) {
  if(index < 0 || index >= list->size) {
    return NULL;
  }
  DN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(i == index) {
      return tmpNode;
    }
    tmpNode = tmpNode->next;
  }
}

static void _DL_sort(DL *list, bool isReversed) {
  DN *currentNode, *previousNode;
  bool difference;
  loopAgain:
    difference = false;
    currentNode = previousNode = list->start;
    for(int i = 0;i < list->size;i++) {
      currentNode = currentNode->next;
      if(currentNode != NULL && (isReversed ? previousNode->value < currentNode->value :
          previousNode->value > currentNode->value)) {
        double v = currentNode->value;
        currentNode->value = previousNode->value;
        previousNode->value = v;
        difference = true;
      }
      previousNode = currentNode;
    }
  if(difference) {
    goto loopAgain;
  }
}

DL * DL_create() {
  DL *list = (DL *)malloc(sizeof(DL));
  if(list == NULL) {
    return NULL;
  }
  list->start = list->end = NULL;
  list->size = 0;
  return list;
}

bool DL_add(DL *list, double v) {
  DN *doubleNode = DN_create(v);
  if(doubleNode == NULL) {
    return false;
  }
  if(list->size == 0) {
    list->start = list->end = doubleNode;
  }else if(list->size == 1) {
    list->start->next = list->end = doubleNode;
  }else {
    list->end->next = doubleNode;
    list->end = list->end->next;
  }
  list->size++;
  return true;
}

bool DL_unshift(DL * list, double v) {
  DN *doubleNode = DN_create(v);
  if(doubleNode == NULL) {
    return false;
  }
  if(list->size == 0) {
    list->start = list->end = doubleNode;
  }else if(list->size == 1) {
    list->start = doubleNode;
    list->start->next = list->end;
  }else {
    DN *tmpNode = list->start;
    list->start = doubleNode;
    list->start->next = tmpNode;
  }
  list->size++;
  return true;
}

double DL_pop(DL *list) {
  double v = 0;
  if(list->size > 2) {
    v = list->end->value;
    free(list->end);
    list->end = DL_getNode(list, list->size - 2);
    list->end->next = NULL;
    list->size--;
  }else if(list->size == 2) {
    v = list->end->value;
    free(list->end);
    list->start->next = list->end = NULL;
    list->size = 1;
  }else if(list->size == 1) {
    v = list->start->value;
    free(list->start);
    list->start = NULL;
    list->size = 0;
  }
  return v;
}

double DL_shift(DL * list) {
  double v = 0;
  if(list->size > 1) {
    DN *tmpNode = list->start->next;
    v = list->start->value;
    free(list->start);
    list->start = tmpNode;
    list->size--;
  }else if(list->size == 1) {
    v = list->start->value;
    free(list->start);
    list->start = NULL;
    list->size = 0;
  }
  return v;
}

bool DL_insert(DL *list, double v, int index) {
  if(index < 0 || index > list->size) {
    return false;
  }
  if(index == 0) {
    if(!DL_unshift(list, v)) return false;
  }else if(index == list->size) {
    if(!DL_add(list, v)) return false;
  }else {
    DN *previousNode = DL_getNode(list, index - 1);
    DN *currentNode = DN_create(v);
    if(currentNode == NULL) return false;
    currentNode->next = previousNode->next;
    previousNode->next = currentNode;
    list->size++;
  }
  return true;
}

double DL_remove(DL *list, int index) {
  double v = 0;
  if(index >= 0 && index < list->size) {
    if(index == 0) {
      v = DL_shift(list);
    }else if(index == list->size - 1) {
      v = DL_pop(list);
    }else {
      DN *previousDN = DL_getNode(list, index - 1);
      DN *doubleNode = previousDN->next;
      v = doubleNode->value;
      previousDN->next = doubleNode->next;
      free(doubleNode);
      list->size--;
    }
  }
  return v;
}

void DL_clear(DL *list) {
  for(int i = 0, size = list->size;i < size;i++) {
    DL_shift(list);
  }
}

void DL_delete(DL *list) {
  DL_clear(list);
  free(list);
}

bool DL_set(DL * list, double v, int index) {
  if(index >= 0 && index < list->size) {
    DN *tmpNode = list->start;
    for(int i = 0;i < list->size;i++) {
      if(i == index) {
        tmpNode->value = v;
        return true;
      }
      tmpNode = tmpNode->next;
    }
  }
  return false;
}

double DL_get(DL * list, int index) {
  if(index < 0 || index >= list->size) {
    return 0;
  }
  DN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(i == index) {
      return tmpNode->value;
    }
    tmpNode = tmpNode->next;
  }
}

double * DL_toDoubleArray(DL *list) {
  double *array = (double*)malloc(list->size * sizeof(double));
  if(array == NULL) {
    return NULL;
  }
  DN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    array[i] = tmpNode->value;
    tmpNode = tmpNode->next;
  }
  return array;
}

void DL_sort(DL *list) {
  _DL_sort(list, false);
}

void DL_rsort(DL *list) {
  _DL_sort(list, true);
}

DL * DL_createFrom(double *array, int len) {
  DL *list = DL_create();
  if(list == NULL) {
    return NULL;
  }
  int i = 0;
  while(i < len) {
    if(!DL_add(list, array[i])) {
      DL_delete(list);
      return NULL;
    }
    i++;
  }
  return list;
}

DL * DL_copy(DL *list) {
  DL *listCopy = DL_create();
  if(listCopy == NULL) {
    return NULL;
  }
  DN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(!DL_add(listCopy, tmpNode->value)) {
      DL_delete(listCopy);
      return NULL;
    }
    tmpNode = tmpNode->next;
  }
  return listCopy;
}

bool DL_concatArray(DL *list, double *array, int len) {
  int i = 0;
  while(i < len) {
    if(!DL_add(list, array[i])) {
      return false;
    }
    i++;
  }
  return true;
}

bool DL_concatList(DL *listA, DL *listB) {
  DN *tmpNode = listB->start;
  for(int i = 0;i < listB->size;i++) {
    if(!DL_add(listA, tmpNode->value)) {
      return false;
    }
    tmpNode = tmpNode->next;
  }
  return true;
}

bool DL_reverse(DL *list) {
  DL *tmpDL = DL_create();
  if(tmpDL == NULL) {
    return false;
  }
  DN *tmpNode = list->start;
  for(int i = 0;i < list->size; i++) {
    if(!DL_unshift(tmpDL, tmpNode->value)) {
      DL_delete(tmpDL);
      return false;
    }
    tmpNode = tmpNode->next;
  }
  DL_clear(list);
  list->start = tmpDL->start;
  list->end = tmpDL->end;
  list->size = tmpDL->size;
  free(tmpDL);
  return true;
}

DL * DL_slice(DL *list, int start, int end) {
  if(start >= list->size || start < 0 || end <= start) {
    return NULL;
  }
  DL *listSub = DL_create();
  if(listSub == NULL) {
    return NULL;
  }
  DN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(i >= start && i < end) {
      if(!DL_add(listSub, tmpNode->value)) {
        DL_delete(listSub);
        return NULL;
      }
    }
    if(i == end - 1) {
      return listSub;
    }
    tmpNode = tmpNode->next;
  }
  return listSub;
}

DL * DL_sub(DL *list, int start, int length) {
  if(start >= list->size || start < 0 || length < 1) {
    return NULL;
  }
  DL *listSub = DL_create();
  if(listSub == NULL) {
    return NULL;
  }
  DN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(i >= start && i < start + length) {
      if(!DL_add(listSub, tmpNode->value)) {
        DL_delete(listSub);
        return NULL;
      }
    }
    if(i > start + length - 1) {
      return listSub;
    }
    tmpNode = tmpNode->next;
  }
  return listSub;
}

bool DL_startsWith(DL *list, double v) {
  return list->size > 0 && list->start->value == v;
}

bool DL_endsWith(DL *list, double v) {
  return list->size == 1 && list->start->value == v || 
    list->size > 0 && list->end->value == v;
}

bool DL_contains(DL * list, double v) {
  DN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(tmpNode->value == v) {
      return true;
    }
    tmpNode = tmpNode->next;
  }
  return false;
}

bool DL_isEmpty(DL *list) {
  return list->size == 0 ? 1 : 0;
}

int DL_compare(DL *listA, DL *listB) {
  int len = listA->size > listB->size ? listB->size : listA->size;
  DN *tmpNodeA = listA->start;
  DN *tmpNodeB = listB->start;
  for(int i = 0;i < len;i++) {
    if(tmpNodeA->value < tmpNodeB->value) {
      return 1;
    }else if(tmpNodeA->value > tmpNodeB->value) {
      return -1;
    }
    tmpNodeA = tmpNodeA->next;
    tmpNodeB = tmpNodeB->next;
  }
  if(listA->size > listB->size) return -1;
  else if(listA->size < listB->size) return 1;
  return 0;
}

bool DL_equalsList(DL *listA, DL *listB) {
  return DL_compare(listA, listB) == 0;
}

bool DL_equalsArray(DL *list, double *array, int len) {
  if(list->size != len) {
    return false;
  }
  DN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(tmpNode->value != array[i]) {
      return false;
    }
    tmpNode = tmpNode->next;
  }
  return true;
}

bool DL_isSame(DL *listA, DL *listB) {
  return listA == listB;
}

int DL_indexOf(DL * list, double v) {
  DN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(tmpNode->value == v) {
      return i;
    }
    tmpNode = tmpNode->next;
  }
  return -1;
}

int DL_lastIndexOf(DL * list, double v) {
  DN *tmpNode = list->start;
  int index = -1;
  for(int i = 0;i < list->size;i++) {
    if(tmpNode->value == v) {
      index = i;
    }
    tmpNode = tmpNode->next;
  }
  return index;
}

int DL_count(DL *list, double v) {
  DN *tmpNode = list->start;
  int n = 0;
  for(int i = 0;i < list->size;i++) {
    if(tmpNode->value == v) {
      n++;
    }
    tmpNode = tmpNode->next;
  }
  return n;
}

void DL_fill(DL *list, double v) {
  DN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    tmpNode->value = v;
    tmpNode = tmpNode->next;
  }
}

void DL_replace(DL *list, double oldValue, double newValue) {
  DN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(tmpNode->value == oldValue) {
      tmpNode->value = newValue;
    }
    tmpNode = tmpNode->next;
  }
}

void DL_print(DL *list) {
  DN *tmpNode = list->start;
  printf("{");
  for(int i = 0;i < list->size;i++) {
    printf("%.2lf", tmpNode->value);
    tmpNode = tmpNode->next;
    i != list->size - 1 && printf(", ");
  }
  printf("}");
}

void DL_forEach(DL *list, void (*cb)(DL *, DN *, int)) {
  DN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    cb(list, tmpNode, i);
    tmpNode = tmpNode->next;
  }
}

DL * DL_map(DL *list, double (*cb)(DL *, DN *, int)) {
  DL *newDL = DL_create();
  if(newDL == NULL) {
    return NULL;
  }  
  DN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(!DL_add(newDL, cb(list, tmpNode, i))) {
      DL_delete(newDL);
      return NULL;
    }
    tmpNode = tmpNode->next;
  }
  return newDL;
}

DL * DL_filter(DL *list, bool (*cb)(DL *, DN *, int)) {
  DL *newDL = DL_create();
  if(newDL == NULL) {
    return NULL;
  }
  DN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(!cb(list, tmpNode, i)) {
      tmpNode = tmpNode->next;
      continue;
    }
    if(!DL_add(newDL, tmpNode->value)) {
      DL_delete(newDL);
      return NULL;
    }
    tmpNode = tmpNode->next;
  }
  return newDL;
}

bool DL_every(DL *list, bool (*cb)(DL *, DN *, int)) {
  DN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(!cb(list, tmpNode, i)) {
      return false;
    }
    tmpNode = tmpNode->next;
  }
  return true;
}

/*--------######################################################################################--------*/
/*--------#--******--******--******--******--**  **--******----**    --******--******--******--#--------*/
/*--------#--******--******--******--******--**  **--******----**    --******--******--******--#--------*/
/*--------#--**    --  **  --**  **--  **  --*** **--**    ----**    --  **  --**    --  **  --#--------*/
/*--------#--******--  **  --******--  **  --******--**    ----**    --  **  --******--  **  --#--------*/
/*--------#--******--  **  --****  --  **  --******--** ***----**    --  **  --******--  **  --#--------*/
/*--------#--    **--  **  --******--  **  --** ***--**  **----**    --  **  --    **--  **  --#--------*/
/*--------#--******--  **  --**  **--******--**  **--******----******--******--******--  **  --#--------*/
/*--------#--******----**----**  **--******--**  **--******----******--******--******--  **  --#--------*/
/*--------######################################################################################--------*/

static void SN_delete(SN *stringNode) {
  CL_delete(stringNode->value);
  free(stringNode);
}

static SN * SN_create(String array) {
  SN *stringNode = (SN *)malloc(sizeof(SN));
  CL *v = CL_createFrom(array);
  if(stringNode == NULL) {
    return NULL;
  }else if(v ==  NULL) {
    SN_delete(stringNode);
  }
  stringNode->value = v;
  stringNode->next = NULL;
  return stringNode;
}

static SN * SN_createFromList(CL *charList) {
  SN *stringNode = (SN *)malloc(sizeof(SN));
  CL *charListCopy = CL_copy(charList);
  if(stringNode == NULL) {
    return NULL;
  }else if(charListCopy == NULL) {
    SN_delete(stringNode);
    return NULL;
  }
  stringNode->value = charListCopy;
  stringNode->next = NULL;
  return stringNode;
}

static SN * SL_getNode(SL * list, int index) {
  if(index < 0 || index >= list->size) {
    return NULL;
  }
  SN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(i == index) {
      return tmpNode;
    }
    tmpNode = tmpNode->next;
  }
}

SL * SL_create() {
  SL *list = (SL *)malloc(sizeof(SL));
  if(list == NULL) {
    return NULL;
  }
  list->start = list->end = NULL;
  list->size = 0;
  return list;
}

bool SL_addArray(SL *list, String array) {
  SN *stringNode = SN_create(array);
  if(stringNode == NULL) {
    return false;
  }
  if(list->size == 0) {
    list->start = list->end = stringNode;
  }else if(list->size == 1) {
    list->start->next = list->end = stringNode;
  }else {
    list->end->next = stringNode;
    list->end = list->end->next;
  }
  list->size++;
  return true;
}

bool SL_addList(SL *list, CL *v) {
  SN *stringNode = SN_createFromList(v);
  if(stringNode == NULL) {
    return false;
  }
  if(list->size == 0) {
    list->start = list->end = stringNode;
  }else if(list->size == 1) {
    list->start->next = list->end = stringNode;
  }else {
    list->end->next = stringNode;
    list->end = list->end->next;
  }
  list->size++;
  return true;
}

bool SL_unshiftArray(SL *list, String array) {
  SN *stringNode = SN_create(array);
  if(stringNode == NULL) {
    return false;
  }
  if(list->size == 0) {
    list->start = list->end = stringNode;
  }else if(list->size == 1) {
    list->start = stringNode;
    list->start->next = list->end;
  }else {
    SN *tmpNode = list->start;
    list->start = stringNode;
    list->start->next = tmpNode;
  }
  list->size++;
  return true;
}

bool SL_unshiftList(SL *list, CL *v) {
  SN *stringNode = SN_createFromList(v);
  if(stringNode == NULL) {
    return false;
  }
  if(list->size == 0) {
    list->start = list->end = stringNode;
  }else if(list->size == 1) {
    list->start = stringNode;
    list->start->next = list->end;
  }else {
    SN *tmpNode = list->start;
    list->start = stringNode;
    list->start->next = tmpNode;
  }
  list->size++;
  return true;
}

void SL_pop(SL *list) {
  if(list->size > 2) {
    SN_delete(list->end);
    list->end = SL_getNode(list, list->size - 2);
    list->end->next = NULL;
    list->size--;
  }else if(list->size == 2) {
    SN_delete(list->end);
    list->start->next = list->end = NULL;
    list->size = 1;
  }else if(list->size == 1) {
    SN_delete(list->start);
    list->start = NULL;
    list->size = 0;
  }
}

void SL_shift(SL * list) {
  if(list->size > 1) {
    SN *tmpNode = list->start->next;
    SN_delete(list->start);
    list->start = tmpNode;
    list->size--;
  }else if(list->size == 1) {
    SN_delete(list->start);
    list->start = NULL;
    list->size = 0;
  }
}

bool SL_insertList(SL *list, CL *v, int index) {
  if(index < 0 || index > list->size) {
    return false;
  }
  if(index == 0) {
    if(!SL_unshiftList(list, v)) return false;
  }else if(index == list->size) {
    if(!SL_addList(list, v)) return false;
  }else {
    SN *previousNode = SL_getNode(list, index - 1);
    SN *currentNode = SN_createFromList(v);
    if(currentNode == NULL) return false;
    currentNode->next = previousNode->next;
    previousNode->next = currentNode;
    list->size++;
  }
  return true;
}

bool SL_insertArray(SL *list, String array, int index) {
  if(index < 0 || index > list->size) {
    return false;
  }
  if(index == 0) {
    if(!SL_unshiftArray(list, array)) return false;
  }else if(index == list->size) {
    if(!SL_addArray(list, array)) return false;
  }else {
    SN *previousNode = SL_getNode(list, index - 1);
    SN *currentNode = SN_create(array);
    if(currentNode == NULL) return false;
    currentNode->next = previousNode->next;
    previousNode->next = currentNode;
    list->size++;
  }
  return true;
}

void SL_remove(SL *list, int index) {
  if(index >= 0 && index < list->size) {
    if(index == 0) {
      SL_shift(list);
    }else if(index == list->size - 1) {
      SL_pop(list);
    }else {
      SN *previousNode = SL_getNode(list, index - 1);
      SN *currentNode = previousNode->next;
      previousNode->next = currentNode->next;
      SN_delete(currentNode);
      list->size--;
    }
  }
}

void SL_clear(SL *list) {
  for(int i = 0, size = list->size;i < size;i++) {
    SL_shift(list);
  }
}

void SL_delete(SL *list) {
  SL_clear(list);
  free(list);
}

bool SL_setArray(SL * list, String array, int index) {
  if(!(index >= 0 && index < list->size)) {
    return false;
  }
  CL *newCL = CL_createFrom(array);
  if(newCL == NULL) {
    return false;
  }
  if(index == 0) {
    CL_delete(list->start->value);
    list->start->value = newCL;
  }else if(index == list->size - 1) {
    CL_delete(list->end->value);
    list->end->value = newCL;
  }else {
    SN *tmpNode = SL_getNode(list, index);
    CL_delete(tmpNode->value);
    tmpNode->value = newCL;
  }
  return true;
}

bool SL_setList(SL * list, CL *v, int index) {
  if(!(index >= 0 && index < list->size)) {
    return false;
  }
  CL *newCL = CL_copy(v);
  if(index == 0) {
    CL_delete(list->start->value);
    list->start->value = newCL;
  }else if(index == list->size - 1) {
    CL_delete(list->end->value);
    list->end->value = newCL;
  }else {
    SN *tmpNode = SL_getNode(list, index);
    CL_delete(tmpNode->value);
    tmpNode->value = newCL;
  }
  return true;
}

String SL_get(SL * list, int index) {
  if(index < 0 || index >= list->size) {
    return NULL;
  }
  SN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(i == index) {
      return CL_toCharArray(tmpNode->value);
    }
    tmpNode = tmpNode->next;
  }
}

void SL_toLowerCase(SL *list) {
  SN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    CL_toLowerCase(tmpNode->value);
    tmpNode = tmpNode->next;
  }
}

void SL_toUpperCase(SL *list) {
  SN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    CL_toUpperCase(tmpNode->value);
    tmpNode = tmpNode->next;
  }
}

void SL_capitalize(SL *list) {
  SN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    CL_capitalize(tmpNode->value);
    tmpNode = tmpNode->next;
  }
}

static void _SL_sort(SL *list, bool isReversed) {
  SN *currentNode, *previousNode;
  bool difference;
  loopAgain:
    difference = false;
    currentNode = previousNode = list->start;
    for(int i = 0;i < list->size;i++) {
      currentNode = currentNode->next;
      if(currentNode != NULL && (isReversed ? CL_compare(previousNode->value, currentNode->value) == 1 :
          CL_compare(previousNode->value, currentNode->value) == -1)) {
        CL *c = currentNode->value;
        currentNode->value = previousNode->value;
        previousNode->value = c;
        difference = true;
      }
      previousNode = currentNode;
    }
  if(difference) {
    goto loopAgain;
  }
}

void SL_sort(SL *list) {
  _SL_sort(list, false);
}

void SL_rsort(SL *list) {
  _SL_sort(list, true);
}

SL * SL_createFrom(String *array, int len) {
  SL *list = SL_create();
  if(list == NULL) {
    return NULL;
  }
  int i = 0;
  while(i < len) {
    if(!SL_addArray(list, array[i])) {
      SL_delete(list);
      return NULL;
    }
    i++;
  }
  return list;
}

SL * SL_copy(SL *list) {
  SL *listCopy = SL_create();
  if(listCopy == NULL) {
    return NULL;
  }
  SN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(!SL_addList(listCopy, tmpNode->value)) {
      SL_delete(listCopy);
      return NULL;
    }
    tmpNode = tmpNode->next;
  }
  return listCopy;
}

bool SL_concat(SL *listA, SL *listB) {
  SN *tmpNode = listB->start;
  for(int i = 0;i < listB->size;i++) {
    if(!SL_addList(listA, tmpNode->value)) {
      SL_delete(listA);
      return false;
    }
    tmpNode = tmpNode->next;
  }
  return true;
}

bool SL_reverse(SL *list) {
  SL *tmpSL = SL_create();
  if(tmpSL == NULL) {
    return false;
  }
  SN *tmpNode = list->start;
  for(int i = 0;i < list->size; i++) {
    if(!SL_unshiftList(tmpSL, tmpNode->value)) {
      SL_delete(tmpSL);
      return false;
    }
    tmpNode = tmpNode->next;
  }
  SL_clear(list);
  list->start = tmpSL->start;
  list->end = tmpSL->end;
  list->size = tmpSL->size;
  free(tmpSL);
  return true;
}

SL * SL_slice(SL *list, int start, int end) {
  if(start >= list->size || start < 0 || end <= start) {
    return NULL;
  }
  SL *listSub = SL_create();
  if(listSub == NULL) {
    return NULL;
  }
  SN *tmpString = list->start;
  for(int i = 0;i < list->size;i++) {
    if(i >= start && i < end) {
      if(!SL_addList(listSub, tmpString->value)) {
        SL_delete(listSub);
        return NULL;
      }
    }
    if(i == end - 1) {
      return listSub;
    }
    tmpString = tmpString->next;
  }
  return listSub;
}

SL * SL_sub(SL *list, int start, int length) {
  if(start >= list->size || start < 0 || length < 1) {
    return NULL;
  }
  SL *listSub = SL_create();
  if(listSub == NULL) {
    return NULL;
  }
  SN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(i >= start && i < start + length) {
      if(!SL_addList(listSub, tmpNode->value)) {
        SL_delete(listSub);
        return NULL;
      }
    }
    if(i == start + length - 1) {
      return listSub;
    }
    tmpNode = tmpNode->next;
  }
  return listSub;
}

bool SL_startsWithArray(SL *list, String array) {
  return list->size > 0 && CL_equalsArray(list->start->value, array);
}

bool SL_startsWithList(SL *list, CL *v) {
  return list->size > 0 && CL_equalsList(list->start->value, v);
}

bool SL_endsWithArray(SL *list, String array) {
  return list->size == 1 && CL_equalsArray(list->start->value, array) ||
    list->size > 0 && CL_equalsArray(list->end->value, array);
}

bool SL_endsWithList(SL *list, CL *v) {
  return list->size == 1 && CL_equalsList(list->start->value, v) ||
    list->size > 0 && CL_equalsList(list->end->value, v);
}

bool SL_containsArray(SL * list, String array) {
  SN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(CL_equalsArray(tmpNode->value, array)) {
      return true;
    }
    tmpNode = tmpNode->next;
  }
  return false;
}

bool SL_containsList(SL * list, CL *v) {
  SN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(CL_equalsList(tmpNode->value, v)) {
      return true;
    }
    tmpNode = tmpNode->next;
  }
  return false;
}

bool SL_isEmpty(SL *list) {
  return list->size == 0 ? 1 : 0;
}

bool SL_equals(SL *listA, SL *listB) {
  if(listA->size != listB->size) {
    return false;
  }
  SN *tmpNodeA = listA->start;
  SN *tmpNodeB = listB->start;
  for(int i = 0;i < listA->size;i++) {
    if(!CL_equalsList(tmpNodeA->value, tmpNodeB->value)) {
      return false;
    }
    tmpNodeA = tmpNodeA->next;
    tmpNodeB = tmpNodeB->next;
  }
  return true;
}

bool SL_isSame(SL *listA, SL *listB) {
  return CL_isSame(listA->start->value, listB->start->value);
}

int SL_indexOfArray(SL * list, String array) {
  SN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(CL_equalsArray(tmpNode->value, array)) {
      return i;
    }
    tmpNode = tmpNode->next;
  }
  return -1;
}

int SL_indexOfList(SL * list, CL *v) {
  SN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(CL_equalsList(tmpNode->value, v)) {
      return i;
    }
    tmpNode = tmpNode->next;
  }
  return -1;
}

int SL_lastIndexOfArray(SL * list, String array) {
  SN *tmpNode = list->start;
  int index = -1;
  for(int i = 0;i < list->size;i++) {
    if(CL_equalsArray(tmpNode->value, array)) {
      index = i;
    }
    tmpNode = tmpNode->next;
  }
  return index;
}

int SL_lastIndexOfList(SL * list, CL *v) {
  SN *tmpNode = list->start;
  int index = -1;
  for(int i = 0;i < list->size;i++) {
    if(CL_equalsList(tmpNode->value, v)) {
      index = i;
    }
    tmpNode = tmpNode->next;
  }
  return index;
}

int SL_countArray(SL *list, String array) {
  SN *tmpNode = list->start;
  int n = 0;
  for(int i = 0;i < list->size;i++) {
    if(CL_equalsArray(tmpNode->value, array)) {
      n++;
    }
    tmpNode = tmpNode->next;
  }
  return n;
}

int SL_countList(SL *list, CL *v) {
  SN *tmpNode = list->start;
  int n = 0;
  for(int i = 0;i < list->size;i++) {
    if(CL_equalsList(tmpNode->value, v)) {
      n++;
    }
    tmpNode = tmpNode->next;
  }
  return n;
}

bool SL_fillArray(SL *list, String array) {
  SN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    CL *newCL = CL_createFrom(array);
    if(newCL == NULL) return false;
    CL_delete(tmpNode->value);
    tmpNode->value = newCL;
    tmpNode = tmpNode->next;
  }
  return true;
}

bool SL_fillList(SL *list, CL *v) {
  SN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    CL *newCL = CL_copy(v);
    if(newCL == NULL) return false;
    CL_delete(tmpNode->value);
    tmpNode->value = newCL;
    tmpNode = tmpNode->next;
  }
  return true;
}

bool SL_replaceArray(SL *list, String oldValue, String newValue) {
  SN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(CL_equalsArray(tmpNode->value, oldValue)) {
      CL *newCL = CL_createFrom(newValue);
      if(newCL == NULL) return false;
      CL_delete(tmpNode->value);
      tmpNode->value = newCL;
    }
    tmpNode = tmpNode->next;
  }
  return true;
}

bool SL_replaceList(SL *list, String oldValue, CL *newValue) {
  SN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(CL_equalsArray(tmpNode->value, oldValue)) {
      CL *newCL = CL_copy(newValue);
      if(newCL == NULL) return false;
      CL_delete(tmpNode->value);
      tmpNode->value = newCL;
    }
    tmpNode = tmpNode->next;
  }
  return true;
}

void SL_print(SL *list) {
  SN *tmpNode = list->start;
  printf("{");
  for(int i = 0;i < list->size;i++) {
    CL_print(tmpNode->value);
    if(i != list->size - 1) {
      printf(", ");
    }
    tmpNode = tmpNode->next;
  }
  printf("}");
}

void SL_forEach(SL *list, void (*cb)(SL *, SN *, int)) {
  SN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    cb(list, tmpNode, i);
    tmpNode = tmpNode->next;
  }
}

SL * SL_map(SL *list, CL * (*cb)(SL *, SN *, int)) {
  SL *newSL = SL_create();
  if(newSL == NULL) {
    return NULL;
  }  
  SN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(!SL_addList(newSL, cb(list, tmpNode, i))) {
      SL_delete(newSL);
      return NULL;
    }
    tmpNode = tmpNode->next;
  }
  return newSL;
}

SL * SL_filter(SL *list, bool (*cb)(SL *, SN *, int)) {
  SL *newSL = SL_create();
  if(newSL == NULL) {
    return NULL;
  }
  SN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(!cb(list, tmpNode, i)) {
      tmpNode = tmpNode->next;
      continue;
    }
    if(!SL_addList(newSL, tmpNode->value)) {
      SL_delete(newSL);
      return NULL;
    }
    tmpNode = tmpNode->next;
  }
  return newSL;
}

bool SL_every(SL *list, bool (*cb)(SL *, SN *, int)) {
  SN *tmpNode = list->start;
  for(int i = 0;i < list->size;i++) {
    if(!cb(list, tmpNode, i)) {
      return false;
    }
    tmpNode = tmpNode->next;
  }
  return true;
}

static SL * CL_splitc(CL *charList, char sep) {
  SL *stringList = SL_create();
  CL *tmpCL = CL_create();
  if(stringList == NULL) {
    return NULL;
  }else if(tmpCL == NULL) {
    SL_delete(stringList);
    return NULL;
  }
  CN *tmpNode = charList->start;
  for(int i = 0;i < charList->size;i++) {
    if(tmpNode->value == sep) {
      if(!SL_addList(stringList, tmpCL)) {
        CL_delete(tmpCL);
        SL_delete(stringList);
        return NULL;
      }
      CL_clear(tmpCL);
    }else {
      if(!CL_add(tmpCL, tmpNode->value)) {
        CL_delete(tmpCL);
        SL_delete(stringList);
        return NULL;
      }
    }
    tmpNode = tmpNode->next;
  }
  if(!SL_addList(stringList, tmpCL)) {
    CL_delete(tmpCL);
    SL_delete(stringList);
    return NULL;
  }
  CL_delete(tmpCL);
  return stringList;
}

static String _CL_substr(CL *charList, int start, int length) {
  CL *subList = CL_sub(charList, start, length);
  if(subList == NULL) {
    return NULL;
  }
  String str = CL_toCharArray(subList);
  CL_delete(subList);
  return str;
}

SL * CL_split(CL *charList, String sep) {
  if(strlen(sep) == 1) {
    return CL_splitc(charList, sep[0]);
  }
  SL *stringList = SL_create();
  if(stringList == NULL) {
    return NULL;
  }
  if(CL_equalsArray(charList, sep)) {
    if(!SL_addArray(stringList, "") || !SL_addArray(stringList, "")) {
      SL_delete(stringList);
      return NULL;
    }
    return stringList;
  }
  CL *tmpCL = CL_create();
  CN *tmpNode = charList->start;
  for(int i = 0;i < charList->size;i++) {
    if(tmpNode->value != sep[0]) {
      if(!CL_add(tmpCL, tmpNode->value)) {
        SL_delete(stringList);
        CL_delete(tmpCL);
        return NULL;
      }
      tmpNode = tmpNode->next;
      continue;
    }
    String s = _CL_substr(charList, i, strlen(sep));
    if(s == NULL) {
      SL_delete(stringList);
      CL_delete(tmpCL);
      return NULL;
    }
    if(!strcmp(s, sep)) {
      if(!SL_addList(stringList, tmpCL)) {
        SL_delete(stringList);
        CL_delete(tmpCL);
        free(s);
        return NULL;
      }
      CL_clear(tmpCL);
      i += strlen(sep) - 1;
      for(int j = 0;j < strlen(sep) - 1; j++) {
        tmpNode = tmpNode->next;
      }
    }else {
      if(!CL_add(tmpCL, tmpNode->value)) {
        SL_delete(stringList);
        CL_delete(tmpCL);
        free(s);
        return NULL;
      }
    }
    free(s);
    tmpNode = tmpNode->next;
  }
  if(!SL_addList(stringList, tmpCL)) {
    SL_delete(stringList);
    CL_delete(tmpCL);
    return NULL;
  }
  CL_delete(tmpCL);
  return stringList;
}