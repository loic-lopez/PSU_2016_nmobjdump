/*
** show32.c for nmobjdump in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/sources/nm/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Tue Feb 21 15:40:36 2017 Loic Lopez
** Last update Tue Feb 21 20:42:20 2017 Loic Lopez
*/

#include "my_nm.h"


char	isuchar(Elf32_Sym *symbol)
{
  char c;

  c = '?';
  if (ELF32_ST_BIND(symbol->st_info) == STB_GNU_UNIQUE)
    c = 'u';
  else if (ELF32_ST_BIND(symbol->st_info) == STB_WEAK)
    {
      c = 'W';
      if (symbol->st_shndx == SHN_UNDEF)
	c = 'w';
    }
  else if (ELF32_ST_BIND(symbol->st_info) == STB_WEAK &&
	   ELF32_ST_TYPE(symbol->st_info) == STT_OBJECT)
    {
      c = 'V';
      if (symbol->st_shndx == SHN_UNDEF)
	c = 'v';
    }
  else if (symbol->st_shndx == SHN_UNDEF)
    c = 'U';
  else if (symbol->st_shndx == SHN_ABS)
    c = 'A';
  else if (symbol->st_shndx == SHN_COMMON)
    c = 'C';
  return (c);
}

char	isvwchar(Elf32_Shdr *shdr, Elf32_Sym *symbol)
{
  char c;

  c = '?';
  if (shdr[symbol->st_shndx].sh_type == SHT_NOBITS
      && shdr[symbol->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
    c = 'B';
  else if (shdr[symbol->st_shndx].sh_type == SHT_PROGBITS
	   && shdr[symbol->st_shndx].sh_flags == SHF_ALLOC)
    c = 'R';
  else if (shdr[symbol->st_shndx].sh_type == SHT_PROGBITS
	   && shdr[symbol->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
    c = 'D';
  else if (shdr[symbol->st_shndx].sh_type == SHT_PROGBITS
	   && shdr[symbol->st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
    c = 'T';
  else if (shdr[symbol->st_shndx].sh_type == SHT_DYNAMIC)
    c = 'D';
  return (c);
}


void	print_symbol_letter(Elf32_Sym *symbol, Elf32_Shdr *shdr, char *name)
{
  char c;

  c = isuchar(symbol);
  if (c == '?')
    c = isvwchar(shdr, symbol);
  if (c == '?')
    c = 'T';
  if (symbol->st_info == STT_NOTYPE)
    c = 'B';
  if (ELF32_ST_BIND(symbol->st_info) == STB_LOCAL)
    c += 32;
  if (strcmp(name, "__data_start") == 0)
    c = 'D';
  else if (strcmp(name, "data_start") == 0)
    c = 'W';
  printf("%c", c);
}

int	print_32(Elf32_Sym *symbol, char *name, int j, Elf32_Shdr *shdr)
{
  if (symbol->st_value != 0)
    printf("%08x ", symbol->st_value);
  else
    printf("%*c", 9, ' ');
  print_symbol_letter(symbol, shdr, name);
  printf(" %s\n", name);
  j++;
  return (j);
}

int	check_and_print32(char *tab[2], char *symbolName,
			  int j, Elf32_Sym *symbol, Elf32_Shdr *shdr)
{
  if (strcmp(tab[0], "data_start") == 0
      && strcmp(symbolName, "data_start") == 0)
    j = print_32(symbol, "__data_start", j, shdr);
  else if (strcmp(tab[0], "__data_start") == 0
	   && strcmp(symbolName, "data_start") == 0)
    j = print_32(symbol, "data_start", j, shdr);
  else if (strstr(tab[0], symbolName) != NULL
	   && strlen(tab[1]) == strlen(symbolName))
    j = print_32(symbol, tab[0], j, shdr);
  return (j);
}

void	show_32(Elf32_Shdr *current, Elf32_Shdr *strtab, void *data, Elf32_Shdr *shdr)
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
	  j = check_and_print32(tab, symbolName[j], j, symbol, shdr);
	}
      i == (current->sh_size / current->sh_entsize) - 1 ? i = 0 : i++;
    }
  free(symbolName);
}
