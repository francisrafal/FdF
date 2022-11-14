# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frafal <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/07 10:02:44 by frafal            #+#    #+#              #
#    Updated: 2022/11/14 15:38:53 by frafal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= fdf
CC			:= cc
RM	    	:= rm -f
FLAGS		:= -Wall -Wextra -Werror
DEBUG		:=

HEADDIR		:= ./includes/
HEADLIST	:= fdf.h
HEADERS		:= $(addprefix ${HEADDIR}, ${HEADLIST})

SRCSDIR		:= ./src/
SRCSLIST	:= main.c
SRCS		:= $(addprefix ${SRCSDIR}, ${SRCSLIST})

OBJSDIR		:= ./obj/
OBJSLIST	:= ${SRCSLIST:.c=.o}
OBJS		:= $(addprefix ${OBJSDIR}, ${OBJSLIST})

LIBFTDIR	:= ./libft/
LIBFT		:= ${LIBFTDIR}libft.a

MLXDIR		:= ./minilibx-linux/
MLX			:= ${MLXDIR}libmlx_Linux.a

LIBS		:= -L${LIBFTDIR} -L${MLXDIR} -lft -lmlx_Linux -static
INCS		:= -I${HEADDIR} -I${LIBFTDIR} -I${MLXDIR}

${NAME}:	${OBJSDIR} ${OBJS} ${LIBFT} ${MLX}
			@ echo "Compilation of $(NAME) ..."
			${CC} ${FLAGS} ${DEBUG} ${OBJS} -o ${NAME} ${LIBS} ${INCS}
			@ echo "$(NAME) created"

${LIBFT}:
			make -C ${LIBFTDIR}

${MLX}:
			git submodule init
			git submodule update
			make -C ${MLXDIR}

${OBJSDIR}%.o:	${SRCSDIR}%.c ${HEADERS}
			@ ${CC} ${FLAGS} ${DEBUG} ${INCS} -c $< -o $@

${OBJSDIR}:
			mkdir -p ${OBJSDIR}

.PHONY:		all clean fclean re test

all:		${NAME}

clean:
			${RM} -r ${OBJSDIR}
			make -C ${LIBFTDIR} clean
			make -C ${MLXDIR} clean
			@ echo "Deleting $(NAME) objects"

fclean:		clean
			${RM} ${NAME}
			make -C ${LIBFTDIR} fclean
			@ echo "Deleting $(NAME) executable"

re:			fclean all

test:		all
			./fdf
