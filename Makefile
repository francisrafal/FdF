# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frafal <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/07 10:02:44 by frafal            #+#    #+#              #
#    Updated: 2022/11/14 16:16:43 by frafal           ###   ########.fr        #
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

CYAN		:= \033[0;36m
RESET		:= \033[0m

${NAME}:	${MLX} ${LIBFT} ${OBJSDIR} ${OBJS}
			@echo ""
			@echo "${CYAN}Compilation Of ${NAME} ...${RESET}"
			${CC} ${FLAGS} ${DEBUG} ${OBJS} -o ${NAME} ${LIBS} ${INCS}
			@echo ""
			@echo "${CYAN}$(NAME) Created${RESET}"

${LIBFT}:
			make -C ${LIBFTDIR}

${MLX}:
			@echo ""
			@echo "${CYAN}Compilation of ${MLX} ...${RESET}"
			git submodule init
			git submodule update
			make -C ${MLXDIR}

${OBJSDIR}%.o:	${SRCSDIR}%.c compiling
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
			@echo "${CYAN}Deleting $(NAME) objects ...${RESET}"
			${RM} -r ${OBJSDIR}
			make -C ${LIBFTDIR} clean
			make -C ${MLXDIR} clean

fclean:		clean
			@echo ""
			@echo "${CYAN}Deleting $(NAME) executable ...${RESET}"
			${RM} ${NAME}
			make -C ${LIBFTDIR} fclean

re:			fclean all

test:		all
			./fdf
