/*
** main_nm.c for nm in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/sources/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Tue Feb 14 14:31:25 2017 Loic Lopez
** Last update Sun Feb 19 12:33:13 2017 Loic Lopez
*/

#include "my_nm.h"

void	my_nm(char *file, char **av)
{
  void	*data;
  Elf32_Ehdr	*elf;
  int	fd;

  if ((fd = my_open(file, av)) == -1)
    return;
  if ((data = mmap(NULL, filesize(fd), PROT_READ, MAP_SHARED, fd, 0)) == MAP_FAILED)
    return (print_error_and_exit("mmap", av[0]));
  elf = (Elf32_Ehdr *)data;
  if (elf->e_ident[EI_CLASS] == ELFCLASS32)
    nm32_format(elf, av);
  else if (elf->e_ident[EI_CLASS] == ELFCLASS64)
    nm64_format((Elf64_Ehdr *)data, av);
  if (munmap(data, filesize(fd)) == -1)
    return (print_error_and_exit("munmap", av[0]));
  if (close(fd) == -1)
    return (print_error_and_exit("close", av[0]));
}

int main(int ac, char **av)
{
  int	i;

  i = 0;
  if (ac == 1)
    my_nm("a.out", av);
  else
    while (++i < ac)
      my_nm(av[i], av);

  return (EXIT_SUCCESS);
}
