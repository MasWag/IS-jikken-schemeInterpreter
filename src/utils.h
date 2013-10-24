/*!
  @file utils.h
  @author Masaki Waga <tsugarutamenobu@gmail.com>
  @date 2013/10/10
  
  @brief utility関数
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "types.h"

//! error処理をやってくれるmalloc
void *mallocWithErr (size_t size);

//! error処理をやってくれるrealloc
void *reallocWithErr (void *ptr, size_t size);

//! atomのdisplay関数
void displayAtomWithoutLF (atom_t in);
#define displayAtom(a) ( displayAtomWithoutLF(a),putchar('\n') )

//! listのdisplay関数
void displayListWithoutLF (list_t in);
#define displayList(a) ( displayListWithoutLF(a),putchar('\n') )

//! define関数
atom_t _define (list_t *);

//! execute関数
atom_t _execute (list_t *,atom_t,list_t *,dataList_t*);

//! lambda
atom_t _lambda ( list_t *);

//! listのcar
#define car(l) (l.car)

//! listのcdr
#define cdr(l) (l.cdr)

//! cons
#define cons( a , b ) ( (list_t){.car = a,.cdr = b})

#define mkErrorMes(a) ( (atom_t){.label=ERROR,.stringData=a} )

void freeList(list_t*);

atom_t executeLambda(list_t *,atom_t functionAtom,list_t * args,dataList_t*);
