/*
** must_i_print_it.c for nmobjdump in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/sources/objdump/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Sat Feb 25 14:35:54 2017 Loic Lopez
** Last update Sat Feb 25 14:36:22 2017 Loic Lopez
*/

#include "my_nm.h"

bool	must_i_print_it64(Elf64_Shdr *current, char *name)
{
  if ((current->sh_type != SHT_NOBITS && current->sh_flags & SHF_ALLOC)
  || !strcmp(".stabstr", name))
    return (true);
  if (!current->sh_size || current->sh_type == SHT_NOBITS
    || current->sh_type == SHT_REL || strstr(name, ".rela")
    || current->sh_type == SHT_SYMTAB || current->sh_type == SHT_STRTAB)
    return (false);
  return (true);
}

bool	must_i_print_it32(Elf32_Shdr *current, char *name)
{
  if ((current->sh_type != SHT_NOBITS && current->sh_flags & SHF_ALLOC)
  || !strcmp(".stabstr", name))
    return (true);
  if (!current->sh_size || current->sh_type == SHT_NOBITS
    || current->sh_type == SHT_REL || strstr(name, ".rela")
    || current->sh_type == SHT_SYMTAB || current->sh_type == SHT_STRTAB)
    return (false);
  return (true);
}
