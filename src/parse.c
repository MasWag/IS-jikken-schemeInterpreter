/*!
  @file parse.c
  @author Masaki Waga <tsugarutamenobu@gmail.com>
  @date 2013/10/10
  
  @brief Schemeのパーサー
*/

#include "parse.h"

atom_t parseAtom(void)
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
}

atom_t parseString(void)
{
  char ch;
  int t = 0;
  char * str;
  size_t strSize = mallocByte;
  atom_t ret;
  str = mallocWithErr( strSize );
  while ( ( ch = getchar () ) != -1 && ch != '"')
    {
      str[t] = ch;
      t++;
    } 
  str[t] = '\0';

  ret.label = STRING;
  ret.stringData = str;

  return ret;
}


atom_t parseAtomWithFirstChar(char ch)
{
  int t = 0;
  char * str;
  size_t strSize = mallocByte;
  bool isDouble = true;
  bool isInt = true;
  atom_t ret;
  str = mallocWithErr( strSize );
  do 
    {
      if ( ch !='.' && ( ch < '0' || ch > '9' ))
	isDouble = isInt = false;
      if ( ch == '.' )
	if ( !isInt )
	  isDouble = false;
	else
	  isInt = false;
      
      if ( (t + 1) >= strSize )
	{
	  strSize += mallocByte;
	  str = reallocWithErr(str, strSize );
	}
      
      str[t] = ch;
      t++;
    } while ( ( ch = getchar () ) != -1 && ch != '\n'  && ch != ' ' );
  str[t] = '\0';

  if ( isInt )
    {
      ret.label = INT;
      ret.intData = atoi(str);
    } 
  else if ( isDouble )
    {
      ret.label = DOUBLE;
      ret.doubleData = atof(str);
    }
  else
    ret =  getData (str);
  
  free (str);

  return ret;
}
