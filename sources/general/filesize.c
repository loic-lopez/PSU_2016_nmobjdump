/*
** filesize.c for filesize in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/sources/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Sat Feb 18 18:33:12 2017 Loic Lopez
** Last update Sun Feb 19 12:23:57 2017 Loic Lopez
*/

#include "general.h"

int	filesize(int fd)
{
  return (lseek(fd, 0, SEEK_END));
}
