/*
** main.c for nmobjdump in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/sources/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Tue Feb 14 14:21:50 2017 Loic Lopez
** Last update Sun Feb 26 19:11:04 2017 Loic Lopez
*/

#include "my_objdump.h"

void	my_objdump(char *file, char **av)
{
  void	*data;
  Elf32_Ehdr	*elf;
  int	fd;

  if ((fd = my_open(file, av)) == -1)
    return;
  if ((data = mmap(NULL, filesize(fd), PROT_READ,
       MAP_SHARED, fd, 0)) == MAP_FAILED)
    return (print_error_and_exit("mmap", av[0]));
  elf = (Elf32_Ehdr *)data;
  elf->e_ident[EI_CLASS] == ELFCLASS32 ?
    (printf("\n%s:", file), objdump32_format(elf, av, filesize(fd), data)) :
    elf->e_ident[EI_CLASS] == ELFCLASS64 ?
    (printf("\n%s:", file),
     objdump64_format((Elf64_Ehdr *)data, av, filesize(fd), data)) :
    fprintf(stderr, "%s: %s: File format not recognized\n", av[0], file);
  if (munmap(data, filesize(fd)) == -1)
    return (print_error_and_exit("munmap", av[0]));
  if (close(fd) == -1)
    return (print_error_and_exit("close", av[0]));
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
