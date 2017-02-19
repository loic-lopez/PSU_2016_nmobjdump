/*
** nmobjdump.h for nmobjdump in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/include/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Tue Feb 14 14:22:22 2017 Loic Lopez
** Last update Sun Feb 19 11:37:27 2017 Loic Lopez
*/

#ifndef NMOBJDUMP_H_
#define NMOBJDUMP_H_

#include <elf.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>

#include "flags.h"

int	filesize(int fd);
int	check_program_args(int ac, char **av);
void	print_error_and_exit(const char *str, const char *progname);

#endif /* !NMOBJDUMP_H_ */
