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
    case SYSTEM_FUNCTION:
      printf("This is system function\n");
      break;
    case STRING:
      printf("\"%s\"\n",in.stringData);
      break;
    case ERROR:
      printf("%s",in.stringData);
      break;
    case BOOL:
      puts( in.boolData ? "true" : "false");
      break;
    case CHAR:
      printf("#\\%c\n",in.charData);
      break;
    case UNDEFINED_VARIABLE:
      printf("error: undefined variable %s\n",in.stringData);
      break;
    default:
      fprintf(stderr,"unknown type of atom!!\n");
      exit(-1);
    }
}

atom_t _define(atom_t label,atom_t data)
{
  if(label.label != STRING) 
    { 
      printf("error: ");
      displayAtom(label);
      puts(" is not string");
      return (atom_t){.label=BOOL,.boolData=false};
    }
  setData(label.stringData,data);
  return data;
}
