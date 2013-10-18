/*!
  @file library.h
  @author Masaki Waga <tsugarutamenobu@gmail.com>
  @date 2013/10/13
  
  @brief libraryだよはあと
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
atom_t _if (list_t *);

#endif
