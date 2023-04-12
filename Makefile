# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 20:55:17 by wbae              #+#    #+#              #
#    Updated: 2023/04/11 20:56:36 by wbae             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -I${HOME}/.brew/opt/readline/include #-fsanitize=address -g3

RDLINE_LIB = -lreadline -L${HOME}/.brew/opt/readline/lib
RELINE_INC = -I${HOME}/.brew/opt/readline/include
LIBFT_LIB = ./libft/libft.a
SRCS = $(addprefix srcs/, main.c \
	signal.c \
	error.c \
	envp.c \
	parse.c \
	tokenize_quote.c \
	tokenize_space.c \
	tokenize_pipe.c \
	tokenize_utils.c \
	util.c \
	debug.c)

OBJS = $(SRCS:.c=.o)
INC = -I./inc

all : $(NAME)

$(NAME) : $(OBJS)
	@make -C ./libft all
	@$(CC) $(CFLAGS) $(INC) $(LIBFT_LIB) $(OBJS) $(RDLINE_LIB) -o $(NAME)
	@echo "Linked into executable \033[0;32mminishell\033[0m."

%.o : %.c
	@$(CC) $(CFLAGS) $(RDLINE_INC) $(INC) -c $< -o $@
	@echo "Compiling [$<]"

$(LIBFT_LIB) :
	@make -C ./libft bonus

clean :
	@echo "Excute clean"
	@make -C ./libft fclean
	@rm -rf $(OBJS)

fclean : clean
	@echo "Excute fclean"
	@rm -rf $(NAME)

re :
	@make fclean
	@make all
