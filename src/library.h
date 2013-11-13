/*!
  @file library.h
  @author Masaki Waga <tsugarutamenobu@gmail.com>
  @date 2013/10/13
  
  @brief library縺�繧医����縺ゅ→
*/

#ifndef LIBRARY_H
#define LIBRARY_H

#include "types.h"

atom_t _plus (list_t *);
atom_t _minus (list_t *);
atom_t _multiply (list_t *);
atom_t _div (list_t *);
atom_t _cons (list_t *);
atom_t _car (list_t *);
atom_t _cdr (list_t *);
atom_t _quit (list_t *);
atom_t _equal (list_t *);
atom_t _gt (list_t *);
atom_t _gtq (list_t *);
atom_t _le (list_t *);
atom_t _leq (list_t *);
atom_t _if (list_t *);
atom_t _list (list_t *);

#endif
