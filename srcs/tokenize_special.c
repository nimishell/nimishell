/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_special.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:24:57 by wbae              #+#    #+#             */
/*   Updated: 2023/04/11 20:57:48 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize_special(t_token *token)
{
	t_token	*next;
	t_token	*head;

	head = token;
	while (token)
	{
		if (token->type == T_CHUNK)
			tokenize_io_redirection(token);
		token = token->next;
	}
}

char	**split_str_io(char *str)
{
	char	**ret;
	char	**iter;
	char	*s;
	int		size;
	int		flag;

	size = 1;
	while (*str != '<' || *str != '>')
		str++;
	flag = 0;
	while (*str)
	{
		if (*str == '<' || *str == '>')
		{
			size++;
			flag = 1;
		}
		else if (flag)
		{
			size++;
			flag = 0;
		}
		str++;
	}
	ret = malloc(sizeof(char *) * size + 1);
	if (!ret)
		return (NULL);
	iter = ret;
	while (--size)
	{
		s = 
		*(iter++) = s;
	}
	*iter = NULL;
	return (ret);
}
