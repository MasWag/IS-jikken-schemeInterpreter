/*!
  @file library.c
  @author Masaki Waga <tsugarutamenobu@gmail.com>
  @date 2013/10/13
  
  @brief libraryだよはあと
*/

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "library.h"

atom_t _plus(list_t * args)
{
  if ( args == NULL || args->cdr.pointerData == NULL || args->cdr.pointerData->cdr.pointerData != NULL ) 
      return (atom_t){.label=ERROR,.stringData="ERROR: Syntax error: define : label -> atom -> atom"};  
  if ( args->car.label == INT && args->cdr.pointerData->car.label == INT )
      return (atom_t){.label=INT,.intData=(args->car.intData+args->cdr.pointerData->car.intData)};
  else if ( args->car.label == INT && args->cdr.pointerData->car.label == DOUBLE )
      return (atom_t){.label=DOUBLE,.doubleData=(args->car.intData+args->cdr.pointerData->car.doubleData)};
  else if ( args->car.label == DOUBLE && args->cdr.pointerData->car.label == INT )
      return (atom_t){.label=DOUBLE,.doubleData=(args->car.doubleData+args->cdr.pointerData->car.intData)};
  return (atom_t){.label=DOUBLE,.doubleData=(args->car.doubleData+args->cdr.pointerData->car.doubleData)};
}

atom_t _quit(list_t* args)
{
  exit(0);
}






