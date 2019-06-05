##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

NAME	=	libmy.a

SRC		:=	$(shell find . -name "*.c")

OBJ		=	$(SRC:.c=.o)

all: $(NAME) clean2

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	cp $(NAME) ../
	cp *.h ../../include/

%.o: %.c
	gcc -g3 -W -Wall -Wextra -o $@ -c $<

clean1 clean2:
	$(shell find . -name "*.o" -delete)
	$(shell find . -name "*~" -delete)
	$(shell find . -name "\#*\#" -delete)
	$(shell find . -name "vgcore.*" -delete)

fclean: clean1
	rm -f $(NAME)

re: fclean all

.PHONY: all clean1 clean2 fclean re
