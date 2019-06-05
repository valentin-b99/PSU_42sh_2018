##
## EPITECH PROJECT, 2018
## makefile
## File description:
## makefile
##

NAME	=	42sh

SRC		=	$(wildcard ./src/parsing/*.c) \
			$(wildcard ./src/*.c) \
			$(wildcard ./src/shell/*.c) \
			$(wildcard ./src/shell/alias/*.c) \
			$(wildcard ./src/shell/if/*.c) \
			$(wildcard ./src/shell/builtins/*.c) \
			$(wildcard ./src/shell/dup/*.c) \
			$(wildcard ./src/shell/variables/*.c) \
			$(wildcard ./src/shell/inhibitors/*.c) \
			$(wildcard ./src/shell/linked_list/*.c) \
			$(wildcard ./src/shell/globbing/*.c) \
			$(wildcard ./src/shell/mysh/*.c) \
			$(wildcard ./src/shell/which_where/*.c) \
			$(wildcard ./src/shell/foreach/*.c) \
			$(wildcard ./src/shell/scripting/*.c)

CFLAGS	=	-g3 -W -Wall -Wextra

all: $(NAME) clean1

$(NAME): $(SRC)
	make -C ./lib/my
	cp ./src/.lib42sh.txt ./src/lib42sh.a
	gcc $(CFLAGS) -g3 -o $(NAME) $(SRC) -L./lib/my -L./src/ -L. -lmy -l42sh -lmy
	rm ./src/lib42sh.a

clean1 clean2:
	rm -f *.o
	rm -f *~
	rm -f \#*\#
	rm -f vgcore.*

fclean: clean2
	rm -f $(NAME)

re: fclean all

.PHONY: all clean1 clean2 fclean re
