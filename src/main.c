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
      else if ( ch == '(' )
	{
	  fprintf(stderr,"not defined yet\n");
	  abort();
	}
      else if ( ch  == '"' )
	{
	  fprintf(stderr,"not defined yet\n");
	  abort();
	}
      else
	{
	  displayAtom( parseAtomWithFirstChar(ch) );	  
	}
    }

  return 0;
}
