# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frafal <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/07 10:02:44 by frafal            #+#    #+#              #
#    Updated: 2022/11/21 14:49:25 by frafal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= fdf
CC			:= cc
RM	    	:= rm -f
FLAGS		:= -Wall -Wextra -Werror
DEBUG		:= -g

HEADDIR		:= ./includes/
HEADLIST	:= fdf.h
HEADERS		:= $(addprefix ${HEADDIR}, ${HEADLIST})

SRCSDIR		:= ./src/
SRCSLIST	:= main.c \
				hooks.c \
				file_handling.c \
				color_handling.c \
				lines.c \
				math_helpers.c \
				transform.c
SRCS		:= $(addprefix ${SRCSDIR}, ${SRCSLIST})

OBJSDIR		:= ./obj/
OBJSLIST	:= ${SRCSLIST:.c=.o}
OBJS		:= $(addprefix ${OBJSDIR}, ${OBJSLIST})

LIBFTDIR	:= ./libft/
LIBFT		:= ${LIBFTDIR}libft.a

MLXDIR		:= ./minilibx-linux/
MLX			:= ${MLXDIR}libmlx.a

LIBS		:= -L${LIBFTDIR} -L${MLXDIR} -lft -lmlx -lXext -lX11 -lm
INCS		:= -I${HEADDIR} -I${LIBFTDIR} -I${MLXDIR}

CYAN		:= \033[0;36m
RESET		:= \033[0m

${NAME}:	${MLX} ${LIBFT} ${OBJSDIR} ${OBJS}
			@echo ""
			@echo "${CYAN}Compiling ${NAME} ...${RESET}"
			${CC} ${FLAGS} ${DEBUG} ${OBJS} -o ${NAME} ${LIBS} ${INCS}
			@echo ""
			@echo "${CYAN}$(NAME) Created${RESET}"

${LIBFT}:
			make -C ${LIBFTDIR}

${MLX}:
			@echo ""
			@echo "${CYAN}Compiling ${MLX} ...${RESET}"
			git submodule init
			git submodule update
			make -C ${MLXDIR}

${OBJSDIR}%.o:	${SRCSDIR}%.c ${HEADERS} compiling
			${CC} ${FLAGS} ${DEBUG} ${INCS} -c $< -o $@

${OBJSDIR}:
			mkdir -p ${OBJSDIR}

.PHONY:		all clean fclean re test 

.INTERMEDIATE:	compiling

compiling:
			@echo ""
			@echo "${CYAN}Compiling Objects ...${RESET}"

all:		${NAME}

clean:
			@echo ""
			@echo "${CYAN}Deleting $(NAME) Objects ...${RESET}"
			${RM} -r ${OBJSDIR}
			make -C ${LIBFTDIR} clean
			make -C ${MLXDIR} clean

fclean:		clean
			@echo ""
			@echo "${CYAN}Deleting $(NAME) Executable ...${RESET}"
			${RM} ${NAME}
			make -C ${LIBFTDIR} fclean

re:			fclean all

test:		all
			./fdf test_maps/42.fdf
