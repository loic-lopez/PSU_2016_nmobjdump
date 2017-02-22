##
## Makefile for Makefile in /Users/loiclopez/Documents/Shared/Epitech/year_2016/psu/PSU_2016_nmobjdump/
##
## Made by Loic Lopez
## Login   <loic.lopez@epitech.eu>
##
## Started on  Tue Feb 14 14:21:35 2017 Loic Lopez
## Last update Wed Feb 22 18:56:35 2017 Loic Lopez
##

CC	=	gcc

OBJDUMP	=	my_objdump

NM	=	my_nm

ECHO	=	/bin/echo -e

DEFAULT	=	"\033[00m"
GREEN	=	"\033[0;32m"
TEAL	=	"\033[1;36m"
RED	=	"\033[5;31m"

CFLAGS	=	-Wextra -Wall -Werror
CFLAGS	+= 	-I./include

SRC_OBJDUMP	=	sources/objdump/main_objdump.c \
			sources/general/filesize.c \
			sources/general/my_open.c \
			sources/general/print_error_and_exit.c

SRC_NM	=	sources/nm/main_nm.c \
		sources/general/my_open.c\
		sources/general/filesize.c \
		sources/general/print_error_and_exit.c \
		sources/nm/nm32_format.c \
		sources/nm/nm64_format.c \
		sources/nm/initSymbolsArray.c \
		sources/nm/show32.c \
		sources/nm/get_symbols32.c \
		sources/nm/show64.c \
		sources/nm/get_symbols64.c



OBJ_OBJDUMP	=	$(SRC_OBJDUMP:.c=.o)
OBJ_NM	=	$(SRC_NM:.c=.o)

all:		$(OBJDUMP) $(NM)

$(OBJDUMP):	$(OBJ_OBJDUMP)
		@$(CC) $(OBJ_OBJDUMP) $(CFLAGS) -o $(OBJDUMP) && \
		$(ECHO) $(GREEN) "[OK]"$(TEAL)"  BUILD :" $(OBJDUMP) $(DEFAULT)  || \
		$(ECHO) $(RED) "[ERROR]" $(TEAL) $(OBJDUMP) $(DEFAULT)


$(NM):		$(OBJ_NM)
		@$(CC) $(OBJ_NM) $(CFLAGS) -o $(NM) && \
		$(ECHO) $(GREEN) "[OK]"$(TEAL)"  BUILD :" $(NM) $(DEFAULT)  || \
		$(ECHO) $(RED) "[ERROR]" $(TEAL) $(NM) $(DEFAULT)

clean:
		@rm -f $(OBJ_OBJDUMP) $(OBJ_NM) && \
		$(ECHO) $(GREEN) "[OK] remove" $(TEAL) $(OBJ_OBJDUMP) $(OBJ_NM) $(DEFAULT) || \
		$(ECHO) $(RED) "[ERROR] doesn't exist" $(TEAL) $(OBJ) $(DEFAULT)

fclean:		clean
		@rm -f $(OBJDUMP) $(NM) && \
		$(ECHO) $(GREEN) "[OK] remove" $(TEAL) $(OBJDUMP) $(NM) $(DEFAULT) || \
		$(ECHO) $(RED) "[ERROR] doesn't exist" $(TEAL) $(OBJ) $(DEFAULT)

re:		fclean all

.c.o:
		 @$(CC) $(CFLAGS) -c -o $@ $< && \
		 $(ECHO) $(GREEN) "[OK]" $(TEAL) $< "--->" $@ $(DEFAULT) || \
		 $(ECHO) $(RED) "[ERROR] doesn't exist" $(TEAL) $^ $(DEFAULT)

.PHONY:   all clean fclean re
