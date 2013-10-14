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

extern void init(void);

int main ()
{

  init();

  int ch;
  
  while ( ( ch = getchar () ) != -1) 
    {
      if ( ch == ' ' || ch == '\n' ) 
	continue;
      else if ( ch == ';' ) 
	{
	  while ( ( ch = getchar () ) != -1 && ch != '\n' ) ;
	  continue;
	}
      else {
	  atom_t atom = parseAtomWithFirstChar( ch );
	  if ( atom.label != POINTER_OF_LIST ) 
	      displayAtom(atom);
	  else {
	      /* displayList( *(atom.pointerData) ); */
		  displayAtom(_execute(atom.pointerData->car,atom.pointerData->cdr.pointerData));

	  }
	 
      }
    }
  
  return 0;
}
