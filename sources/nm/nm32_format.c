/*
** nm32_format.c for nmobjdump in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/sources/nm/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Sun Feb 19 12:15:02 2017 Loic Lopez
** Last update Tue Feb 21 01:26:16 2017 Loic Lopez
*/

#include "my_nm.h"

bool	check32_integrity(Elf32_Ehdr *elf)
{
  if (elf->e_ident[EI_MAG0] != ELFMAG0 || elf->e_ident[EI_MAG1] != ELFMAG1 ||
    elf->e_ident[EI_MAG2] != ELFMAG2 || elf->e_ident[EI_MAG3] != ELFMAG3 ||
    elf->e_type == ET_NONE)
    return (false);
  else
    return (true);
}


bool	is_truncated(size_t size, Elf32_Ehdr *elf)
{
  if (size <= sizeof(Elf32_Ehdr) || size <= elf->e_shoff)
    return (true);
  else
    return (false);
}

bool	checkOrder(char *str, char *str2)
{
  size_t j;
  size_t i;

  i = 0;
  j = 0;
  if (str[0] == '_' && str[1] == '_')
    i += 2;
  else if (str2[0] == '_' && str2[1] == '_')
    j += 2;
  else if (str[0] == '_')
    i += 1;
  else if (str2[0] == '_')
    j += 1;

  while (str[i] && str2[j])
  {
    if (tolower(str[i]) < tolower(str2[j]))
      return (true);
    j++;
    i++;
  }
  return (false);
}

bool	isNotOrdered(char *str, char *str2)
{
  size_t j;
  size_t i;

  i = 0;
  j = 0;
  if (str[0] == '_' && str[1] == '_')
    i += 2;
  else if (str2[0] == '_' && str2[1] == '_')
    j += 2;
  else if (str[0] == '_')
    i += 1;
  else if (str2[0] == '_')
    j += 1;

  while (str[i] && str2[j])
  {
    if (tolower(str[i]) > tolower(str2[j]))
      return (true);
    j++;
    i++;
  }

  return (false);
}

void	show_32(Elf32_Shdr *current, Elf32_Shdr *strtab, void *data)
{
  size_t	i;
  size_t	j;
  size_t	x;
  char *name;
  Elf32_Sym *symbol;
  char **symbolName;
  int	*symbols;


  i = 0;
  j = 0;
  symbolName = malloc(sizeof(Elf32_Sym *) * current->sh_size / current->sh_entsize);
  symbols = malloc(sizeof(Elf32_Sym *) * current->sh_size / current->sh_entsize);
  while (i < current->sh_size / current->sh_entsize)
    {
      symbol = (Elf32_Sym *)(data + current->sh_offset + i * sizeof(Elf32_Sym));
      name = (char *)(data + strtab->sh_offset + symbol->st_name);
      if (strcmp(name, "") > 0 && symbol->st_info != STT_FILE)
	     {
         symbols[j] = symbol->st_value;
         symbolName[j++] = strdup(name);
	     }
      i++;
    }
  symbolName[j] = NULL;
  i = 0;

  while (symbolName[i])
  {
    printf("%s\n", symbolName[i]);
    i++;
  }
  printf("\n");
  i = 0;
  while (1)
  {
    if (i > 0 && symbolName[i - 1] && checkOrder(symbolName[i], symbolName[i - 1]))
    {
      name = symbolName[i];
      symbolName[i] = symbolName[i - 1];
      symbolName[i - 1] = name;
    }
    else if (i < j && symbolName[i + 1] && checkOrder(symbolName[i], symbolName[i + 1]))
    {
      name = symbolName[i];
      symbolName[i] = symbolName[i + 1];
      symbolName[i + 1] = name;
    }
    if (i == j - 1)
      i = 0;
    x = 0;
    while (symbolName[x])
    {
      if (x < j && isNotOrdered(symbolName[x], symbolName[x + 1]))
        break;
      x++;
    }
    if (x == 1)
      break;
    i++;
  }

  i = 0;
  while (symbolName[i])
  {
    printf("%s\n", symbolName[i]);
    i++;
  }
}

// if (symbol->st_value != 0)
//  printf("%08x ", symbol->st_value);
// else
//  printf("%*c", 8, ' ');
// print_symbol(elf, symbol);
// printf(" %s\n", name);

Elf32_Shdr	*get_stringtab(Elf32_Shdr *shdr, Elf32_Ehdr *elf, void *data)
{
  size_t i;
  size_t offset;
  char *name;

  i = -1;
  while (++i < elf->e_shnum)
  {
   offset = elf->e_shoff + i * sizeof(Elf32_Shdr);
   name = (char *)(data + shdr[elf->e_shstrndx].sh_offset + shdr[i].sh_name);
   if (!strcmp(".strtab", name))
     return ((Elf32_Shdr *)(data + offset));
  }
  return (NULL);
}

void	nm32_format(Elf32_Ehdr *elf, char **av, size_t filesize, void *data)
{
  Elf32_Shdr *shdr;
  Elf32_Shdr *stringtab;
  size_t	offset;
  char	*name;
  int	i;

  if (!av[1])
    av[1] = "a.out";
  if (!check32_integrity(elf))
    return ((void)fprintf(stderr, "%s: Wrong header in: %s", av[0], av[1]));
  else if (elf->e_shstrndx == SHN_UNDEF)
    return ((void)fprintf(stderr, "%s: %s: Undefined reference to header section tables", av[0], av[1]));
  else if (is_truncated(filesize, elf))
    return ((void)fprintf(stderr, "%s: %s: File truncated\n", av[0], av[1]));
  shdr = (Elf32_Shdr *)(data + elf->e_shoff);
  if ((stringtab = get_stringtab(shdr, elf, data)) == NULL)
    return ((void)fprintf(stderr, "%s: %s: No symbols\n", av[0], av[1]));
  i = -1;
  while (++i < elf->e_shnum)
    {
      offset = elf->e_shoff + i * sizeof(Elf32_Shdr);
      name = (char *)(data + shdr[elf->e_shstrndx].sh_offset + shdr[i].sh_name);
      if (!strcmp(".symtab", name))
        show_32((Elf32_Shdr *)(data + offset), stringtab, data);
    }
}
