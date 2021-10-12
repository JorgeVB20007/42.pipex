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
#OBJS_BONUS = ${SRCS_BONUS:.c=.o}

PATH_INCLUDES = ./includes/
PATH_LIBFT = ./libft/
PATH_MANDATORY = ./mandatory/
#PATH_BONUS = ./bonus/

NAME = pipex
#NAME_BONUS = fdf_bonus
LIBFT = libft.a
CC = gcc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address

all:		${NAME}
${NAME}:	${LIBFT} ${OBJS} 
#			${CC} ${CFLAGS} libft/${LIBFT} ${OBJS} -I ${PATH_LIBFT} -I ${PATH_INCLUDES} -o ${NAME}
			${CC} ${CFLAGS} ${PATH_LIBFT}${LIBFT} ${OBJS} -I ${PATH_INCLUDES} -o ${NAME}
${LIBFT}:	
			@make -C ${PATH_LIBFT}

#bonus:			${NAME_BONUS}
#${NAME_BONUS}:	${OBJS_BONUS} ${LIBFT} ${MLX}
#				${CC} ${CFLAGS} libftjvb/${LIBFT} ${OBJS_BONUS} -I ${PATH_LIBFT} -I ${PATH_INCLUDES} -I ${PATH_MLX} ${SUFFIX} -o ${NAME_BONUS}

clean:
	@${RM} ${OBJS} ${OBJS_BONUS}
	@make clean -C ${PATH_LIBFT}
	@echo ".o's are no more!"
fclean:		clean
	@${RM} ${NAME} libft/${LIBFT}
	@echo "(including .a's and pipex)"
re:		fclean all
#rebonus:		fclean bonus
.PHONY: all clean fclean re
