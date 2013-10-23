/*!
  @file data.h
  @author Masaki Waga <tsugarutamenobu@gmail.com>
  @date 2013/10/10
  
  @brief Schemeのデータを保持する
*/

#ifndef INCLUDED_DATA_H
#define INCLUDED_DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "utils.h"

typedef struct
{
  char *label;
  atom_t data;
} data_t;

typedef struct _dataList_t
{
  data_t car;
  struct _dataList_t *cdr;
} dataList_t;


//! dataを格納しているlistから要素を取り出す
atom_t getLocalData (char *, dataList_t *);

//! dataを格納しているlistから要素を取り出す
atom_t getData (char *);

//! dataを格納する.とりあえず破壊的代入もできるようにする
void setLocalData (char *, atom_t, dataList_t *);

//! dataを格納する.とりあえず破壊的代入もできるようにする
void setData (char *, atom_t);

void freeDataList(dataList_t*,dataList_t*);

#endif
