/*
** check_program_args.c for nmobjdump in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/sources/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Sat Feb 18 18:34:45 2017 Loic Lopez
** Last update Sat Feb 18 18:36:00 2017 Loic Lopez
*/

#include "nmobjdump.h"

int	check_program_args(int ac, char **av)
{
  int	fd;
  
  if (ac == 1)
  {
    if ((fd = open("a.out", O_RDONLY)) == -1)
    {
      perror("a.out");
      exit(1);
    }
  }
  else
  {
    if ((fd = open(av[1], O_RDONLY)) == -1)
    {
      perror(av[1]);
      exit(1);
    }
  }
  return (fd);
}
