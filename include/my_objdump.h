/*
** nmobjdump.h for nmobjdump in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/include/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Tue Feb 14 14:22:22 2017 Loic Lopez
** Last update Sun Feb 19 12:45:15 2017 Loic Lopez
*/

#ifndef MY_OBJDUMP_H_
#define MY_OBJDUMP_H_

#include <elf.h>
#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>

#include "flags.h"

int	filesize(int fd);
int	my_open(char *file, char **av);
void	print_error_and_exit(const char *str, const char *progname);

#endif /* !MY_OBJDUMP_H_ */
