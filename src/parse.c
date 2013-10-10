/*!
  @file parse.c
  @author Masaki Waga <tsugarutamenobu@gmail.com>
  @date 2013/10/10
  
  @brief Schemeのパーサー
*/

#include "parse.h"

atom_t parseAtom(void)
{
  abort();
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
