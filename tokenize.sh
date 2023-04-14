#!/bin/bash
cc ft_split_token.c libft/srcs/ft_calloc.c libft/srcs/ft_strtrim.c libft/srcs/ft_substr.c libft/srcs/ft_memset.c libft/srcs/ft_strlen.c libft/srcs/ft_bzero.c libft/srcs/ft_strchr.c libft/srcs/ft_strdup.c libft/srcs/ft_strlcpy.c -I./libft/inc;
./a.out "   gndk     | kdjkf ||||| <<<<< >>>> \"gn'd'kfj\" '.....'  "
