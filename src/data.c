/*!
  @file data.c
  @author Masaki Waga <tsugarutamenobu@gmail.com>
  @date 2013/10/10
  
  @brief Schemeのデータを保持する
*/

#include "data.h"

static dataList_t listHead = {
  .car.label="define",
  .car.data={
    .label=SYSTEM_FUNCTION,
    .systemFunction=_define},
  .cdr=NULL
};

//! dataを格納しているlistから要素を取り出す
atom_t getData(char* label)
{
  dataList_t* ptr = &listHead;
  if ( strcmp(ptr->car.label,label) == 0)
      return ptr->car.data;
  if ( ptr->cdr != NULL )
    {
      for( ; ptr->cdr != NULL;ptr = ptr->cdr)
	{
	  if ( strcmp(ptr->cdr->car.label,label) == 0)
	    {
	      return ptr->cdr->cdr->car.data;
	    }
	}
    }
  return mkErrorMes("error: undefined variable\n");
}

//! dataを格納する.とりあえず破壊的代入もできるようにする
void setData(char* label, atom_t data)
{
  dataList_t* ptr = &listHead;
  if ( strcmp(ptr->car.label,label) == 0)
    {
      ptr->car.data = data;
      return;
    }
  dataList_t * next = NULL;
  if ( ptr->cdr != NULL )
    {
      for( ; ptr->cdr != NULL;ptr = ptr->cdr)
	{
	  if ( strcmp(ptr->cdr->car.label,label) == 0)
	    {
	      ptr->cdr->cdr->car.data = data;
	      return;
	    }
	}
    }
  next = mallocWithErr(sizeof(dataList_t));
  next-> car.label = label;
  next-> car.data = data;
  next-> cdr = NULL;
  ptr->cdr = next;  
}
