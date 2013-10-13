/*!
  @file init.c
  @author Masaki Waga <tsugarutamenobu@gmail.com>
  @date 2013/10/10
  
  @brief 初期化処理をおこなう
*/

#include "data.h"
#include "types.h"

void init(void)
{
    setData("a",(atom_t){.label=INT,.intData=3});

}
