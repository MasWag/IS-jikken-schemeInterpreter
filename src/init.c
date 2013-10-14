/*!
  @file init.c
  @author Masaki Waga <tsugarutamenobu@gmail.com>
  @date 2013/10/10
  
  @brief 初期化処理をおこなう
*/

#include "data.h"
#include "types.h"
#include "library.h"

void init(void)
{
    setData("a",(atom_t){.label=INT,.intData=3});
    setData("+",(atom_t){.label=SYSTEM_FUNCTION,.systemFunction=_plus});
    setData("-",(atom_t){.label=SYSTEM_FUNCTION,.systemFunction=_minus});
    setData("*",(atom_t){.label=SYSTEM_FUNCTION,.systemFunction=_multiply});
    setData("/",(atom_t){.label=SYSTEM_FUNCTION,.systemFunction=_div});
    setData("quit",(atom_t){.label=SYSTEM_FUNCTION,.systemFunction=_quit});
}
