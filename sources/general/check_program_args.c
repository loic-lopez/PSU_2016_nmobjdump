/*
** check_program_args.c for nmobjdump in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/sources/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Sat Feb 18 18:34:45 2017 Loic Lopez
** Last update Sun Feb 19 11:36:35 2017 Loic Lopez
*/

#include "nmobjdump.h"

int	check_program_args(int ac, char **av)
{
  int	fd;

  if (ac == 1)
  {
    if ((fd = open("a.out", O_RDONLY)) == -1)
      print_error_and_exit("a.out", av[0]);
  }
  else
    if ((fd = open(av[1], O_RDONLY)) == -1)
      print_error_and_exit(av[1], av[0]);

  return (fd);
}
