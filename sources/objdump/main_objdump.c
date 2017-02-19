/*
** main.c for nmobjdump in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/sources/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Tue Feb 14 14:21:50 2017 Loic Lopez
** Last update Sun Feb 19 11:37:08 2017 Loic Lopez
*/

#include "nmobjdump.h"

int	main(int ac, char **av)
{
  void	*data;
  Elf64_Ehdr	*elf;
  Elf64_Shdr	*shdr;
  char	*strtab;
  int	fd;

  fd = check_program_args(ac, av);
  if ((data = mmap(NULL, filesize(fd), PROT_READ, MAP_SHARED, fd, 0)) == MAP_FAILED)
    print_error_and_exit("mmap", av[0]);
  elf = (Elf64_Ehdr *)data;
  shdr = (Elf64_Shdr *)(data + elf->e_shoff);
  strtab = (char *)(data + shdr[elf->e_shstrndx].sh_offset);

  int	i = 0;
  while (i < elf->e_shnum)
  {
    printf("%s\n", &strtab[shdr[i].sh_name]);
    i++;
  }

  return (0);
}
