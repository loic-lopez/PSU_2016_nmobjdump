/*
** filesize.c for filesize in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/sources/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Sat Feb 18 18:33:12 2017 Loic Lopez
** Last update Sat Feb 18 18:33:38 2017 Loic Lopez
*/

#include "nmobjdump.h"

int	filesize(int fd)
{
  return (lseek(fd, 0, SEEK_END));
}
