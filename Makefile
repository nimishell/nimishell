# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/12 16:06:02 by yeongo            #+#    #+#              #
#    Updated: 2023/04/12 20:29:59 by wbae             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				:=	minishell
PROJECT_NAME		:=	MINISHELL

HEADER				:=	./inc/
SRC_DIR				:=	./srcs/
OBJ_DIR				:=	./.obj/
CACHE_DIR			:=	./.cache/

LIBFT_DIR			:=	./libft/
LIBFT_HEADER		:=	./libft/
LIBFT				:=	$(LIBFT_DIR)libft.a
LIBRDLINE_DIR		:=	${HOME}/.brew/opt/readline/lib/
LIBRDLINE_HEADER	:=	${HOME}/.brew/opt/readline/include/
LIBRDLINE			:=	$(LIBRDLINE_DIR)libreadline.a
LDFLAGS				:=	-L$(LIBFT_DIR) -lft -L$(LIBRDLINE_DIR) -lreadline

CC					:=	cc
CFLAGS				:=	-Wall -Wextra -Werror
CPPFLAGS			:=	-I$(HEADER) -I$(LIBFT_HEADER) -I$(LIBRDLINE_HEADER)
MJFLAGS				 =	-MJ $@.part.json
RM					:=	rm -rf

SRC_FILES			:=	$(addsuffix .c,			\
							signal				\
							error				\
							envp 				\
							parse 				\
							tokenize_quote		\
							tokenize_space		\
							tokenize_pipe		\
							tokenize_utils		\
							tokenize_redirection\
							util				\
	 						debug				\
	 						main				\
						)
OBJ_FILES			:=	$(SRC_FILES:.c=.o)
JSON_FILES			:=	compile_commands.json
SRC					:=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ					:=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))

SRC_FOLDER			:=	$(SRC_DIR)
OBJ_FOLDER			:=	$(OBJ_DIR)
OBJS				:=	$(OBJ)
PRINT				:=	$(PROJECT_NAME)

ifdef TEST
		SRC				+=	$(addprefix $(SRC_DIR), $(addsuffix .c, debug))
		OBJ				+=	$(addprefix $(OBJ_DIR), $(addsuffix .o, debug))
		PRINT			:=	$(addsuffix _TEST, $(PRINT))
else ifdef DEBUG
		DBFLAGS			:=	-g -fsanitize=address
		PRINT			:=	$(addsuffix _DEBUG, $(PRINT))
endif

.PHONY	:	all
all		:	$(OBJ_FOLDER) $(NAME)

$(OBJ_FOLDER)	:
	@if [ ! -d $(OBJ_FOLDER) ]; then \
		mkdir -p $(OBJ_FOLDER); \
	fi

$(NAME)	:	$(OBJS)
	@make -s -C $(LIBFT_DIR) all
	@$(CC) $(CFLAGS) $(LDFLAGS) $(DBFLAGS) -o $@ $^
	@(printf [ && find . -name "*.part.json" | xargs cat && printf ]) > $(JSON_FILES);
	@echo "\033[01;32m         SUCCESS!        \033[0m"

$(OBJ_FOLDER)%.o	:	$(SRC_FOLDER)%.c
	@$(CC) $(CFLAGS) $(DBFLAGS) $(CPPFLAGS) $(MJFLAGS) -c -o $@ $<

.PHONY	:	test
test	:
	@make TEST=1 all

.PHONY	:	debug
debug	:
	@make DEBUG=1 all

.PHONY	:	clean
clean	:
	@$(RM) $(OBJ_DIR) $(CACHE_DIR)
	@echo "\033[91m      REMOVE OBJECT      \033[0m"

.PHONY	:	fclean
fclean	:	clean
	@$(RM) $(NAME)
	@echo "\033[91m       FCLEAN DONE       \033[0m"

.PHONY	:	re
re		:	fclean
	@make all
