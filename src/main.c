/*!
  @file main.c
  @author Masaki Waga <tsugarutamenobu@gmail.com>
  @date 2013/10/10
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "parse.h"
#include "utils.h"

extern void init (void);
extern void setDisplayUndefVariableMode(bool in);

int
main ()
{

  init ();

  int ch;

  while ((ch = getchar ()) != -1)
    {
      if (ch == ' ' || ch == '\n')
	continue;
      else if (ch == ';')
	{
	  while ((ch = getchar ()) != -1 && ch != '\n');
	  continue;
	}
      else
	{
	  atom_t atom = parseAtomWithFirstChar (ch);
	  if (atom.label != LAMBDA) {
	    setDisplayUndefVariableMode(true);
	    displayAtom (atom);
	    setDisplayUndefVariableMode(false);
	  }
	  else
	    {
	      atom_t ret = _execute (atom.pointerData,atom.pointerData->car,
				     atom.pointerData->cdr.pointerData,getGlobalDataListHead());
	      setDisplayUndefVariableMode(true);
	      switch ( ret.label )
		{
		case POINTER_OF_LIST:
		case LAMBDA :
		  displayList (*(ret.pointerData));
		  freeList ( ret.pointerData );
		  break;
		case FUNCTION:
		  puts("LAMBDA");
		  break;
		default :
		  displayAtom (ret);
		  break;
	      }
	      setDisplayUndefVariableMode(false);
	    }

	}
    }

  return 0;
}
