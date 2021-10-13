# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvacaris <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/12 21:45:02 by jvacaris          #+#    #+#              #
#    Updated: 2021/10/12 21:45:03 by jvacaris         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS	=	./mandatory/err_mngmnt.c \
			./mandatory/pipex.c \
			./mandatory/doublefree.c \
			./mandatory/dothings.c \

OBJS = ${SRCS:.c=.o}

PATH_INCLUDES = ./includes/
PATH_LIBFT = ./libft/
PATH_MANDATORY = ./mandatory/

NAME = pipex
LIBFT = libft.a
CC = gcc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra

all:		${NAME}
${NAME}:	${LIBFT} ${OBJS} 
			${CC} ${CFLAGS} ${PATH_LIBFT}${LIBFT} ${OBJS} -I ${PATH_INCLUDES} -o ${NAME}
${LIBFT}:	
			@make -C ${PATH_LIBFT}

clean:
	@${RM} ${OBJS} ${OBJS_BONUS}
	@make clean -C ${PATH_LIBFT}
	@echo ".o's are no more!"
fclean:		clean
	@${RM} ${NAME} libft/${LIBFT}
	@echo "(including .a's and pipex)"
re:		fclean all
.PHONY: all clean fclean re
