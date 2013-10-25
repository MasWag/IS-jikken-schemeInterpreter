/*!
  @file data.c
  @author Masaki Waga <tsugarutamenobu@gmail.com>
  @date 2013/10/10
  
  @brief Schemeのデータを保持する
*/

#include "data.h"
#include "utils.h"

static dataList_t listHead = {
  .car.label = "define",
  .car.data = {
	       .label = SYSTEM_FUNCTION,
	       .systemFunction = _define,
	       .variableName = "define"},
  .cdr = NULL
};

dataList_t * getGlobalDataListHead(void){return &listHead;}


//! dataを格納しているlistから要素を取り出す
atom_t 
getData( char* label, dataList_t * in)
{
  dataList_t *ptr = in;
  if (strcmp (ptr->car.label, label) == 0)
    return ptr->car.data;
  if (ptr->cdr != NULL)
    {
      for (; ptr->cdr != NULL; ptr = ptr->cdr)
	{
	  if (strcmp (ptr->cdr->car.label, label) == 0)
	    {
		atom_t ret = ptr->cdr->car.data;
		ret.variableName = label;
		return ret;
	    }
	}
    }
  return (atom_t)
  {
      .label = UNDEFINED_VARIABLE,.stringData = label,.variableName=label};
}

//! dataを格納する.とりあえず破壊的代入もできるようにする
void
setData (char *label, atom_t data)
{
  setLocalData(label,data,&listHead);
}

//! dataを格納する.とりあえず破壊的代入もできるようにする
void
setLocalData (char *label, atom_t data,dataList_t *in)
{
  dataList_t *ptr = in;
  if (strcmp (ptr->car.label, label) == 0)
    {
      ptr->car.data = data;
      return;
    }
  dataList_t *next = NULL;
  if (ptr->cdr != NULL)
    {
      for (; ptr->cdr != NULL; ptr = ptr->cdr)
	{
	  if (strcmp (ptr->cdr->car.label, label) == 0)
	    {
	      ptr->cdr->cdr->car.data = data;
	      return;
	    }
	}
    }
  next = mallocWithErr (sizeof (dataList_t));
  next->car.label = label;
  next->car.data = data;
  next->cdr = NULL;
  ptr->cdr = next;
}

void freeDataList(dataList_t * src,dataList_t* end)
{
  if ( src == NULL )
    return;

  if ( src->car.data.label == POINTER_OF_LIST && src->car.data.pointerData != NULL )
    freeList( src->car.data.pointerData );
  if ( src->cdr != NULL && src->cdr != end)
      freeDataList( src->cdr ,end);
  
  free ( src );
}
