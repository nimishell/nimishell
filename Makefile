# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/12 16:06:02 by yeongo            #+#    #+#              #
#    Updated: 2023/05/08 12:04:57 by wbae             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				:=	minishell
PROJECT_NAME		:=	MINISHELL

HEADER				:=	./inc/

SRC_PARSE_DIR		:=	./srcs/
SRC_BUILTIN_DIR		:=	./srcs/builtin/
SRC_EXECUTE_DIR		:=	./srcs/execute/

OBJ_DIR				:=	./.obj/
OBJ_PARSE_DIR		:=	./.obj/parse/
OBJ_BUILTIN_DIR		:=	./.obj/builtin/
OBJ_EXECUTE_DIR		:=	./.obj/execute/
CACHE_DIR			:=	./.cache/

LIBFT_DIR			:=	./libft/
LIBFT_HEADER		:=	./libft/inc/
LIBFT				:=	$(LIBFT_DIR)libft.a

BREW_PREFIX			:=	${HOME}/.brew/opt/readline/
LIBRDLINE_DIR		:=	$(BREW_PREFIX)lib
LIBRDLINE_HEADER	:=	$(BREW_PREFIX)include
LIBRDLINE			:=	$(LIBRDLINE_DIR)libreadline.a

LDFLAGS				:=	-L$(LIBFT_DIR) -lft -L$(LIBRDLINE_DIR) -lreadline

CC					:=	cc
CFLAGS				:=	-Wall -Wextra -Werror
CPPFLAGS			:=	-I$(HEADER) -I$(LIBFT_HEADER) -I$(LIBRDLINE_HEADER)
MJFLAGS				 =	-MJ $@.part.json
RM					:=	rm -rf

SRC_PARSE_FILES		:=	$(addsuffix .c,				\
							signal					\
							error					\
							envp					\
							parse					\
							cmd						\
							split_token				\
							split_token2			\
							after_split_chunk		\
							translate_dollar		\
							treat_redir				\
							tokenize_utils			\
							util					\
							debug					\
							main					\
						)
SRC_BUILTIN_FILES	:=	$(addsuffix .c,				\
							ft_cd					\
							ft_echo					\
							ft_env					\
							ft_exit					\
							ft_export				\
							ft_pwd					\
							ft_unset				\
						)
SRC_EXECUTE_FILES	:=	$(addsuffix .c,				\
							execute_builtin			\
							execute_command			\
							execute_multi			\
							execute_single			\
							heredoc					\
							open_file				\
							terminate				\
						)
OBJ_PARSE_FILES		:=	$(SRC_PARSE_FILES:.c=.o)
OBJ_BUILTIN_FILES	:=	$(SRC_BUILTIN_FILES:.c=.o)
OBJ_EXECUTE_FILES	:=	$(SRC_EXECUTE_FILES:.c=.o)
JSON_FILES			:=	compile_commands

SRC_PARSE			:=	$(addprefix $(SRC_PARSE_DIR), $(SRC_PARSE_FILES))
SRC_BUILTIN			:=	$(addprefix $(SRC_BUILTIN_DIR), $(SRC_BUILTIN_FILES))
SRC_EXECUTE			:=	$(addprefix $(SRC_EXECUTE_DIR), $(SRC_EXECUTE_FILES))

OBJ_PARSE			:=	$(addprefix $(OBJ_PARSE_DIR),	$(OBJ_PARSE_FILES))
OBJ_BUILTIN			:=	$(addprefix $(OBJ_BUILTIN_DIR),	$(OBJ_BUILTIN_FILES))
OBJ_EXECUTE			:=	$(addprefix $(OBJ_EXECUTE_DIR),	$(OBJ_EXECUTE_FILES))
JSON				:=	$(addsuffix .json,				$(JSON_FILES))

# SRC_FOLDER			:=	$(SRC_DIR)
OBJ_FOLDER			:=	$(OBJ_DIR) \
						$(OBJ_PARSE_DIR) \
						$(OBJ_BUILTIN_DIR) \
						$(OBJ_EXECUTE_DIR)
OBJS				:=	$(OBJ_PARSE) \
						$(OBJ_BUILTIN) \
						$(OBJ_EXECUTE)
PRINT				:=	$(PROJECT_NAME)

ifdef		TEST
		SRC			+=	$(addprefix $(SRC_DIR), $(addsuffix .c, debug))
		OBJ			+=	$(addprefix $(OBJ_DIR), $(addsuffix .o, debug))
		PRINT		:=	$(addsuffix _TEST, $(PRINT))
else ifdef	DEBUG
		DBFLAGS		:=	-g -fsanitize=address
		PRINT		:=	$(addsuffix _DEBUG, $(PRINT))
endif

.PHONY	:	all
all		:	$(OBJ_FOLDER) $(NAME)

$(OBJ_DIR)	:
	@if [ ! -d $(OBJ_DIR) ]; then \
		mkdir -p $(OBJ_DIR); \
	fi

$(OBJ_PARSE_DIR)	:
	@if [ ! -d $(OBJ_PARSE_DIR) ]; then \
		mkdir -p $(OBJ_PARSE_DIR); \
	fi

$(OBJ_BUILTIN_DIR)	:
	@if [ ! -d $(OBJ_BUILTIN_DIR) ]; then \
		mkdir -p $(OBJ_BUILTIN_DIR); \
	fi

$(OBJ_EXECUTE_DIR)	:
	@if [ ! -d $(OBJ_EXECUTE_DIR) ]; then \
		mkdir -p $(OBJ_EXECUTE_DIR); \
	fi

$(NAME)	:	$(OBJS)
	@make -s -C $(LIBFT_DIR) all
	@$(CC) $(CFLAGS) $(LDFLAGS) $(DBFLAGS) -o $@ $^
	@(printf [ && find . -name "*.part.json" | xargs cat && printf ]) > $(JSON);
	@echo "\033[01;32m         SUCCESS!        \033[0m"

$(OBJ_PARSE_DIR)%.o		:	$(SRC_PARSE_DIR)%.c
	@$(CC) $(CFLAGS) $(DBFLAGS) $(CPPFLAGS) $(MJFLAGS) -c -o $@ $<

$(OBJ_BUILTIN_DIR)%.o	:	$(SRC_BUILTIN_DIR)%.c
	@$(CC) $(CFLAGS) $(DBFLAGS) $(CPPFLAGS) $(MJFLAGS) -c -o $@ $<

$(OBJ_EXECUTE_DIR)%.o	:	$(SRC_EXECUTE_DIR)%.c
	@$(CC) $(CFLAGS) $(DBFLAGS) $(CPPFLAGS) $(MJFLAGS) -c -o $@ $<

.PHONY	:	test
test	:
	@make TEST=1 all

.PHONY	:	debug
debug	:
	@make DEBUG=1 all

.PHONY	:	clean
clean	:
	@make -s -C libft clean
	@$(RM) $(OBJ_DIR) $(CACHE_DIR)
	@echo "\033[91m      REMOVE OBJECT      \033[0m"

.PHONY	:	fclean
fclean	:	clean
	@$(RM) $(NAME)
	@echo "\033[91m       FCLEAN DONE       \033[0m"

.PHONY	:	re
re		:	fclean
	@make all
