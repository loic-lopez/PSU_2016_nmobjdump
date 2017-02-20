/*
** nm32_format.c for nmobjdump in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/sources/nm/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Sun Feb 19 12:15:02 2017 Loic Lopez
** Last update Mon Feb 20 18:12:59 2017 Loic Lopez
*/

#include "my_nm.h"

bool	check32_integrity(Elf32_Ehdr *elf)
{
  if (elf->e_ident[EI_MAG0] != ELFMAG0 || elf->e_ident[EI_MAG1] != ELFMAG1 ||
    elf->e_ident[EI_MAG2] != ELFMAG2 || elf->e_ident[EI_MAG3] != ELFMAG3 ||
    elf->e_type == ET_NONE)
    return (false);
  else
    return (true);
}

char	check_symbols(Elf32_Sym sym, Elf32_Shdr *shdr)
{
  char c;
  bool	weak;

  if (ELF32_ST_BIND(sym.st_info) == STB_WEAK)
    weak = true;
  int unresolved = (sym.st_shndx == SHN_UNDEF);
  shdr = shdr;
  if (unresolved)
     weak ? (c = 'w') : (c = 'U');
  return (c);
}


void	nm32_format(Elf32_Ehdr *elf, char **av, void *data)
{
  Elf32_Sym	*symtab;
  Elf32_Shdr *shdr;
  char	*strtab;
  // char	*shstrtab;
  int	i;

  if (!check32_integrity(elf))
    return ((void)fprintf(stderr, "%s: Wrong header in: %s", av[0], av[1]));
  else if (elf->e_shstrndx == SHN_UNDEF)
    return ((void)fprintf(stderr, "%s: Undefined reference to header section tables: %s", av[0], av[1]));
  shdr = (Elf32_Shdr *)(data + elf->e_shoff);
  i = -1;
  while (++i < elf->e_shnum)
    if (shdr[i].sh_type == SHT_SYMTAB)
    {
      symtab = (Elf32_Sym *)(data + shdr[i].sh_offset);
      break;
    }
  symtab = symtab;
  strtab = (char *)(data + shdr[elf->e_shstrndx].sh_offset);
  i = -1;
  while (++i < elf->e_shnum)
  {
    printf("%s\n", &strtab[shdr[i].sh_name]);
  }
}
