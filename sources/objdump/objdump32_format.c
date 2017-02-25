/*
** objdump32_format.c for nmobjdump in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/sources/objdump/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Sat Feb 25 14:44:58 2017 Loic Lopez
** Last update Sat Feb 25 15:07:13 2017 Loic Lopez
*/

#include "my_objdump.h"

char	*getElf32(Elf32_Ehdr	*elf)
{
  if (elf->e_machine == EM_NONE)
    return "NONE";
  else if (elf->e_machine == EM_386)
    return "i386";
  return ("NONE");
}

char	*getArch32(Elf32_Ehdr	*elf)
{
  if (elf->e_machine == EM_NONE)
    return "NONE";
  else if (elf->e_machine == EM_386)
    return "i386";
  return ("NONE");
}

void	objdump32_format(Elf32_Ehdr	*elf, char **av, size_t filesize, void *data)
{
  Elf32_Shdr	*shdr;
  char	*strtab;
  int	i = 0;
  bool	*flags;

  i = -1;
  !av[1] ? (av[1] = "a.out") : av[1];
  if (check_if_thereis_an_error(elf, av, filesize))
    return;
  shdr = (Elf32_Shdr *)(data + elf->e_shoff);
  strtab = (char *)(data + shdr[elf->e_shstrndx].sh_offset);
  printf("     file format elf32-%s\n", getElf32(elf));
  flags = malloc(sizeof(bool) * 5);
  while (++i < 5)
    flags[i] = false;
  printf("architecture: %s, flags 0x%08lx:\n", getArch32(elf),
  get_flags32(elf, shdr, strtab, flags));
  print_flags32(flags);
  printf("start address 0x%08x\n\n", elf->e_entry);
  print_objdump32(elf, shdr, strtab);
}
