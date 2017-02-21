/*
** show32.c for nmobjdump in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/sources/nm/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Tue Feb 21 15:40:36 2017 Loic Lopez
** Last update Tue Feb 21 15:52:29 2017 Loic Lopez
*/

#include "my_nm.h"

int	print_32(Elf32_Sym *symbol, char *name, int j)
{
  if (symbol->st_value != 0)
    printf("%08x ", symbol->st_value);
  else
    printf("%*c", 8, ' ');
  // print_symbol(elf, symbol);
  printf(" %s\n", name);
  j++;
  return (j);
}

int	check_and_print32(char *tab[2], char *symbolName,
			  int j, Elf32_Sym *symbol)
{
  if (strcmp(tab[0], "data_start") == 0
      && strcmp(symbolName, "data_start") == 0)
    j = print_32(symbol, "__data_start", j);
  else if (strcmp(tab[0], "__data_start") == 0
	   && strcmp(symbolName, "data_start") == 0)
    j = print_32(symbol, "data_start", j);
  else if (strstr(tab[0], symbolName) != NULL
	   && strlen(tab[1]) == strlen(symbolName))
    j = print_32(symbol, tab[0], j);
  return (j);
}

void	show_32(Elf32_Shdr *current, Elf32_Shdr *strtab, void *data)
{
  size_t	i;
  size_t	j;
  char	*name;
  Elf32_Sym *symbol;
  char	**symbolName;
  char	*tmp;
  char	*tab[2];

  symbolName = initSymbolsArray(current, strtab, data);
  i = j = 0;
  while (symbolName[j])
    {
      symbol = (Elf32_Sym *)(data + current->sh_offset + i * sizeof(Elf32_Sym));
      name = (char *)(data + strtab->sh_offset + symbol->st_name);
      if (strcmp(name, "") > 0 && symbol->st_info != STT_FILE)
	{
	  name[0] == '_' && name[1] == '_' ? tmp = &name[2] :
	    name[0] == '_' ? tmp = &name[1] : (tmp = name);
	  tab[0] = name;
	  tab[1] = tmp;
	  j = check_and_print32(tab, symbolName[j], j, symbol);
	}
      i == (current->sh_size / current->sh_entsize) - 1 ? i = 0 : i++;
    }
  free(symbolName);
}
