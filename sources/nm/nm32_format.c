/*
** nm32_format.c for nmobjdump in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/sources/nm/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Sun Feb 19 12:15:02 2017 Loic Lopez
** Last update Fri Feb 24 23:46:09 2017 Loic Lopez
*/

#include "my_nm.h"

Elf32_Shdr	*get_stringtab(Elf32_Shdr *shdr, Elf32_Ehdr *elf, void *data)
{
  size_t i;
  size_t offset;
  char *name;

  i = -1;
  while (++i < elf->e_shnum)
  {
   offset = elf->e_shoff + i * sizeof(Elf32_Shdr);
   name = (char *)(data + shdr[elf->e_shstrndx].sh_offset + shdr[i].sh_name);
   if (!strcmp(".strtab", name))
     return ((Elf32_Shdr *)(data + offset));
  }
  return (NULL);
}

void	nm32_format(Elf32_Ehdr *elf, char **av, size_t filesize, void *data)
{
  Elf32_Shdr *shdr;
  Elf32_Shdr *stringtab;
  size_t	offset;
  char	*name;
  int	i;

  !av[1] ? (av[1] = "a.out") : av[1];
  if (check_if_thereis_an_error(elf, av, filesize))
    return;
  shdr = (Elf32_Shdr *)(data + elf->e_shoff);
  if ((stringtab = get_stringtab(shdr, elf, data)) == NULL)
    return ((void)fprintf(stderr, "%s: %s: No symbols\n", av[0], av[1]));
  i = -1;
  while (++i < elf->e_shnum)
    {
      offset = elf->e_shoff + i * sizeof(Elf32_Shdr);
      name = (char *)(data
        + shdr[elf->e_shstrndx].sh_offset + shdr[i].sh_name);
      if (!strcmp(".symtab", name))
        show_32((Elf32_Shdr *)(data + offset), stringtab, data, shdr);
    }
}
