/*
** 64_32bit.c for nmobjdump in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/sources/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Tue Feb 14 15:21:36 2017 Loic Lopez
** Last update Tue Feb 14 16:20:29 2017 Loic Lopez
*/

#include "nmobjdump.h"

bool	is_32bit()
{
  return (sizeof(int *) == 4);
}

bool	is_64bit()
{
  return (sizeof(int *) == 8);
}
