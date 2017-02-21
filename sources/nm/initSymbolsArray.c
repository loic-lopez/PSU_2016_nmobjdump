/*
** initSymbolsArray.c for nmobjdump.c in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/sources/nm/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Tue Feb 21 14:35:58 2017 Loic Lopez
** Last update Tue Feb 21 15:44:49 2017 Loic Lopez
*/

#include "my_nm.h"

int my_strcasecmp(char *s1, char *s2)
{
  while (*s1 && *s2)
    {
      if (tolower(*s1) != tolower(*s2))
	{
	  break;
	}
      ++s1;
      ++s2;
    }
  return (tolower(*s1) - tolower(*s2));
}

int	my_compare(const void *a, const void *b)
{
  char	**one;
  char	**two;

  one = (char	**)a;
  two = (char	**)b;

  return (my_strcasecmp(*one, *two));
}

char	**initSymbolsArray(Elf32_Shdr *current,
			   Elf32_Shdr *strtab, void *data)
{
  size_t	i;
  size_t	j;
  char	*name;
  Elf32_Sym	*symbol;
  char	**symbolName;

  i = -1;
  j = 0;
  symbolName = malloc(sizeof(Elf32_Sym) * current->sh_size
		      / current->sh_entsize);
  while (++i < current->sh_size / current->sh_entsize)
    {
      symbol = (Elf32_Sym *)(data + current->sh_offset
			     + i * sizeof(Elf32_Sym));
      name = (char *)(data + strtab->sh_offset + symbol->st_name);
      if (strcmp(name, "") > 0 && symbol->st_info != STT_FILE)
	{
	  name[0] == '_' && name[1] == '_' ? symbolName[j++] = &name[2] :
	    name[0] == '_' ?  symbolName[j++] = &name[1]
	    : (symbolName[j++] = name);
	}
    }
  symbolName[j] = NULL;
  qsort(symbolName, j, sizeof(char *), my_compare);
  return (symbolName);
}
