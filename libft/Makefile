# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/13 15:28:56 by yeongo            #+#    #+#              #
#    Updated: 2023/04/21 19:23:01 by yeongo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=	libft.a

CC				:=	cc
CFLAGS			:=	-Wall -Wextra -Werror
CPPFLAGS		:=
MJFLAGS			 =	-MJ $@.part.json

AR				:=	ar
ARFLAGS			:=	rcus
RM				:=	rm -rf

HEADER			:=	./inc/
SRC_DIR			:=	./srcs/
OBJ_DIR			:=	./.obj/
CACHE_DIR		:=	./.cache/

SRC_FILES		:=	$(addsuffix .c,				\
						ft_atoi					\
						ft_bzero				\
						ft_calloc				\
						ft_isalnum				\
						ft_isalpha				\
						ft_isascii				\
						ft_isdigit				\
						ft_isprint				\
						ft_issign				\
						ft_isspace				\
						ft_isspace_str			\
						ft_itoa					\
						ft_memchr				\
						ft_memcmp				\
						ft_memcpy				\
						ft_memmove				\
						ft_memset				\
						ft_putchar_fd			\
						ft_putendl_fd			\
						ft_putnbr_fd			\
						ft_putstr_fd			\
						ft_split				\
						ft_strchr				\
						ft_strdup				\
						ft_striteri				\
						ft_strjoin				\
						ft_strjoin_char			\
						ft_strlcat				\
						ft_strlcpy				\
						ft_strlen				\
						ft_strmapi				\
						ft_strncmp				\
						ft_strnstr				\
						ft_strrchr				\
						ft_strtrim				\
						ft_substr				\
						ft_tolower				\
						ft_toupper				\
						ft_lstadd_back			\
						ft_lstadd_front			\
						ft_lstclear				\
						ft_lstdelone			\
						ft_lstiter				\
						ft_lstlast				\
						ft_lstmap				\
						ft_lstnew				\
						ft_lstsize				\
						ft_ultoa				\
					)
OBJ_FILES		:=	$(SRC_FILES:.c=.o)
JSON_FILES		:=	compile_commands
SRC				:=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ				:=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))
JSON			:=	$(addsuffix .json,		$(JSON_FILES))

CPPFLAGS		+=	-I$(HEADER)
SRC_FOLDER		:=	$(SRC_DIR)
OBJ_FOLDER		:=	$(OBJ_DIR)
OBJS			:=	$(OBJ)
PRINT			:=	LIBFT

.PHONY	:	all
all		:	$(OBJ_FOLDER) $(NAME)

$(OBJ_FOLDER)	:
	@if [ ! -d $(OBJ_FOLDER) ]; then \
		mkdir -p $(OBJ_FOLDER); \
	fi

$(NAME)	:	$(OBJS)
	@$(AR) $(ARFLAGS) $@ $^
	@(printf [ && find . -name "*.part.json" | xargs cat && printf ]) > $(JSON);
	@echo "\033[01;32m       LFT_SUCCESS!      \033[0m"

$(OBJ_FOLDER)%.o	:	$(SRC_FOLDER)%.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(MJFLAGS) -c -o $@ $<

.PHONY	:	clean
clean	:
	@$(RM) $(OBJ_DIR) $(CACHE_DIR)
	@echo "\033[91m    REMOVE LFT_OBJECT    \033[0m"

.PHONY	:	fclean
fclean	:	clean
	@$(RM) $(NAME)
	@echo "\033[91m     LFT_FCLEAN DONE     \033[0m"

.PHONY	:	re
re		:	fclean
	@make all
