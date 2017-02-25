/*
** show32.c for nmobjdump in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/sources/nm/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Tue Feb 21 15:40:36 2017 Loic Lopez
** Last update Fri Feb 24 23:28:41 2017 Loic Lopez
*/

#include "my_nm.h"

char	print_symbol_letter(Elf32_Sym *symbol, Elf32_Shdr *shdr, char *name)
{
  char c;

  c = get_symbol32(symbol);
  c == '?' ? c = get_shdr_symbols32(shdr, symbol) : c;
  if (c == '?')
    c = 'T';
  symbol->st_info == STT_NOTYPE ? c = 'B' : c;
  ELF32_ST_BIND(symbol->st_info) == STB_LOCAL ? c += 32 : c;
  if (strcmp(name, "__data_start") == 0)
    c = 'D';
  else if (strcmp(name, "data_start") == 0)
    c = 'W';
  else if (strstr(name, "__init") != NULL)
    c = 't';
  else if (strcmp(name, "__GNU_EH_FRAME_HDR") == 0)
    c = 'r';
  return (c);
}

int	print_32(Elf32_Sym *symbol, char *name, int j, Elf32_Shdr *shdr)
{
  char	c;

  c = print_symbol_letter(symbol, shdr, name);
  if (c != 'w' && c != 'U')
    printf("%08x ", symbol->st_value);
  else
    printf("%*c", 9, ' ');
  printf("%c", c);
  printf(" %s\n", name);
  j++;
  return (j);
}

int	check_and_print32(void *tab[3], char *symbolName,
			  int j, Elf32_Sym *symbol)
{
  char	*name;
  char	*tmp;
  Elf32_Shdr *shdr;

  name = (char *)tab[0];
  tmp = (char *)tab[1];
  shdr = (Elf32_Shdr *)tab[2];
  if (strcmp(name, "data_start") == 0
      && strcmp(symbolName, "data_start") == 0)
    j = print_32(symbol, "__data_start", j, shdr);
  else if (strcmp(name, "__data_start") == 0
	   && strcmp(symbolName, "data_start") == 0)
    j = print_32(symbol, "data_start", j, shdr);
  else if (strstr(name, symbolName) != NULL
	   && strlen(tmp) == strlen(symbolName))
    j = print_32(symbol, name, j, shdr);
  return (j);
}

char	*get_name(char *tmp, char *name)
{
  name[0] == '_' && name[1] == '_' ? tmp = &name[2] :
    name[0] == '_' ? tmp = &name[1] : (tmp = name);
  return (tmp);
}

void	show_32(Elf32_Shdr *current, Elf32_Shdr *strtab,
		void *data, Elf32_Shdr *shdr)
{
  size_t	i;
  size_t	j;
  char	*name;
  Elf32_Sym *sym;
  char	**symbolName;
  char	*tmp;
  void	*tab[3];

  symbolName = initSymbolsArray(current, strtab, data);
  i = j = 0;
  while (symbolName[j])
    {
      sym = (Elf32_Sym *)(data + current->sh_offset + i * sizeof(Elf32_Sym));
      name = (char *)(data + strtab->sh_offset + sym->st_name);
      if (strcmp(name, "") > 0 && sym->st_info != STT_FILE)
	{
	  tmp = get_name(tmp, name);
	  tab[0] = name;
	  tab[1] = tmp;
	  tab[2] = shdr;
	  j = check_and_print32(tab, symbolName[j], j, sym);
	}
      i == (current->sh_size / current->sh_entsize) - 1 ? i = 0 : i++;
    }
  free(symbolName);
}
