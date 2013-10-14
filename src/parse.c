/*!
  @file parse.c
  @author Masaki Waga <tsugarutamenobu@gmail.com>
  @date 2013/10/10
  
  @brief Schemeのパーサー
*/

#include "parse.h"

#define matchTwo(a,b,c) ( (a == b) || (a == c) )

static bool isFinFunc = false;
//! -1が返ってきたらexitするgetchar
static inline int
getcharWithExit ()
{
  int tmp;
  if ((tmp = getchar ()) == -1)
    exit (0);
  return tmp;
}

atom_t
parseAtom (void)
{
  int ch;

  while ((ch = getchar ()) != -1 && (ch == ' ' || ch == '\n'));

  return parseAtomWithFirstChar (ch);
}

atom_t
parseAtomWithFirstChar (char ch)
{
  if (ch == -1)
    exit (0);

_parseAtom1:
  switch (ch)
    {
    case ';':
      while ((ch = getchar ()) != -1 && ch != '\n');
      goto _parseAtom1;
    case '(':
      {
	list_t *first;
	list_t *now;
	list_t *last;
	while ((ch = getchar ()) != -1 && (ch == ' ' || ch == '\n'));

	if (ch != ')')
	  {
	    first = mallocWithErr (sizeof (list_t));
	    now = first;
	    while (ch != ')')
	      {
		if (ch == ' ' || ch == '\n')
		  {
		    ch = getcharWithExit ();
		    continue;
		  }
		now->car = parseAtomWithFirstChar (ch);
		now->cdr = (atom_t)
		{
		.label = LAMBDA,.pointerData =
		    mallocWithErr (sizeof (list_t))};
		last = now;
		now = now->cdr.pointerData;
		if (isFinFunc)
		  {
		    isFinFunc = false;
		    break;
		  }
		ch = getcharWithExit ();
	      }
	    last->cdr.pointerData = NULL;
	    free (now);
	  }
	return (atom_t)
	{
	.label = LAMBDA,.pointerData = first};
      }
    case '"':
      return parseString ();
    case '#':
      if ((ch = getchar ()) == -1)
	exit (0);

      switch (ch)
	{
	case 't':
	  return (atom_t)
	  {
	  .label = BOOL,.boolData = true};
	case 'f':
	  return (atom_t)
	  {
	  .label = BOOL,.boolData = false};
	case '\\':
	  return parseChar ();
	}
      fprintf (stderr, "not defined yet\n");
      abort ();
    default:
      return parseOtherAtomWithFirseChar (ch);
    }
}

atom_t
parseString (void)
{
  char ch;
  int t = 0;
  char *str;
  size_t strSize = mallocByte;
  atom_t ret;
  str = mallocWithErr (strSize);
  while ((ch = getchar ()) != -1 && ch != '"')
    {
      if ((t + 1) >= strSize)
	{
	  strSize += mallocByte;
	  str = reallocWithErr (str, strSize);
	}

      str[t] = ch;
      t++;
    }
  str[t] = '\0';

  ret.label = STRING;
  ret.stringData = str;

  return ret;
}

atom_t
parseChar (void)
{
  int t = 2;
  char c;
  char ch;
  char *str;
  c = getcharWithExit ();
  ch = getcharWithExit ();
  if (ch == ' ' || ch == '\n')
    return (atom_t)
    {
    .label = CHAR,.charData = c};

  size_t strSize = mallocByte;
  str = mallocWithErr (strSize);
  str[0] = c;
  str[1] = ch;
  while ((ch = getchar ()) != -1 && ch != '\n' && ch != ' ')
    {
      if ((t + 1) >= strSize)
	{
	  strSize += mallocByte;
	  str = reallocWithErr (str, strSize);
	}

      str[t] = ch;
      t++;
    }
  str[t] = '\0';
  printf ("error : unknown character #\\%s\n", str);
  return (atom_t)
  {
  .label = ERROR};
}

atom_t
parseOtherAtomWithFirseChar (char ch)
{
  int t = 0;
  char *str;
  size_t strSize = mallocByte;
  bool isDouble = true;
  bool isInt = true;
  atom_t ret;
  str = mallocWithErr (strSize);
  do
    {
      if (ch != '.' && (ch < '0' || ch > '9'))
	isDouble = isInt = false;
      if (ch == '.')
	{
	  if (!isInt)
	    isDouble = false;
	  else
	    isInt = false;
	}

      if ((t + 1) >= strSize)
	{
	  strSize += mallocByte;
	  str = reallocWithErr (str, strSize);
	}

      str[t] = ch;
      t++;
    }
  while ((ch = getchar ()) != -1 && ch != '\n' && ch != ' ' && ch != ')');
  str[t] = '\0';

  if (ch == ')')
    isFinFunc = true;

  if (isInt)
    {
      ret.label = INT;
      ret.intData = atoi (str);
      free (str);
    }
  else if (isDouble)
    {
      ret.label = DOUBLE;
      ret.doubleData = atof (str);
      free (str);
    }
  else
    ret = getData (str);


  return ret;
}
