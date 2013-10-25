/*!
  @file utils.c
  @author Masaki Waga <tsugarutamenobu@gmail.com>
  @date 2013/10/10
  
  @brief utility関数
*/

#include "utils.h"
#include "library.h"

extern void setHead(list_t*);
extern void setDataListHead(dataList_t*);
static bool m_isDisplayUndefVariable;
void setDisplayUndefVariableMode(bool in){ m_isDisplayUndefVariable = in;}

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
  bool tmp;
  switch (in.label)
    {
    case INT:
      printf ("%d", in.intData);
      break;
    case DOUBLE:
      printf ("%f", in.doubleData);
      break;
    case SYSTEM_FUNCTION:
	printf("%s", in.variableName);
      /* printf ("This is system function"); */
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
	if ( m_isDisplayUndefVariable )
	    printf ("error: undefined variable %s ", in.stringData);
	else 
	    printf("%s", in.variableName);
      break;
    case FUNCTION:
	tmp = m_isDisplayUndefVariable;
	setDisplayUndefVariableMode(false);
	displayListWithoutLF( *(in.lambdaData.expression));
	setDisplayUndefVariableMode(tmp);
      /* printf("LAMBDA"); */
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
    displayListWithoutLF (*(list.car.pointerData));
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

atom_t _execute (list_t* head,atom_t functionAtom,list_t * args,dataList_t* dataListHead)
{

  if (functionAtom.label == ERROR)
    return functionAtom;
  if (functionAtom.label == LAMBDA) {
    functionAtom =
	_execute (head,functionAtom.pointerData->car,
		  functionAtom.pointerData->cdr.pointerData,dataListHead);
  }
  if (functionAtom.label == ERROR || functionAtom.label == UNDEFINED_VARIABLE) {
      puts("HERE");
      return (atom_t){.label=ERROR,.stringData=functionAtom.stringData };
  }
  else if (functionAtom.label != SYSTEM_FUNCTION && functionAtom.label != FUNCTION)
    {
      printf ("error: ");
      displayAtomWithoutLF (functionAtom);
      printf (" is not function %d\n",functionAtom.label);
      return (atom_t)
      {
      .label = ERROR,};
    }
  else if (functionAtom.label == FUNCTION)
    {
	for (list_t * t = args; t != NULL; t = t->cdr.pointerData)
	    if (t->car.label == LAMBDA)
	    {
	      atom_t tmp =
		  _execute (head,t->car.pointerData->car,
			    t->car.pointerData->cdr.pointerData,dataListHead);
	      free( t->car.pointerData);
	      t->car = tmp;
	    }
	#ifndef NODISPLAY
	displayList( *head );
	#endif
	return executeLambda(head,functionAtom,args,dataListHead);
    }
  else if (functionAtom.label == SYSTEM_FUNCTION)
    {
      if ( functionAtom.systemFunction != _lambda && functionAtom.systemFunction != _if ) 
	for (list_t * t = args; t != NULL; t = t->cdr.pointerData)
	  if (t->car.label == LAMBDA)
	    {
	      atom_t tmp =
		  _execute (head,t->car.pointerData->car,
			    t->car.pointerData->cdr.pointerData,dataListHead);
	      free( t->car.pointerData);
	      t->car = tmp;
	    }
      setHead(head);
      setDataListHead(dataListHead);
      #ifndef NODISPLAY
      displayList( *head );
      #endif
      return functionAtom.systemFunction (args);
    }
  return (atom_t)
  {
      .label = ERROR,.stringData="Unknown error"};
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

void copyLambda(atom_t srcAtom,atom_t** destAtom ,dataList_t* dataList)
{
    *destAtom = mallocWithErr( sizeof( atom_t ) );
    memcpy(*destAtom,&srcAtom,sizeof ( atom_t ) );
    switch ( srcAtom.label ) {
    case POINTER_OF_LIST:
    case LAMBDA:
	if ( srcAtom.pointerData != NULL ) {
	    (*destAtom)->pointerData = mallocWithErr( sizeof(list_t) );
	    atom_t * car = &((*destAtom)->pointerData->car);
	    atom_t * cdr = &((*destAtom)->pointerData->cdr);
	    copyLambda(srcAtom.pointerData->car,&car,dataList);
	    (*destAtom)->pointerData->car = *car;
	    copyLambda(srcAtom.pointerData->cdr,&cdr,dataList);
	    (*destAtom)->pointerData->cdr = *cdr;
	}
	break;
    case UNDEFINED_VARIABLE:
	**destAtom = getData((*destAtom)->variableName,dataList);
	break;
    default:
	break;
    }    
}

atom_t executeLambda(list_t* head,atom_t functionAtom,list_t * args,dataList_t* dataListHead)
{
//! freeするときはdataHeadからfunctionAtom.lambdaData.dataListの直前までをfreeする
  dataList_t* dataHead;
  dataList_t* dataNow;
  dataList_t* dataHead_;
  list_t * argsNow;
  atom_t * newFunctionAtom;
  if ( functionAtom.label != FUNCTION )
    {
      return mkErrorMes( "internal error in executeLambda (util.c)" );
    }

  argsNow = functionAtom.lambdaData.args;
  dataHead = mallocWithErr( sizeof(dataList_t) );
  dataNow = dataHead_ = mallocWithErr(sizeof(dataList_t) );
  dataHead_->cdr = dataHead;
  
  for ( list_t *t = args; t != NULL; t = t->cdr.pointerData ) {
      if ( argsNow == NULL ) {
	  freeDataList( dataHead ,functionAtom.lambdaData.dataList);
	  return mkErrorMes( "Error : too much args!! " );
      }
      dataNow->cdr->car = (data_t){.label=argsNow->car.stringData,.data=t->car};
      dataNow->cdr->cdr = mallocWithErr( sizeof(dataList_t) );
      dataNow = dataNow->cdr;
      argsNow = argsNow->cdr.pointerData;
  }
  free ( dataNow->cdr );
  dataNow->cdr = functionAtom.lambdaData.dataList;  
  /* if ( dataHead_ != NULL ) */
  /* free ( dataHead_ ); */
  // ここまでlocal variableのlistの処理

  if ( argsNow != NULL )
      return (atom_t){.label=FUNCTION,.lambdaData={.args=argsNow,.expression=functionAtom.lambdaData.expression,.dataList=dataHead}};
  
  // ここからlambda式のcopyと変数展開
  copyLambda((atom_t){.label=LAMBDA,.pointerData=functionAtom.lambdaData.expression}, &newFunctionAtom,dataHead);
  
  #ifndef NODISPLAY
  printf("called function :");
  displayListWithoutLF(*(functionAtom.lambdaData.expression));
  displayList(*args);
  #endif
  atom_t ret = _execute (newFunctionAtom->pointerData,newFunctionAtom->pointerData->car,newFunctionAtom->pointerData->cdr.pointerData,dataListHead);
  freeDataList(dataHead,functionAtom.lambdaData.dataList);
  freeList(newFunctionAtom->pointerData);
  return ret;
}
