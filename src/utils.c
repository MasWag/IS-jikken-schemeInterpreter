/*!
  @file utils.c
  @author Masaki Waga <tsugarutamenobu@gmail.com>
  @date 2013/10/10
  
  @brief utility関数
*/

#include "utils.h"

//! error処理をやってくれるmalloc
void *
mallocWithErr (size_t size)
{
  char *tmp;

  tmp = malloc (size);

  if (tmp == NULL)
    {
      fprintf (stderr, "error:MALLOC FAILED!!\n");
      exit (-1);
    }
  return tmp;
}

//! error処理をやってくれるrealloc
void *
reallocWithErr (void *ptr, size_t size)
{
  char *tmp;

  tmp = realloc (ptr, size);

  if (tmp == NULL)
    {
      fprintf (stderr, "error:REALLOC FAILED!!\n");
      exit (-1);
    }
  return tmp;
}

//! atomのdisplay関数
void
displayAtomWithoutLF (atom_t in)
{

  switch (in.label)
    {
    case INT:
      printf ("%d", in.intData);
      break;
    case DOUBLE:
      printf ("%f", in.doubleData);
      break;
    case SYSTEM_FUNCTION:
      printf ("This is system function");
      break;
    case STRING:
      printf ("\"%s\"", in.stringData);
      break;
    case ERROR:
      printf ("%s", in.stringData);
      break;
    case BOOL:
      printf (in.boolData ? "#t" : "#f");
      break;
    case CHAR:
      printf ("#\\%c", in.charData);
      break;
    case UNDEFINED_VARIABLE:
      printf ("error: undefined variable %s ", in.stringData);
      break;
    default:
      if (in.pointerData == NULL)
	{
	  printf ("()");
	  return;
	}
      fprintf (stderr, "unknown type of atom!!");
      printf ("%d\n", in.label);
      return;
      /* exit(-1); */
    }
}

void
displayListWithoutBraces (list_t list)
{
  putchar (' ');
  if (list.car.label != POINTER_OF_LIST && list.car.label != LAMBDA)
    displayAtomWithoutLF (list.car);
  else
    displayList (*(list.car.pointerData));
  if (list.cdr.pointerData == NULL)
    return;
  if (list.cdr.label != POINTER_OF_LIST && list.cdr.label != LAMBDA)
    {
      putchar (' ');
      putchar ('.');
      putchar (' ');
      displayAtomWithoutLF (list.cdr);
    }
  else
    displayListWithoutBraces (*(list.cdr.pointerData));
}

void
displayListWithoutLF (list_t list)
{
  putchar ('(');
  displayListWithoutBraces (list);
  putchar (' ');
  putchar (')');
}


atom_t
_define (list_t * args)
{
  if (args == NULL || args->cdr.pointerData == NULL
      || args->cdr.pointerData->cdr.pointerData != NULL)
    return (atom_t)
    {
    .label = ERROR,.stringData =
	"ERROR: Syntax error: define : label -> atom -> atom"};
  if (args->car.label != UNDEFINED_VARIABLE)
    {
      printf ("error: ");
      displayAtom (args->car);
      puts (" is not string");
      return (atom_t)
      {
      .label = BOOL,.boolData = false};
    }
  setData (args->car.stringData, args->cdr.pointerData->car);
  return args->cdr.pointerData->car;
}

atom_t
_lambda (list_t * args)
{
  dataList_t *dataList;
  if (args == NULL || args->cdr.pointerData == NULL
      || args->cdr.pointerData->cdr.pointerData != NULL || args->car.label != LAMBDA || args->cdr.pointerData->car.label != LAMBDA)
    return (atom_t)
    {
    .label = ERROR,.stringData =
	"ERROR: Syntax error: lambda : args -> function -> atom"};
  dataList = malloc ( sizeof( dataList_t ) );

  return (atom_t){.label=FUNCTION,.lambdaData={.args=args->car.pointerData,.expression=args->cdr.pointerData->car.pointerData}};
}

atom_t
_execute (atom_t functionAtom, list_t * args)
{
  if (functionAtom.label == ERROR)
    return functionAtom;
  if (functionAtom.label == LAMBDA)
    functionAtom =
      _execute (functionAtom.pointerData->car,
		functionAtom.pointerData->cdr.pointerData);
  else if (functionAtom.label != SYSTEM_FUNCTION)
    {
      printf ("error: ");
      displayAtomWithoutLF (functionAtom);
      puts (" is not function");
      return (atom_t)
      {
      .label = ERROR,};
    }
  else if (functionAtom.label == SYSTEM_FUNCTION)
    {
      if ( functionAtom.systemFunction != _lambda )
	for (list_t * t = args; t != NULL; t = t->cdr.pointerData)
	  if (t->car.label == LAMBDA)
	    {
	      atom_t tmp =
		_execute (t->car.pointerData->car,
			  t->car.pointerData->cdr.pointerData);
	      free( t->car.pointerData);
	      t->car = tmp;
	    }
      return functionAtom.systemFunction (args);
    }
  return (atom_t)
  {
  .label = ERROR};
}

void freeList(list_t * src)
{
  if ( src == NULL )
    return;

  if ( src->car.label == POINTER_OF_LIST && src->car.pointerData != NULL )
    freeList( src->car.pointerData );
  if ( src->cdr.label == POINTER_OF_LIST && src->cdr.pointerData != NULL )
    freeList( src->cdr.pointerData );
  
  free ( src );
}
