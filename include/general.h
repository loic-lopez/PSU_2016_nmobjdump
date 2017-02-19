/*
** general.h for nmobjdump.h in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/include/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Sun Feb 19 12:23:16 2017 Loic Lopez
** Last update Sun Feb 19 12:26:28 2017 Loic Lopez
*/

#ifndef GENERAL_H_
#define GENERAL_H_

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

void	print_error_and_exit(const char *str, const char *progname);

#endif /* !GENERAL_H_ */
