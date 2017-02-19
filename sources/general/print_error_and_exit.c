/*
** error_and_exit.c for nmobjdump in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/sources/general/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Sun Feb 19 11:29:42 2017 Loic Lopez
** Last update Sun Feb 19 12:24:06 2017 Loic Lopez
*/

#include "general.h"

void	print_error_and_exit(const char *str, const char *progname)
{
  write(2, progname, strlen(progname));
  write(2, " ", 1);
  perror(str);
}
