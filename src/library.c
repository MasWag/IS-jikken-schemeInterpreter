/*!
  @file library.c
  @author Masaki Waga <tsugarutamenobu@gmail.com>
  @date 2013/10/13
  
  @brief libraryだよはあと
*/
  
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "types.h"
#include "utils.h"
#include "library.h"

static list_t * m_head;
static dataList_t* dataListHead;

#define ARG1 args->car
#define ARG2 args->cdr.pointerData->car
#define ARG3 args->cdr.pointerData->cdr.pointerData->car
#define CHECKERROR(A) if ( (A).label == UNDEFINED_VARIABLE || (A).label == ERROR ) return (A)
#define CHECKERROR1 CHECKERROR( ARG1 );
#define CHECKERROR2 CHECKERROR( ARG1 ); CHECKERROR (ARG2);
#define CHECKALLERROR(A) for( list_t* _t = (A);_t != NULL ; _t = _t->cdr.pointerData) if ( _t->car.label == UNDEFINED_VARIABLE ||  _t->car.label == ERROR ) return  _t->car
#define ISNOTARGS1 args == NULL || args->cdr.pointerData != NULL
#define ISNOTARGS2 args == NULL || args->cdr.pointerData == NULL || args->cdr.pointerData->cdr.pointerData != NULL
#define RETERROR(A) return (atom_t){.label=ERROR,.stringData=(A)} 
#define RETINT(A) return (atom_t){.label=INT,.intData=(A)} 
#define RETDOUBLE(A) return (atom_t){.label=DOUBLE,.doubleData=(A)} 
#define RETLIST(A) return (atom_t){.label=POINTER_OF_LIST,.pointerData=(A)} 
#define IFNOTARGS1ERROR(A) if ( ISNOTARGS1 ) { RETERROR(A); }
#define IFNOTARGS2ERROR(A) if ( ISNOTARGS2 ) { RETERROR(A); }
#define IS_NUM(A) (A).label == INT || (A).label == DOUBLE
#define IFNOTNUMERROR(A) if (! (IS_NUM((A))) ) { RETERROR("ERROR: number required"); }
#define NUMVALUE(A) (A).label == INT ? (A).intData : (A).doubleData
#define DEFINESYSTEMFUNCTION(A) atom_t A (list_t * args)
#define BIND(A,B) DEFINESYSTEMFUNCTION(A){B}

void setDataListHead( dataList_t * head){dataListHead = head;}

void setHead( list_t * head)
{
    m_head = head;
}

DEFINESYSTEMFUNCTION( _lambda )
{
  if ( ISNOTARGS2 || ARG1.label != LAMBDA || ARG2.label != LAMBDA )
      RETERROR("ERROR: Syntax error: lambda : args -> function -> atom");

  return (atom_t){.label=FUNCTION,.lambdaData={.args=ARG1.pointerData,.expression=ARG2.pointerData,.dataList = dataListHead}};
}

#define OPERATOR(OPR)  IFNOTARGS2ERROR ("ERROR: Syntax error: "#OPR" : num -> num -> num" ) \
  CHECKERROR2;\
  if (ARG1.label == INT && ARG2.label == INT)\
    {\
      return (atom_t)\
      {\
      .label = INT,.intData =\
	  (ARG1.intData OPR ARG2.intData)};\
    }\
  else if (ARG1.label == INT\
	   && ARG2.label == DOUBLE)\
    {\
      return (atom_t)\
      {\
      .label = DOUBLE,.doubleData =\
	  (ARG1.intData OPR ARG2.doubleData)};\
    }\
  else \
    if (ARG1.label == DOUBLE && ARG2.label == INT)\
    {\
      return (atom_t)\
      {\
      .label = DOUBLE,.doubleData =\
	  (ARG1.doubleData OPR ARG2.intData)};\
    }\
    else if (ARG1.label == DOUBLE && ARG2.label == DOUBLE)\
	return (atom_t)\
	{\
	    .label = DOUBLE,.doubleData =\
		(ARG1.doubleData OPR ARG2.doubleData)};\
  return (atom_t)\
  {\
      .label = ERROR,.stringData =\
      "error : argument of "#OPR" must be num"}

#define ORDER_OPERATOR(OPR,STR) float arg1,arg2;				\
  IFNOTARGS2ERROR ("ERROR: Syntax error: "STR" : atom -> atom -> bool")\
  CHECKERROR2;\
  switch ( ARG1.label) {\
  case INT:\
      arg1 = ARG1.intData;\
      break;\
  case DOUBLE:\
      arg1 = ARG1.doubleData;\
      break;\
  default :\
      return ( atom_t){.label = ERROR,.stringData="In procedure "STR": Wrong type argument in position 1"};\
  }\
  switch ( ARG2.label) {\
  case INT:\
      arg2 = ARG2.intData;\
      break;\
  case DOUBLE:\
      arg2 = ARG2.doubleData;\
      break;\
  default :\
      return ( atom_t){.label = ERROR,.stringData="In procedure "STR": Wrong type argument in position 2"};\
  }\
  if ( arg1 OPR arg2 )\
      return (atom_t){.label=BOOL,.boolData=true};\
  return (atom_t){.label=BOOL,.boolData=false}

BIND ( _plus,OPERATOR(+);)
BIND ( _minus,OPERATOR(-);)
BIND ( _multiply,OPERATOR(*);)
BIND ( _div ,OPERATOR(/);)

atom_t  _modulo (list_t * args) 
{
  IFNOTARGS2ERROR ("ERROR: Syntax error: modulo : num -> num -> num" )
  CHECKERROR2;
  if (ARG1.label == INT && ARG2.label == INT)
    {
      return (atom_t) 
      {
      .label = INT,.intData = 
	  (ARG1.intData % ARG2.intData)};
    }
  return (atom_t)
  {
      .label = ERROR,.stringData ="error : argument of modulo must be int"};
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
  IFNOTARGS1ERROR ("ERROR: Syntax error: cdr : list -> atom" )
  CHECKERROR1
  if (ARG1.label != POINTER_OF_LIST)
    return (atom_t)
    {
    .label = ERROR,.stringData = "ERROR: cdr : list -> atom"};
  return ARG1.pointerData->cdr;
}

BIND ( _quit,exit (0);)
BIND ( _equal,ORDER_OPERATOR( == , "=");)
BIND ( _gt ,ORDER_OPERATOR( > , ">");)
BIND ( _gtq ,ORDER_OPERATOR( >= , ">=");)
BIND ( _le ,ORDER_OPERATOR( < , "<");)
BIND ( _leq,ORDER_OPERATOR( <= , "<=");)

atom_t  _if (list_t * args) 
{
  if (args == NULL || args->cdr.pointerData == NULL 
       ||args->cdr.pointerData->cdr.pointerData == NULL || args->cdr.pointerData->cdr.pointerData->cdr.pointerData != NULL)
    return (atom_t) 
    {
    .label = ERROR,.stringData =
	"ERROR: Syntax error: if : bool -> expr -> expr -> atom"};
  if ( ARG1.label == LAMBDA) {
    ARG1 = _execute( m_head,ARG1.pointerData->car,ARG1.pointerData->cdr.pointerData ,dataListHead);
  }
#define EXECUTE_IN_IF(ARG) if (ARG.label == LAMBDA || ARG.label == SYSTEM_FUNCTION || ARG.label == FUNCTION ) \
	  return _execute(m_head,ARG.pointerData->car,ARG.pointerData->cdr.pointerData,dataListHead);\
      return ARG\

  if ( ARG1.label == BOOL && ARG1.boolData == false) {
    EXECUTE_IN_IF(ARG3);
  }
    EXECUTE_IN_IF(ARG2);
#undef EXECUTE_IN_IF
}

DEFINESYSTEMFUNCTION ( _list )
{
  CHECKALLERROR(args);
  RETLIST(args);
}

#define SQUAREFUNCTION( FUNCNAME ) DEFINESYSTEMFUNCTION( _##FUNCNAME ){\
  IFNOTARGS1ERROR ("ERROR: Syntax error: _"#FUNCNAME" : num -> num" ) \
  IFNOTNUMERROR (ARG1)\
  return (atom_t){.label=DOUBLE,.doubleData=FUNCNAME(NUMVALUE(ARG1))};\
}

SQUAREFUNCTION( sin )
SQUAREFUNCTION( cos )
SQUAREFUNCTION( tan )
SQUAREFUNCTION( asin )
SQUAREFUNCTION( acos )
SQUAREFUNCTION ( exp )
SQUAREFUNCTION ( log )

DEFINESYSTEMFUNCTION( _atan ){
    if ( args == NULL )
	RETERROR ("wrong number of arguments for atan required 1");
    if ( !(ISNOTARGS1) ) {
	IFNOTNUMERROR (ARG1)
	RETDOUBLE (atan(NUMVALUE(ARG1)));
    }
    IFNOTNUMERROR (ARG1)
    IFNOTNUMERROR (ARG2)
    RETDOUBLE (atan2(NUMVALUE(ARG1),NUMVALUE(ARG2)));
}

DEFINESYSTEMFUNCTION( _expt ){
  IFNOTARGS2ERROR ("ERROR: Syntax error: _expt : num -> num -> num" ) 
  IFNOTNUMERROR (ARG1)
  IFNOTNUMERROR (ARG2)
  return (atom_t){.label=DOUBLE,.doubleData=pow(NUMVALUE(ARG1),NUMVALUE(ARG2))};
}
