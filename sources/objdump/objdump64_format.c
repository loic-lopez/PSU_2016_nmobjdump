/*
** objdump64_format.c for nmobjdump in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/sources/objdump/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Sat Feb 25 14:32:43 2017 Loic Lopez
** Last update Sat Feb 25 14:33:27 2017 Loic Lopez
*/

#include "my_objdump.h"

char	*getElf64(Elf64_Ehdr	*elf)
{
  if (elf->e_machine == EM_NONE)
    return "NONE";
  else if (elf->e_machine == EM_860 || elf->e_machine == EM_X86_64)
    return "x86-64";
  return ("NONE");
}

char	*getArch64(Elf64_Ehdr	*elf)
{
  if (elf->e_machine == EM_NONE)
    return "NONE";
  else if (elf->e_machine == EM_860)
    return "i860:x86-64";
  else if (elf->e_machine == EM_X86_64)
    return "i386:x86-64";
  return ("NONE");
}

void	objdump64_format(Elf64_Ehdr	*elf, char **av, size_t filesize, void *data)
{
  Elf64_Shdr	*shdr;
  char	*strtab;
  int	i = 0;
  bool	*flags;

  i = -1;
  !av[1] ? (av[1] = "a.out") : av[1];
  if (check_if_thereis_an_error64(elf, av, filesize))
    return;
  shdr = (Elf64_Shdr *)(data + elf->e_shoff);
  strtab = (char *)(data + shdr[elf->e_shstrndx].sh_offset);
  printf("     file format elf64-%s\n", getElf64(elf));
  flags = malloc(sizeof(bool) * 5);
  while (++i < 5)
    flags[i] = false;
  printf("architecture: %s, flags 0x%08lx:\n", getArch64(elf),
  get_flags64(elf, shdr, strtab, flags));
  print_flags64(flags);
  printf("start address 0x%016lx\n\n", elf->e_entry);
  print_objdump64(elf, shdr, strtab);
}
