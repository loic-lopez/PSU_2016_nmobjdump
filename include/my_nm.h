/*
** my_nm.h for my_nm.h in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/include/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Sun Feb 19 12:16:14 2017 Loic Lopez
** Last update Sun Feb 19 12:45:31 2017 Loic Lopez
*/

#ifndef MY_NM_H_
#define MY_NM_H_

#include <elf.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>

#include "flags.h"

int	filesize(int fd);
int	my_open(char *file, char **av);
void	print_error_and_exit(const char *str, const char *progname);
void	nm32_format(Elf32_Ehdr *, char **av);
void	nm64_format(Elf64_Ehdr *, char **av);

#endif /* !MY_NM_H_ */