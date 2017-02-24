/*
** main.c for nmobjdump in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/sources/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Tue Feb 14 14:21:50 2017 Loic Lopez
** Last update Fri Feb 24 20:40:40 2017 Loic Lopez
*/

#include "my_objdump.h"

void	objdump32_format(Elf32_Ehdr	*elf, char **av, size_t size, void *data)
{
  (void)size;
  (void)elf;
  (void)av;
  (void)data;
}

void	print_sh_name64(Elf64_Ehdr *elf, Elf64_Shdr	*shdr, char *strtab)
{
  size_t	size;

  size = 0;
  while (size < elf->e_shnum)
  {
    if (strcmp(&strtab[shdr[size].sh_name], "") > 0)
    {
      printf("Contents of section %s:\n", &strtab[shdr[size].sh_name]);
      if (!strcmp(&strtab[shdr[size].sh_name], ".debug_ranges"))
        break;
    }
    size++;
  }
}

char	*getElf64(Elf64_Ehdr	*elf)
{
  if (elf->e_machine == EM_NONE)
    return "NONE";
  else if (elf->e_machine == EM_860 || elf->e_machine == EM_X86_64)
    return "x86-64";
  return ("NONE");
}

char	*getArch64(Elf64_Ehdr	*elf)
{
  if (elf->e_machine == EM_NONE)
    return "NONE";
  else if (elf->e_machine == EM_860)
    return "i860:x86-64";
  else if (elf->e_machine == EM_X86_64)
    return "i386:x86-64";
  return ("NONE");
}


void	objdump64_format(Elf64_Ehdr	*elf, char **av, size_t size, void *data)
{
  Elf64_Shdr	*shdr;
  (void)size;
  (void)av;
  char	*strtab;

  shdr = (Elf64_Shdr *)(data + elf->e_shoff);
  strtab = (char *)(data + shdr[elf->e_shstrndx].sh_offset);
  printf("%s:     file format elf64-%s\n", av[0], getElf64(elf));
  printf("architecture: %s, flags\n", getArch64(elf));
  printf("start address\n\n");
  print_sh_name64(elf, shdr, strtab);
}

void	my_objdump(char *file, char **av)
{
  void	*data;
  Elf32_Ehdr	*elf;
  int	fd;

  if ((fd = my_open(file, av)) == -1)
    return;
  if ((data = mmap(NULL, filesize(fd), PROT_READ,
       MAP_SHARED, fd, 0)) == MAP_FAILED)
    return (print_error_and_exit("mmap", av[0]));
  elf = (Elf32_Ehdr *)data;
  if (elf->e_ident[EI_CLASS] == ELFCLASS32)
    objdump32_format(elf, av, filesize(fd), data);
  else if (elf->e_ident[EI_CLASS] == ELFCLASS64)
    objdump64_format((Elf64_Ehdr *)data, av, filesize(fd), data);
  else
    fprintf(stderr, "%s: %s: File format not recognized\n", av[0], file);
  if (munmap(data, filesize(fd)) == -1)
    return (print_error_and_exit("munmap", av[0]));
  if (close(fd) == -1)
    return (print_error_and_exit("close", av[0]));
}

int	main(int ac, char **av)
{
  int	i;

  i = 0;
  if (ac == 1)
    my_objdump("a.out", av);
  else
    while (++i < ac)
      my_objdump(av[i], av);

  return (0);
}
