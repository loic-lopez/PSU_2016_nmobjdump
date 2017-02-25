/*
** get_symbols64.c for nmobjdump in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/sources/nm/
**
** Made by Loic Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  Wed Feb 22 18:34:03 2017 Loic Lopez
** Last update Fri Feb 24 21:18:50 2017 Loic Lopez
*/

#include "my_nm.h"

char	get_symbol64(Elf64_Sym *symbol)
{
  char c;

  c = '?';
  if (ELF64_ST_BIND(symbol->st_info) == STB_GNU_UNIQUE)
    c = 'u';
  else if (ELF64_ST_BIND(symbol->st_info) == STB_WEAK)
    {
      c = 'W';
      symbol->st_shndx == SHN_UNDEF ? c = 'w' : c;
    }
  else if (ELF64_ST_BIND(symbol->st_info) == STB_WEAK &&
	   ELF64_ST_TYPE(symbol->st_info) == STT_OBJECT)
    {
      c = 'V';
      symbol->st_shndx == SHN_UNDEF ? c = 'v' : c;
    }
  else if (symbol->st_shndx == SHN_UNDEF)
    c = 'U';
  else if (symbol->st_shndx == SHN_ABS)
    c = 'A';
  else if (symbol->st_shndx == SHN_COMMON)
    c = 'C';
  return (c);
}

char	get_shdr_symbols64(Elf64_Shdr *shdr, Elf64_Sym *symbol)
{
  char c;

  c = '?';
  shdr[symbol->st_shndx].sh_type == SHT_NOBITS
    && shdr[symbol->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE) ?
    c = 'B' :
    (shdr[symbol->st_shndx].sh_type == SHT_PROGBITS
     && shdr[symbol->st_shndx].sh_flags == SHF_ALLOC)
    || (shdr[symbol->st_shndx].sh_flags == 18) ?
    c = 'R' :
    shdr[symbol->st_shndx].sh_type == SHT_PROGBITS
    && shdr[symbol->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE) ?
    c = 'D' :
    shdr[symbol->st_shndx].sh_type == SHT_PROGBITS
    && shdr[symbol->st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR) ?
    c = 'T' :
    shdr[symbol->st_shndx].sh_type == SHT_DYNAMIC ? c = 'D' : c;
  return (c);
}
