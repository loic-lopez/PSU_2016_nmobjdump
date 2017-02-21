/*
** nm32_format.c for nmobjdump in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/sources/nm/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Sun Feb 19 12:15:02 2017 Loic Lopez
** Last update Tue Feb 21 15:00:01 2017 Loic Lopez
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



char	**initSymbolsArray(Elf32_Shdr *current, Elf32_Shdr *strtab, void *data, char	**symbolName);
int	my_compare(const void *a, const void *b);

void	show_32(Elf32_Shdr *current, Elf32_Shdr *strtab, void *data)
{
  size_t	i;
  size_t	j;
  char	*name;
  Elf32_Sym *symbol;
  char	**symbolName;
  char	*tmp;

  symbolName = NULL;
  symbolName = initSymbolsArray(current, strtab, data, symbolName);
  i = 0;
  j = 0;
  while (symbolName[j])
  {
    symbol = (Elf32_Sym *)(data + current->sh_offset + i * sizeof(Elf32_Sym));
    name = (char *)(data + strtab->sh_offset + symbol->st_name);
    if (strcmp(name, "") > 0 && symbol->st_info != STT_FILE)
      {
        name[0] == '_' && name[1] == '_' ? tmp = &name[2] :
        name[0] == '_' ? tmp = &name[1] : (tmp = name);
        if (strcmp(name, "data_start") == 0 && strcmp(symbolName[j], "data_start") == 0)
        {
          printf("%08x ", symbol->st_value);
          // print_symbol(elf, symbol);
          printf(" %s\n", "__data_start");
          j++;
        }
        else if (strcmp(name, "__data_start") == 0 && strcmp(symbolName[j], "data_start") == 0)
        {
          printf("%08x ", symbol->st_value);
          // print_symbol(elf, symbol);
          printf(" %s\n", "data_start");
          j++;
        }
        else if (strcmp(tmp, symbolName[j]) == 0)
        {
          if (symbol->st_value != 0)
           printf("%08x ", symbol->st_value);
          else
           printf("%*c", 8, ' ');
          // print_symbol(elf, symbol);
          printf(" %s\n", name);
          j++;
        }
        else if (strstr(name, symbolName[j]) != NULL && strlen(tmp) == strlen(symbolName[j]))
          {

            if (symbol->st_value != 0)
             printf("%08x ", symbol->st_value);
            else
             printf("%*c", 8, ' ');
            // print_symbol(elf, symbol);
            printf(" %s\n", name);
            j++;
          }
    }
    if (i == (current->sh_size / current->sh_entsize) - 1)
      i = 0;
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
