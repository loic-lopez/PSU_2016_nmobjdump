/*
** print64.c for nmobjdump in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/sources/objdump/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Sat Feb 25 14:33:48 2017 Loic Lopez
** Last update Sat Feb 25 14:43:39 2017 Loic Lopez
*/

#include "my_objdump.h"

void	check_printable_char(char c)
{
  if (isprint(c))
    printf("%c", c);
  else
    printf(".");
}

int	print_char64(size_t i, Elf64_Shdr	*shdr, void *data)
{
  size_t	j;

  j = 0;
  printf("  ");
  if (i == 0 || i % 16 == 0)
    {
      check_printable_char((unsigned char)((char *)(data
        + shdr->sh_offset + i))[0]);
      i++;
      j++;
    }
  while ((i % 16) != 0 && i < shdr->sh_size && i != 0)
    {
      check_printable_char((unsigned char)((char *)(data
        + shdr->sh_offset + i))[0]);
      i++;
      j++;
    }
  if (j < 16)
  	 while (++j <= 16)
  	   printf(" ");
  printf("\n");
  return (i);
}

void	print_section64(size_t i, Elf64_Shdr	*shdr, void *data)
{
  size_t x;

  printf(" ");
  x = 1;
  if (i == 0 || i % 16 == 0)
    {
      printf("%02x", (unsigned char)((char *)(data + shdr->sh_offset + i))[0]);
      x += 2;
      i++;
    }
  while ((i % 16) != 0 && i < shdr->sh_size && i != 0)
    {
      if (i % 4 == 0)
      	{
      	  printf(" ");
      	  x++;
      	}
      printf("%02x", (unsigned char)((char *)(data + shdr->sh_offset + i))[0]);
      x += 2;
      i++;
    }
  while (++x <= 36)
  	printf(" ");
}

void print_hearth64(Elf64_Shdr	*shdr, char *strtab, size_t size, void *data)
{
  size_t j;

  j = 0;
  if (shdr->sh_size == 0)
   return;
  size = size ;
  printf("Contents of section %s:\n", &strtab[shdr->sh_name]);
  while (j < shdr->sh_size)
  {
    printf(" %04lx", shdr->sh_addr + j);
    print_section64(j, shdr, data);
    j = print_char64(j, shdr, data);
  }
}

void	print_objdump64(Elf64_Ehdr *elf, Elf64_Shdr	*shdr, char *strtab)
{
  size_t	size;
  void *data;
  size_t offset;
  Elf64_Shdr *current;

  size = 0;
  data = (void *)elf;
  while (size < elf->e_shnum)
  {
    offset = elf->e_shoff + size * sizeof(Elf64_Shdr);
    current = (Elf64_Shdr *)(data + offset);
    if (strcmp(&strtab[shdr[size].sh_name], "") > 0)
    {
      if(must_i_print_it64(current, &strtab[shdr[size].sh_name]))
        print_hearth64(current, strtab, size, data);
    }
    size++;
  }
}
