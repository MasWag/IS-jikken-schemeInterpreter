/*!
  @file utils.c
  @author Masaki Waga <tsugarutamenobu@gmail.com>
  @date 2013/10/10
  
  @brief utility関数
*/

#include "utils.h"

//! error処理をやってくれるmalloc
void * mallocWithErr(size_t size)
{
  char * tmp;
  
  tmp = malloc ( size );

  if ( tmp == NULL )
    {
      fprintf(stderr,"error:MALLOC FAILED!!\n");
      exit(-1);
    }
  return tmp;
}

//! error処理をやってくれるrealloc
void * reallocWithErr(void* ptr,size_t size)
{
  char * tmp;
  
  tmp = realloc (ptr ,size );

  if ( tmp == NULL )
    {
      fprintf(stderr,"error:REALLOC FAILED!!\n");
      exit(-1);
    }
  return tmp;
}

//! atomのdisplay関数
void displayAtom(atom_t in)
{
  switch ( in.label )
    {
    case INT:
      printf("%d\n",in.intData);
      break;
    case DOUBLE:
      printf("%f\n",in.doubleData);
      break;
    default:
      fprintf(stderr,"unknown type of atom!!\n");
      exit(-1);
    }
}

