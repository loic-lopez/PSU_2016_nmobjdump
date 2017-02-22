/*
** nm64_format.c for nmobjdump in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/sources/nm/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Sun Feb 19 12:14:48 2017 Loic Lopez
** Last update Wed Feb 22 19:06:07 2017 Loic Lopez
*/

#include "my_nm.h"

bool	check64_integrity(Elf64_Ehdr *elf)
{
  if (elf->e_ident[EI_MAG0] != ELFMAG0 || elf->e_ident[EI_MAG1] != ELFMAG1 ||
    elf->e_ident[EI_MAG2] != ELFMAG2 || elf->e_ident[EI_MAG3] != ELFMAG3 ||
    elf->e_type == ET_NONE)
    return (false);
  else
    return (true);
}

bool	is_truncated64(size_t size, Elf64_Ehdr *elf)
{
  if (size <= sizeof(Elf64_Ehdr) || size <= elf->e_shoff)
    return (true);
  else
    return (false);
}

Elf64_Shdr	*get_stringtab64(Elf64_Shdr *shdr, Elf64_Ehdr *elf, void *data)
{
  size_t i;
  size_t offset;
  char *name;

  i = -1;
  while (++i < elf->e_shnum)
  {
   offset = elf->e_shoff + i * sizeof(Elf64_Shdr);
   name = (char *)(data + shdr[elf->e_shstrndx].sh_offset + shdr[i].sh_name);
   if (!strcmp(".strtab", name))
     return ((Elf64_Shdr *)(data + offset));
  }
  return (NULL);
}

bool	check_if_thereis_an_error64(Elf64_Ehdr *elf, char **av,
  size_t filesize)
{
  if (!check64_integrity(elf))
  {
    fprintf(stderr, "%s: Wrong header in: %s", av[0], av[1]);
    return (true);
  }
  else if (elf->e_shstrndx == SHN_UNDEF)
  {
    fprintf(stderr,
      "%s: %s: Undefined reference to header section tables", av[0], av[1]);
    return (true);
  }
  else if (is_truncated64(filesize, elf))
  {
    fprintf(stderr, "%s: %s: File truncated\n", av[0], av[1]);
    return (true);
  }
  return (false);
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
