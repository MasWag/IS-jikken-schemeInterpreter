/*!
  @file types.h
  @author Masaki Waga <tsugarutamenobu@gmail.com>
  @date 2013/10/10
  
  @brief Schemeの型を定義する
*/

#pragma once

#include <stdbool.h>

struct _list_t;

//! atom_tの内部で用いるLabel
typedef enum {
  INT,
  DOUBLE,
  POINTER_OF_LIST,
  SYSTEM_FUNCTION,
  STRING,
  BOOL,
  ERROR
} atom_label_t;

//! atomを表す構造体.
typedef struct {
  atom_label_t label;
  /* union { */
    int intData;
    double doubleData;
    void* systemFunction;
    char* stringData;
    bool boolData;
    struct _list_t* pointerData;
  /* }; */
} atom_t;

//! listを表す構造体.
typedef struct _list_t {
  atom_t car;
  atom_t cdr;
} list_t;
