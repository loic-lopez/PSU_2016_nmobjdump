/*
** nm64_format.c for nmobjdump in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/sources/nm/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Sun Feb 19 12:14:48 2017 Loic Lopez
** Last update Fri Feb 24 23:43:04 2017 Loic Lopez
*/

#include "my_nm.h"

Elf64_Shdr	*get_stringtab64(Elf64_Shdr *shdr, Elf64_Ehdr *elf, void *data)
{
  size_t i;
  size_t offset;
  char *name;

  i = -1;
  while (++i < elf->e_shnum)
    {
      offset = elf->e_shoff + i * sizeof(Elf64_Shdr);
      name = (char *)(data + shdr[elf->e_shstrndx].sh_offset
		      + shdr[i].sh_name);
      if (!strcmp(".strtab", name))
	return ((Elf64_Shdr *)(data + offset));
    }
  return (NULL);
}

void	nm64_format(Elf64_Ehdr *elf, char **av, size_t filesize, void *data)
{
  Elf64_Shdr *shdr;
  Elf64_Shdr *stringtab;
  size_t	offset;
  char	*name;
  int	i;

  !av[1] ? (av[1] = "a.out") : av[1];
  if (check_if_thereis_an_error64(elf, av, filesize))
    return;
  shdr = (Elf64_Shdr *)(data + elf->e_shoff);
  if ((stringtab = get_stringtab64(shdr, elf, data)) == NULL)
    return ((void)fprintf(stderr, "%s: %s: No symbols\n", av[0], av[1]));
  i = -1;
  while (++i < elf->e_shnum)
    {
      offset = elf->e_shoff + i * sizeof(Elf64_Shdr);
      name = (char *)(data
		      + shdr[elf->e_shstrndx].sh_offset + shdr[i].sh_name);
      if (!strcmp(".symtab", name))
        show_64((Elf64_Shdr *)(data + offset), stringtab, data, shdr);
    }
}
