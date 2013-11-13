/*!
  @file library.c
  @author Masaki Waga <tsugarutamenobu@gmail.com>
  @date 2013/10/13
  
  @brief libraryÁ∏∫†ÁπßÂåªıÄÅÆÁ∏∫„ÇÖ‚Üí
*/  
  
#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "utils.h"
#include "library.h"

static list_t * m_head;
static dataList_t* dataListHead;

#define ARG1 args->car
#define ARG2 args->cdr.pointerData->car
#define CHECKERROR(A) if ( (A).label == UNDEFINED_VARIABLE || (A).label == ERROR ) return (A)
#define CHECKERROR1 CHECKERROR( ARG1 );
#define CHECKERROR2 CHECKERROR( ARG1 ); CHECKERROR (ARG2);
#define CHECKALLERROR(A) for( list_t* _t = (A);_t != NULL ; _t = _t->cdr.pointerData) if ( _t->car.label == UNDEFINED_VARIABLE ||  _t->car.label == ERROR ) return  _t->car
#define ISNOTARGS1 args == NULL || args->cdr.pointerData != NULL
#define ISNOTARGS2 args == NULL || args->cdr.pointerData == NULL || args->cdr.pointerData->cdr.pointerData != NULL
#define RETERROR(A) return (atom_t){.label=ERROR,.stringData=(A)} 
#define IFNOTARGS1ERROR(A) if ( ISNOTARGS1 ) { RETERROR(A); }
#define IFNOTARGS2ERROR(A) if ( ISNOTARGS2 ) { RETERROR(A); }

void setDataListHead( dataList_t * head){dataListHead = head;}

void setHead( list_t * head)
{
    m_head = head;
}

atom_t
_lambda (list_t * args)
{
  if ( ISNOTARGS2 || ARG1.label != LAMBDA || ARG2.label != LAMBDA )
      RETERROR("ERROR: Syntax error: lambda : args -> function -> atom");

  return (atom_t){.label=FUNCTION,.lambdaData={.args=ARG1.pointerData,.expression=ARG2.pointerData,.dataList = dataListHead}};
}

  atom_t  _plus (list_t * args) 
{
  IFNOTARGS2ERROR ("ERROR: Syntax error: + : num -> num -> num" )
  CHECKERROR2;
  if (ARG1.label == INT && ARG2.label == INT)
    {
      return (atom_t)
      {
      .label = INT,.intData =
	  (ARG1.intData + ARG2.intData)};
    }
  else if (ARG1.label == INT
	   && ARG2.label == DOUBLE)
    {
      return (atom_t)
      {
      .label = DOUBLE,.doubleData =
	  (ARG1.intData + ARG2.doubleData)};
    }
  else 
    if (ARG1.label == DOUBLE && ARG2.label == INT)
    {
      return (atom_t)
      {
      .label = DOUBLE,.doubleData =
	  (ARG1.doubleData + ARG2.intData)};
    }
    else if (ARG1.label == DOUBLE && ARG2.label == DOUBLE)
  return (atom_t)
  {
  .label = DOUBLE,.doubleData =
      (ARG1.doubleData + ARG2.doubleData)};
  return (atom_t)
  {
      .label = ERROR,.stringData =
      "error : argument of + must be num"};
}

atom_t
_minus (list_t * args) 
{
  IFNOTARGS2ERROR ("ERROR: Syntax error: - : num -> num -> num" )
  CHECKERROR2;
  if (ARG1.label == INT && ARG2.label == INT)
    {
      return (atom_t) 
      {
      .label = INT,.intData = 
	  (ARG1.intData - ARG2.intData)};
    }
  
  else
  if (ARG1.label == INT && ARG2.label == DOUBLE)
    {
      return (atom_t) 
      {
      .label = DOUBLE,.doubleData = 
	  (ARG1.intData - ARG2.doubleData)};
    }
  
  else
  if (ARG1.label == DOUBLE && ARG2.label == INT)
    {
      return (atom_t) 
      {
      .label = DOUBLE,.doubleData = 
	  (ARG1.doubleData - ARG2.intData)};
    }
  return (atom_t) 
  {
  .label = DOUBLE,.doubleData = 
      (ARG1.doubleData - ARG2.doubleData)};
}

 atom_t  _multiply (list_t * args) 
{
  IFNOTARGS2ERROR ("ERROR: Syntax error: * : num -> num -> num" )
  CHECKERROR2;
  if (ARG1.label == INT && ARG2.label == INT)
    {
      return (atom_t) 
      {
      .label = INT,.intData = 
	  (ARG1.intData * ARG2.intData)};
    }
  
  else
  if (ARG1.label == INT && ARG2.label == DOUBLE)
    {
      return (atom_t) 
      {
      .label = DOUBLE,.doubleData = 
	  (ARG1.intData * ARG2.doubleData)};
    }
  
  else
  if (ARG1.label == DOUBLE && ARG2.label == INT)
    return (atom_t) 
    {
    .label = DOUBLE,.doubleData = 
	(ARG1.doubleData * ARG2.intData)};
  return (atom_t) 
  {
  .label = DOUBLE,.doubleData = 
      (ARG1.doubleData * ARG2.doubleData)};
}

 atom_t  _div (list_t * args) 
{
  IFNOTARGS2ERROR ("ERROR: Syntax error: / : num -> num -> num" )
  CHECKERROR2;
  if (ARG1.label == INT && ARG2.label == INT)
    {
      return (atom_t) 
      {
      .label = INT,.intData = 
	  (ARG1.intData / ARG2.intData)};
    }
  else
  if (ARG1.label == INT && ARG2.label == DOUBLE)
    {
      return (atom_t) 
      {
      .label = DOUBLE,.doubleData = 
	  (ARG1.intData / ARG2.doubleData)};
    }

  else
    if (ARG1.label == DOUBLE && ARG2.label == INT)
    {
      return (atom_t) 
      {
      .label = DOUBLE,.doubleData =
	  (ARG1.doubleData / ARG2.intData)};
    }
  return (atom_t) 
  {
  .label = DOUBLE,.doubleData = 
      (ARG1.doubleData / ARG2.doubleData)};
}

 atom_t  _cons (list_t * args) 
{
  list_t * ret;
  IFNOTARGS2ERROR ("ERROR: Syntax error: cons : atom -> atom -> list" )
  CHECKERROR2;
  ret = mallocWithErr (sizeof (list_t));
  *ret = cons (ARG1, ARG2);
  return (atom_t) 
  {
  .label = POINTER_OF_LIST,.pointerData = ret};
}

atom_t  _car (list_t * args) 
{
  IFNOTARGS1ERROR ("ERROR: Syntax error: car : list -> atom" )
  CHECKERROR1
  if (ARG1.label != POINTER_OF_LIST)
    return (atom_t)
    {
    .label = ERROR,.stringData = "ERROR: car : list -> atom"};
  return ARG1.pointerData->car;
}

atom_t  _cdr (list_t * args) 
{
  IFNOTARGS1ERROR ("ERROR: Syntax error: car : list -> atom" )
  CHECKERROR1
  if (ARG1.label != POINTER_OF_LIST)
    return (atom_t)
    {
    .label = ERROR,.stringData = "ERROR: cdr : list -> atom"};
  return ARG1.pointerData->cdr;
}

atom_t  _quit (list_t * args) 
{
  exit (0);
}

 atom_t  _equal (list_t * args) 
{
  float arg1,arg2;
  IFNOTARGS2ERROR ("ERROR: Syntax error: = : atom -> atom -> bool")
  CHECKERROR2;
  switch ( ARG1.label) {
  case INT:
      arg1 = ARG1.intData;
      break;
  case DOUBLE:
      arg1 = ARG1.doubleData;
      break;
  default :
      return ( atom_t){.label = ERROR,.stringData="In procedure =: Wrong type argument in position 1"};
  }

  switch ( ARG2.label) {
  case INT:
      arg2 = ARG2.intData;
      break;
  case DOUBLE:
      arg2 = ARG2.doubleData;
      break;
  default :
      return ( atom_t){.label = ERROR,.stringData="In procedure =: Wrong type argument in position 2"};
  }
  if ( arg1 == arg2 )
      return (atom_t){.label=BOOL,.boolData=true};

  return (atom_t){.label=BOOL,.boolData=false};
}

atom_t  _gt (list_t * args) 
{
  float arg1,arg2;
  IFNOTARGS2ERROR ("ERROR: Syntax error: > : atom -> atom -> bool")
  CHECKERROR2;
  switch ( ARG1.label) {
  case INT:
      arg1 = ARG1.intData;
      break;
  case DOUBLE:
      arg1 = ARG1.doubleData;
      break;
  default :
      return ( atom_t){.label = ERROR,.stringData="In procedure >: Wrong type argument in position 1"};
  }

  switch ( ARG2.label) {
  case INT:
      arg2 = ARG2.intData;
      break;
  case DOUBLE:
      arg2 = ARG2.doubleData;
      break;
  default :
      return ( atom_t){.label = ERROR,.stringData="In procedure >: Wrong type argument in position 2"};
  }
  if ( arg1 > arg2 )
      return (atom_t){.label=BOOL,.boolData=true};

  return (atom_t){.label=BOOL,.boolData=false};
}

 atom_t  _gtq (list_t * args) 
{
  float arg1,arg2;
  IFNOTARGS2ERROR ("ERROR: Syntax error: >= : atom -> atom -> bool")
  CHECKERROR2;
  switch ( ARG1.label) {
  case INT:
      arg1 = ARG1.intData;
      break;
  case DOUBLE:
      arg1 = ARG1.doubleData;
      break;
  default :
      return ( atom_t){.label = ERROR,.stringData="In procedure >=: Wrong type argument in position 1"};
  }

  switch ( ARG2.label) {
  case INT:
      arg2 = ARG2.intData;
      break;
  case DOUBLE:
      arg2 = ARG2.doubleData;
      break;
  default :
      return ( atom_t){.label = ERROR,.stringData="In procedure >=: Wrong type argument in position 2"};
  }
  if ( arg1 >= arg2 )
      return (atom_t){.label=BOOL,.boolData=true};

  return (atom_t){.label=BOOL,.boolData=false};
}

 atom_t  _le (list_t * args) 
{
  float arg1,arg2;
  IFNOTARGS2ERROR ("ERROR: Syntax error: < : atom -> atom -> bool")
  CHECKERROR2;
  switch ( ARG1.label) {
  case INT:
      arg1 = ARG1.intData;
      break;
  case DOUBLE:
      arg1 = ARG1.doubleData;
      break;
  default :
      return ( atom_t){.label = ERROR,.stringData="In procedure <: Wrong type argument in position 1"};
  }

  switch ( ARG2.label) {
  case INT:
      arg2 = ARG2.intData;
      break;
  case DOUBLE:
      arg2 = ARG2.doubleData;
      break;
  default :
      return ( atom_t){.label = ERROR,.stringData="In procedure <: Wrong type argument in position 2"};
  }
  if ( arg1 < arg2 )
      return (atom_t){.label=BOOL,.boolData=true};

  return (atom_t){.label=BOOL,.boolData=false};
}

 atom_t  _leq (list_t * args) 
{
  float arg1,arg2;
  IFNOTARGS2ERROR ("ERROR: Syntax error: <= : atom -> atom -> bool")
  CHECKERROR2;
  switch ( ARG1.label) {
  case INT:
      arg1 = ARG1.intData;
      break;
  case DOUBLE:
      arg1 = ARG1.doubleData;
      break;
  default :
      return ( atom_t){.label = ERROR,.stringData="In procedure <=: Wrong type argument in position 1"};
  }

  switch ( ARG2.label) {
  case INT:
      arg2 = ARG2.intData;
      break;
  case DOUBLE:
      arg2 = ARG2.doubleData;
      break;
  default :
      return ( atom_t){.label = ERROR,.stringData="In procedure <=: Wrong type argument in position 2"};
  }
  if ( arg1 <= arg2 )
      return (atom_t){.label=BOOL,.boolData=true};

  return (atom_t){.label=BOOL,.boolData=false};
}

atom_t  _if (list_t * args) 
{
  if (args == NULL || args->cdr.pointerData == NULL 
       ||args->cdr.pointerData->cdr.pointerData == NULL || args->cdr.pointerData->cdr.pointerData->cdr.pointerData != NULL)
    return (atom_t) 
    {
    .label = ERROR,.stringData =
	"ERROR: Syntax error: if : bool -> expr -> expr -> atom"};
  if ( ARG1.label == LAMBDA) {
      atom_t tmp = _execute( m_head,ARG1.pointerData->car,ARG1.pointerData->cdr.pointerData ,dataListHead);
      /* freeList(ARG1.pointerData); */
      ARG1 = tmp;
  }
  if ( ARG1.label == BOOL && ARG1.boolData == false) {
      if (args->cdr.pointerData->cdr.pointerData->car.label == LAMBDA || args->cdr.pointerData->cdr.pointerData->car.label == SYSTEM_FUNCTION || args->cdr.pointerData->cdr.pointerData->car.label == FUNCTION )
	  return _execute(m_head,args->cdr.pointerData->cdr.pointerData->car.pointerData->car,args->cdr.pointerData->cdr.pointerData->car.pointerData->cdr.pointerData,dataListHead);
      return args->cdr.pointerData->cdr.pointerData->car;
  }
  if (ARG2.label == LAMBDA || ARG2.label == SYSTEM_FUNCTION || ARG2.label == FUNCTION )
      return _execute(m_head,ARG2.pointerData->car,ARG2.pointerData->cdr.pointerData,dataListHead);
  return ARG2;
}

atom_t  _list (list_t * args)
{
  CHECKALLERROR(args);
  return (atom_t) 
  {
  .label = POINTER_OF_LIST,.pointerData = args};
}
