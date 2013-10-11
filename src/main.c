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
	  list_t list;
	  while ( ( ch = getchar () ) != -1 && (ch == ' ' || ch == '\n' )) ;

	  // ここインチキしている
	  if ( ch != ')' )
	    {
	      list.car = parseAtomWithFirstChar(ch);
	    }
	  fprintf(stderr,"not defined yet\n");
	  abort();
	}
      else if ( ch  == '"' )
	{
	  displayAtom( parseString() );
	}
      else if ( ch == '#' )
	{
	  if( ( ch = getchar () ) == -1)
	    exit(0);
	  //true mode
	  if (ch == 't')
	    {
	      displayAtom( (atom_t){.label=BOOL,.boolData=true} );
	      continue;
	    }
	  //fales mode
	  if (ch == 'f')
	    {
	      displayAtom( (atom_t){.label=BOOL,.boolData=false} );
	      continue;
	    }

	  // char mode
	  if (ch == '\\')
	    {
	       char c;
	       if( ( ch = getchar () ) == -1)
		 exit(0);
	       c = ch;
	       if( ( ch = getchar () ) == -1)
		 exit(0);
	       if( ch == ' ' || ch == '\n')
		 {
		   displayAtom( (atom_t){.label=CHAR,.charData=c} );
		   continue;
		 }
	       fprintf(stderr,"unknown character name\n");
	       abort();
	    }
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
