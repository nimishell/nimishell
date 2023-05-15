# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/12 16:06:02 by yeongo            #+#    #+#              #
#    Updated: 2023/05/15 21:38:34 by wbae             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				:=	minishell
PROJECT_NAME		:=	MINISHELL

HEADER				:=	./inc/

SRC_MAIN_DIR		:=	./srcs/main/
SRC_PARSE_DIR		:=	./srcs/parse/
SRC_BUILTIN_DIR		:=	./srcs/builtin/
SRC_EXECUTE_DIR		:=	./srcs/execute/
SRC_LIST_DIR		:=	./srcs/list/

OBJ_DIR				:=	./.obj/
OBJ_MAIN_DIR		:=	./.obj/main/
OBJ_PARSE_DIR		:=	./.obj/parse/
OBJ_BUILTIN_DIR		:=	./.obj/builtin/
OBJ_EXECUTE_DIR		:=	./.obj/execute/
OBJ_LIST_DIR		:=	./.obj/list/
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

SRC_MAIN_FILES		:=	$(addsuffix .c,				\
							envp					\
							error					\
							free					\
							main					\
							signal					\
						)
SRC_PARSE_FILES		:=	$(addsuffix .c,				\
							chunk_control			\
							join_argv_tokens		\
							make_cmd				\
							parse					\
							split_by_parameter		\
							split_by_quote			\
							syntax_check			\
							treat_dollar			\
							treat_heredoc			\
							treat_redir				\
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
SRC_LIST_FILES		:=	$(addsuffix .c,				\
							clear_list				\
							type_cmd				\
							type_env				\
							type_redir				\
							type_token				\
						)
OBJ_MAIN_FILES		:=	$(SRC_MAIN_FILES:.c=.o)
OBJ_PARSE_FILES		:=	$(SRC_PARSE_FILES:.c=.o)
OBJ_BUILTIN_FILES	:=	$(SRC_BUILTIN_FILES:.c=.o)
OBJ_EXECUTE_FILES	:=	$(SRC_EXECUTE_FILES:.c=.o)
OBJ_LIST_FILES		:=	$(SRC_LIST_FILES:.c=.o)
JSON_FILES			:=	compile_commands

SRC_MAIN			:=	$(addprefix $(SRC_MAIN_DIR),	$(SRC_MAIN_FILES))
SRC_PARSE			:=	$(addprefix $(SRC_PARSE_DIR),	$(SRC_PARSE_FILES))
SRC_BUILTIN			:=	$(addprefix $(SRC_BUILTIN_DIR),	$(SRC_BUILTIN_FILES))
SRC_EXECUTE			:=	$(addprefix $(SRC_EXECUTE_DIR),	$(SRC_EXECUTE_FILES))
SRC_LIST			:=	$(addprefix $(SRC_LIST_DIR),	$(SRC_LIST_FILES))

OBJ_MAIN			:=	$(addprefix $(OBJ_MAIN_DIR),	$(OBJ_MAIN_FILES))
OBJ_PARSE			:=	$(addprefix $(OBJ_PARSE_DIR),	$(OBJ_PARSE_FILES))
OBJ_BUILTIN			:=	$(addprefix $(OBJ_BUILTIN_DIR),	$(OBJ_BUILTIN_FILES))
OBJ_EXECUTE			:=	$(addprefix $(OBJ_EXECUTE_DIR),	$(OBJ_EXECUTE_FILES))
OBJ_LIST			:=	$(addprefix $(OBJ_LIST_DIR),	$(OBJ_LIST_FILES))
JSON				:=	$(addsuffix .json,				$(JSON_FILES))

# SRC_FOLDER			:=	$(SRC_DIR)
OBJ_FOLDER			:=	$(OBJ_DIR)			\
						$(OBJ_MAIN_DIR)		\
						$(OBJ_PARSE_DIR)	\
						$(OBJ_BUILTIN_DIR)	\
						$(OBJ_EXECUTE_DIR)	\
						$(OBJ_LIST_DIR)
OBJS				:=	$(OBJ_MAIN)			\
						$(OBJ_PARSE)		\
						$(OBJ_BUILTIN)		\
						$(OBJ_EXECUTE)		\
						$(OBJ_LIST)
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

$(OBJ_MAIN_DIR)	:
	@if [ ! -d $(OBJ_MAIN_DIR) ]; then \
		mkdir -p $(OBJ_MAIN_DIR); \
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

$(OBJ_LIST_DIR)	:
	@if [ ! -d $(OBJ_LIST_DIR) ]; then \
		mkdir -p $(OBJ_LIST_DIR); \
	fi

$(NAME)	:	$(OBJS)
	@make -s -C $(LIBFT_DIR) all
	@$(CC) $(CFLAGS) $(LDFLAGS) $(DBFLAGS) -o $@ $^
	@(printf [ && find . -name "*.part.json" | xargs cat && printf ]) > $(JSON);
	@echo "\033[01;32m         SUCCESS!        \033[0m"

$(OBJ_MAIN_DIR)%.o		:	$(SRC_MAIN_DIR)%.c
	@$(CC) $(CFLAGS) $(DBFLAGS) $(CPPFLAGS) $(MJFLAGS) -c -o $@ $<

$(OBJ_PARSE_DIR)%.o		:	$(SRC_PARSE_DIR)%.c
	@$(CC) $(CFLAGS) $(DBFLAGS) $(CPPFLAGS) $(MJFLAGS) -c -o $@ $<

$(OBJ_BUILTIN_DIR)%.o	:	$(SRC_BUILTIN_DIR)%.c
	@$(CC) $(CFLAGS) $(DBFLAGS) $(CPPFLAGS) $(MJFLAGS) -c -o $@ $<

$(OBJ_EXECUTE_DIR)%.o	:	$(SRC_EXECUTE_DIR)%.c
	@$(CC) $(CFLAGS) $(DBFLAGS) $(CPPFLAGS) $(MJFLAGS) -c -o $@ $<

$(OBJ_LIST_DIR)%.o	:	$(SRC_LIST_DIR)%.c
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
