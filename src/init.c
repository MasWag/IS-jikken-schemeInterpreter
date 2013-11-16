/*!
  @file init.c
  @author Masaki Waga <tsugarutamenobu@gmail.com>
  @date 2013/10/10
  
  @brief 初期化処理をおこなう
*/

#include "utils.h"
#include "data.h"
#include "types.h"
#include "library.h"

#define SETSYSTEMFUNC( A , B )   setData (#A, (atom_t){.label = SYSTEM_FUNCTION,.systemFunction = B})
void
init (void)
{
  setData ("a", (atom_t)
	   {
	   .label = INT,.intData = 3});
  SETSYSTEMFUNC( + , _plus );
  SETSYSTEMFUNC( - , _minus);
  SETSYSTEMFUNC( * , _multiply);
  SETSYSTEMFUNC( / , _div);
  SETSYSTEMFUNC( cons, _cons);
  SETSYSTEMFUNC( car , _car);
  SETSYSTEMFUNC( cdr, _cdr);
  SETSYSTEMFUNC( exit, _quit);
  SETSYSTEMFUNC( quit, _quit);
  SETSYSTEMFUNC( lambda, _lambda);
  SETSYSTEMFUNC( if, _if);
  SETSYSTEMFUNC( =, _equal);
  SETSYSTEMFUNC( >, _gt);
  SETSYSTEMFUNC( >=, _gtq);
  SETSYSTEMFUNC( <, _le);
  SETSYSTEMFUNC( <=, _leq);
  SETSYSTEMFUNC( list, _list);
  SETSYSTEMFUNC( modulo, _modulo);
  SETSYSTEMFUNC( remainder, _modulo);
  SETSYSTEMFUNC( sin, _sin);
  SETSYSTEMFUNC( cos, _cos);
  SETSYSTEMFUNC( tan, _tan);
  SETSYSTEMFUNC( asin, _asin);
  SETSYSTEMFUNC( acos, _acos);
  SETSYSTEMFUNC( atan, _atan);
  SETSYSTEMFUNC( exp, _exp);
  SETSYSTEMFUNC( log, _log);
  SETSYSTEMFUNC( expt, _expt);

  
}
