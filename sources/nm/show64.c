/*
** show64.c for nmobjdump in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/sources/nm/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Wed Feb 22 18:31:15 2017 Loic Lopez
** Last update Wed Feb 22 18:58:12 2017 Loic Lopez
*/

#include "my_nm.h"

void	print_symbol_letter64(Elf64_Sym *symbol, Elf64_Shdr *shdr, char *name)
{
  char c;

  c = get_symbol64(symbol);
  c == '?' ? c = get_shdr_symbols64(shdr, symbol) : c;
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
  printf("%c", c);
}

int	print_64(Elf64_Sym *symbol, char *name, int j, Elf64_Shdr *shdr)
{
  if (symbol->st_value != 0)
    printf("%016lx ", symbol->st_value);
  else
    printf("%*c", 17, ' ');
  print_symbol_letter64(symbol, shdr, name);
  printf(" %s\n", name);
  j++;
  return (j);
}

int	check_and_print64(void *tab[3], char *symbolName,
			  int j, Elf64_Sym *symbol)
{
  char	*name;
  char	*tmp;
  Elf64_Shdr *shdr;

  name = (char *)tab[0];
  tmp = (char *)tab[1];
  shdr = (Elf64_Shdr *)tab[2];
  if (strcmp(name, "data_start") == 0
      && strcmp(symbolName, "data_start") == 0)
    j = print_64(symbol, "__data_start", j, shdr);
  else if (strcmp(name, "__data_start") == 0
	   && strcmp(symbolName, "data_start") == 0)
    j = print_64(symbol, "data_start", j, shdr);
  else if (strstr(name, symbolName) != NULL
	   && strlen(tmp) == strlen(symbolName))
    j = print_64(symbol, name, j, shdr);
  return (j);
}

void	show_64(Elf64_Shdr *current, Elf64_Shdr *strtab,
  void *data, Elf64_Shdr *shdr)
{
  size_t	i;
  size_t	j;
  char	*name;
  Elf64_Sym *sym;
  char	**symbolName;
  char	*tmp;
  void	*tab[3];

  symbolName = initSymbolsArray64(current, strtab, data);
  i = j = 0;
  while (symbolName[j])
    {
      sym = (Elf64_Sym *)(data + current->sh_offset + i * sizeof(Elf64_Sym));
      name = (char *)(data + strtab->sh_offset + sym->st_name);
      if (strcmp(name, "") > 0 && sym->st_info != STT_FILE)
	{
	  tmp = get_name(tmp, name);
	  tab[0] = name;
	  tab[1] = tmp;
	  tab[2] = shdr;
	  j = check_and_print64(tab, symbolName[j], j, sym);
	}
      i == (current->sh_size / current->sh_entsize) - 1 ? i = 0 : i++;
    }
  free(symbolName);
}
