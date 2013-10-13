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

int main ()
{

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
	      displayList( *(atom.pointerData) );
	      if ( atom.pointerData->cdr.pointerData != NULL )
	      _execute(atom.pointerData->car,*(atom.pointerData->cdr.pointerData));
	  }
	 
      }
    }
  
  return 0;
}
