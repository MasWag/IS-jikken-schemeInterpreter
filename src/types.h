/*!
  @file types.h
  @author Masaki Waga <tsugarutamenobu@gmail.com>
  @date 2013/10/10
  
  @brief Schemeの型を定義する
*/

#pragma once

#include <stdbool.h>

struct _list_t;

typedef struct {
} system_function_t;

//! atom_tの内部で用いるLabel
typedef enum {
  INT,
  DOUBLE,
  POINTER_OF_LIST,
  SYSTEM_FUNCTION,
  STRING,
  CHAR,
  BOOL,
  ERROR,
  UNDEFINED_VARIABLE,
  NULL_LIST
} atom_label_t;

//! atomを表す構造体.
typedef struct _atom_t {
  atom_label_t label;
  /* union { */
    char charData;
    int intData;
    double doubleData;
    struct _atom_t (*systemFunction)(list_t);
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
