/*
** EPITECH PROJECT, 2018
** get_next_line
** File description:
** get_next_line
*/

#ifndef GET_NEXT_LINE_H_
# define GET_NEXT_LINE_H_

# ifndef READ_SIZE
#  define READ_SIZE (1)
# endif /* !READ_SIZE */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int gnl_reread(int *is, int fd, char *buff, char **str);

#endif /* !GET_NEXT_LINE_H_ */
