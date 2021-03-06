/*
** my_nm.h for my_nm.h in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/include/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Sun Feb 19 12:16:14 2017 Loic Lopez
** Last update Sat Feb 25 14:34:32 2017 Loic Lopez
*/

#ifndef MY_NM_H_
#define MY_NM_H_

#include <elf.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "flags.h"

int	filesize(int fd);
int	my_open(char *file, char **av);
void	print_error_and_exit(const char *str, const char *progname);
void	nm32_format(Elf32_Ehdr *, char **av, size_t filesize, void *data);
char	**initSymbolsArray(Elf32_Shdr *current,
			   Elf32_Shdr *strtab, void *data);
void	show_32(Elf32_Shdr *current, Elf32_Shdr *strtab,
		void *data, Elf32_Shdr *shdr);
char	get_symbol32(Elf32_Sym *symbol);
char	get_shdr_symbols32(Elf32_Shdr *shdr, Elf32_Sym *symbol);
bool	check_if_thereis_an_error(Elf32_Ehdr *elf, char **av,
				  size_t filesize);
void	nm64_format(Elf64_Ehdr *elf, char **av, size_t filesize, void *data);
char	get_symbol64(Elf64_Sym *symbol);
char	get_shdr_symbols64(Elf64_Shdr *shdr, Elf64_Sym *symbol);
void	show_64(Elf64_Shdr *current, Elf64_Shdr *strtab, void *data,
		Elf64_Shdr *shdr);
bool	check_if_thereis_an_error64(Elf64_Ehdr *elf, char **av,
				    size_t filesize);
char	*get_name(char *tmp, char *name);
char	**initSymbolsArray64(Elf64_Shdr *current,
			     Elf64_Shdr *strtab, void *data);

#endif /* !MY_NM_H_ */
