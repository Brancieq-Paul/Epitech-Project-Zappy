##
## EPITECH PROJECT, 2019
## Pushswap
## File description:
## Libmy Makefile
##

CC 		= 	gcc

SRC		=	my_str_isnum_pos.c \
			my_remove_whitespace.c 	\
			my_str_toupper.c \
			my_strdupcat.c \
			get_file_lines.c \
			get_file_size.c \
			get_filenames.c \
			get_nb_files_in_dir.c \
			my_count_char.c \
			my_count_until_sep.c\
			my_str_to_word_array.c \
			my_strdupcat.c \
			remove_before_sep.c \
			my_sdup.c\
			my_strarr_to_str.c\
			my_int_to_str.c \
			my_revstr.c \
			my_intlen.c\
			rand_between_two_value.c \
			my_replace_char.c 	\

OBJ		=	$(SRC:.c=.o)

CFLAGS	=	-W -Wall -Wextra -Werror

DBFLAGS	=	-g -g3 -ggdb

HEADER	=	my.h

NAME	=	libmy.a

all:		$(OBJ)
			ar rc $(NAME) $(OBJ)
			cp $(NAME) ../
			cp $(HEADER) ../../inc

clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)
			rm -f ../$(NAME)
			rm -f ../../inc/$(HEADER)

re:			fclean all

.phony:		re fclean clean
