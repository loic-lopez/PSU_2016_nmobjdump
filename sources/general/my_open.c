/*
** check_program_args.c for nmobjdump in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/sources/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Sat Feb 18 18:34:45 2017 Loic Lopez
** Last update Sat Feb 25 14:22:06 2017 Loic Lopez
*/

#include "general.h"

int	my_open(char *file, char **av)
{
  int	fd;

  if ((fd = open(file, O_RDONLY)) == -1)
      fprintf(stderr, "%s: '%s': No such file\n", av[0], file);
  return (fd);
}
