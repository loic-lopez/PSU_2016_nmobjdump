/*
** check_if_thereis_an_error64.c for nmobjdump.c in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/sources/general/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Fri Feb 24 23:39:22 2017 Loic Lopez
** Last update Fri Feb 24 23:42:41 2017 Loic Lopez
*/

#include "general.h"

bool	check64_integrity(Elf64_Ehdr *elf)
{
  if (elf->e_ident[EI_MAG0] != ELFMAG0 || elf->e_ident[EI_MAG1] != ELFMAG1 ||
    elf->e_ident[EI_MAG2] != ELFMAG2 || elf->e_ident[EI_MAG3] != ELFMAG3 ||
    elf->e_type == ET_NONE)
    return (false);
  else
    return (true);
}

bool	is_truncated64(size_t size, Elf64_Ehdr *elf)
{
  if (size <= sizeof(Elf64_Ehdr) || size <= elf->e_shoff)
    return (true);
  else
    return (false);
}

bool	check_if_thereis_an_error64(Elf64_Ehdr *elf, char **av,
  size_t filesize)
{
  if (!check64_integrity(elf))
  {
    fprintf(stderr, "%s: Wrong header in: %s", av[0], av[1]);
    return (true);
  }
  else if (elf->e_shstrndx == SHN_UNDEF)
  {
    fprintf(stderr,
      "%s: %s: Undefined reference to header section tables", av[0], av[1]);
    return (true);
  }
  else if (is_truncated64(filesize, elf))
  {
    fprintf(stderr, "%s: %s: File truncated\n", av[0], av[1]);
    return (true);
  }
  return (false);
}
