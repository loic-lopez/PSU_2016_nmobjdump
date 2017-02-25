/*
** nmobjdump.h for nmobjdump in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/include/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Tue Feb 14 14:22:22 2017 Loic Lopez
** Last update Sat Feb 25 14:52:02 2017 Loic Lopez
*/

#ifndef MY_OBJDUMP_H_
#define MY_OBJDUMP_H_

#include <elf.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "flags.h"

int	filesize(int fd);
int	my_open(char *file, char **av);
void	print_error_and_exit(const char *str, const char *progname);
bool	check_if_thereis_an_error64(Elf64_Ehdr *elf, char **av,
  size_t filesize);
bool	must_i_print_it64(Elf64_Shdr *current, char *name);
void	objdump64_format(Elf64_Ehdr	*elf, char **av,
			 size_t filesize, void *data);
size_t	get_flags64(Elf64_Ehdr *elf, Elf64_Shdr *shdr,
		    char *strtab, bool *flags);
void	print_flags64(bool *flags);
void	print_objdump64(Elf64_Ehdr *elf, Elf64_Shdr *shdr, char *strtab);
bool	check_if_thereis_an_error(Elf32_Ehdr *elf, char **av,
				  size_t filesize);
void	objdump32_format(Elf32_Ehdr	*elf, char **av,
			 size_t filesize, void *data);
bool	must_i_print_it32(Elf32_Shdr *current, char *name);
size_t	get_flags32(Elf32_Ehdr *elf, Elf32_Shdr *shdr,
		    char *strtab, bool *flags);
void	print_flags32(bool *flags);
void	print_objdump32(Elf32_Ehdr *elf, Elf32_Shdr *shdr, char *strtab);

#endif /* !MY_OBJDUMP_H_ */
