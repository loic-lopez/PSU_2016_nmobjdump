/*
** main.c for nmobjdump in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/sources/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Tue Feb 14 14:21:50 2017 Loic Lopez
** Last update Sun Feb 19 12:22:57 2017 Loic Lopez
*/

#include "my_objdump.h"

void	my_objdump(char *file, char **av)
{
  void	*data;
  Elf32_Ehdr	*elf;
  int	fd;

  fd = my_open(file, av);
  if ((data = mmap(NULL, filesize(fd), PROT_READ, MAP_SHARED, fd, 0)) == MAP_FAILED)
    print_error_and_exit("mmap", av[0]);
  elf = (Elf32_Ehdr *)data;
  elf = elf;
}

int	main(int ac, char **av)
{
  int	i;

  i = 0;
  if (ac == 1)
    my_objdump("a.out", av);
  else
    while (++i < ac)
      my_objdump(av[i], av);

  return (0);
}
