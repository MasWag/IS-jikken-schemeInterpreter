/*!
  @file utils.h
  @author Masaki Waga <tsugarutamenobu@gmail.com>
  @date 2013/10/10
  
  @brief utility関数
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

//! error処理をやってくれるmalloc
void * mallocWithErr(size_t size);

//! error処理をやってくれるrealloc
void * reallocWithErr(void* ptr,size_t size);

//! atomのdisplay関数
void displayAtom(atom_t in);

//! listのdisplay関数
void displayList(list_t in);
