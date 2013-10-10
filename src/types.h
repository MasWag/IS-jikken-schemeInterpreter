/*!
  @file types.h
  @author Masaki Waga <tsugarutamenobu@gmail.com>
  @date 2013/10/10
  
  @brief Schemeの型を定義する
*/

#pragma once


//! atom_tの内部で用いるLabel
typedef enum {
  INT,
  DOUBLE
} atom_label_t;

//! atomを表す構造体.
typedef struct {
  atom_label_t label;
  union {
    int intData;
    double doubleData;
  };
} atom_t;

//! listを表す構造体.
typedef struct {
  atom_t car;
  list_t* cdr;
} list_t;
