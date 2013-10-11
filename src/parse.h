/*!
  @file parse.h
  @author Masaki Waga <tsugarutamenobu@gmail.com>
  @date 2013/10/10
  
  @brief Schemeのパーサー
*/

#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include "utils.h"
#include "types.h"
#include "data.h"
#include "params.h"

//! atomをparseする
atom_t parseAtom(void);
atom_t parseAtomWithFirstChar(char ch);
atom_t parseString(void);
