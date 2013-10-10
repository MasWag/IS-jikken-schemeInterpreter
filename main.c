/*!
  @file main.c
  @author Masaki Waga <tsugarutamenobu@gmail.com>
  @date 2013/10/10
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static const int mallocByte = 100;

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
	  int t = 0;
	  char * str;
	  size_t strSize = mallocByte;
	  bool numFlag = true;
	  bool dotFlag = true;
	  str = mallocWithErr( strSize );	  
	  do 
	    {
	      if ( ch !='.' && ( ch <= '0' || ch >= '9' ))
		numFlag = false;
	      if ( ch == '.' )
		if ( dotFlag  == false )
		  numFlag = false;
		else
		  dotFlag = false;
	      
	      if ( (t + 1) >= strSize )
		{
		  strSize += mallocByte;
		  str = reallocWithErr(str, strSize );
		}

	      str[t] = ch;
	      t++;
	    } while ( ( ch = getchar () ) != -1 && ch != '\n'  && ch != ' ' );
	  str[t] = '\0';
	  if ( numFlag )
	    {
	      puts( dotFlag ? "true":"false");
	      puts("NUM");
	      printf("%f\n",atof(str));
	    }
	  else
	    puts (str);
	  free (str);
	}
    }

  return 0;
}
