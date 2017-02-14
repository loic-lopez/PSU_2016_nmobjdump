/*
** main.c for nmobjdump in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/sources/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Tue Feb 14 14:21:50 2017 Loic Lopez
** Last update Tue Feb 14 16:29:15 2017 Loic Lopez
*/

#include "nmobjdump.h"

int	main(int ac, char **av)
{
  (void)ac, (void)av;

  if (is_64bit())
    printf("64BITS\n");
  else if (is_32bit())
    printf("32BITS\n");

  return 0;
}
