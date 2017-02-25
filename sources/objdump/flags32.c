/*
** flags32.c for nmobjdump in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/sources/objdump/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Sat Feb 25 14:47:17 2017 Loic Lopez
** Last update Sat Feb 25 14:50:31 2017 Loic Lopez
*/

#include "my_objdump.h"

size_t	count_flags(size_t total_flags, bool *flags, Elf32_Ehdr *elf)
{
  if (elf->e_type == ET_EXEC)
  {
    total_flags += EXEC_P;
    flags[0] = true;
  }
  if (elf->e_type == ET_DYN)
  {
    total_flags += DYNAMIC;
    flags[1] = true;
  }
  if (elf->e_type == ET_REL)
  {
    total_flags += HAS_RELOC;
    flags[2] = true;
  }
  if (elf->e_phnum != 0)
  {
     total_flags += D_PAGED;
     flags[3] = true;
  }
  return (total_flags);
}

size_t	get_flags32(Elf32_Ehdr *elf, Elf32_Shdr *shdr,
		    char *strtab, bool *flags)
{
  size_t total_flags;
  int	i;

  total_flags = 0;
  total_flags = count_flags(total_flags, flags, elf);
  i = -1;
  while (++i < elf->e_shnum)
  {
    if (strstr(&strtab[shdr[i].sh_name], "symtab") == 0)
     {
       total_flags += HAS_SYMS;
       flags[4] = true;
       break;
     }
  }
  return (total_flags);
}

void	print_flags32(bool *flags)
{
  flags[2] == true ? printf("HAS_RELOC, ") : 0;
  flags[0] == true ? printf("EXEC_P, ") : 0;
  flags[4] == true && flags[3] == true ? printf("HAS_SYMS, ") : 0;
  flags[4] == true && flags[3] == false ? printf("HAS_SYMS\n") : 0;
  flags[1]  == true ? printf("DYNAMIC, ") : 0;
  flags[3] == true ? printf("D_PAGED\n") : 0;
  free(flags);
}
