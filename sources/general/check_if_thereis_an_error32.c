/*
** check_if_thereis_an_error32.c for nmobjdump in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/sources/general/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Fri Feb 24 23:45:35 2017 Loic Lopez
** Last update Fri Feb 24 23:46:12 2017 Loic Lopez
*/

#include "general.h"

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

bool	check_if_thereis_an_error(Elf32_Ehdr *elf, char **av, size_t filesize)
{
  if (!check32_integrity(elf))
    {
      fprintf(stderr, "%s: Wrong header in: %s", av[0], av[1]);
      return (true);
    }
  else if (elf->e_shstrndx == SHN_UNDEF)
    {
      fprintf(stderr,
	      "%s: %s: Undefined reference to header section tables",
	      av[0], av[1]);
      return (true);
    }
  else if (is_truncated(filesize, elf))
    {
      fprintf(stderr, "%s: %s: File truncated\n", av[0], av[1]);
      return (true);
    }
  return (false);
}
