/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_special.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:24:57 by wbae              #+#    #+#             */
/*   Updated: 2023/04/12 18:52:22 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize_special(t_token *token)
{
	// t_token	*next;
	t_token	*head;

	head = token;
	while (token)
	{
		if (token->type == T_CHUNK)
			split_str_io(token, token->str);
		token = token->next;
	}
}

void	split_str_io(t_token *token, char *str)
{
	int		flag;
	int		i;

	i = 0;
	while (str[i] && str[i] != '<' && str[i] != '>')
		i++;
	if (!str[i])
		return ;
	flag = 0;
	while (str[i] == '<' || str[i] == '>')
	{
		if (str[i] == '<')
		{
			if (str[i + 1] == '<' && flag == 0)
				flag = 1;
			tokenize_io(token, ft_strdup("<"), i, flag);
			break ;
		}
		else if (str[i] == '>')
		{
			if (str[i + 1] == '>' && flag == 0)
				flag = 1;
			tokenize_io(token, ft_strdup(">"), i, flag);
			break ;
		}
	}
}

void	tokenize_io(t_token *token, char *s, int idx, int flag)
{
	char	*tmp;

	if (flag == 0)
	{
		add_token(&token, 2, T_CHUNK, ft_substr(token->str, idx + 1, \
			ft_strlen(token->str) - idx));
		add_token(&token, 1, T_IO_L, ft_strdup(s));
		tmp = ft_substr(token->str, 0, idx);
		free(token->str);
		token->str = ft_strdup(tmp);
		free(tmp);
	}
	else
	{
		s = ft_strjoin(s, s);
		add_token(&token, 2, T_CHUNK, ft_substr(token->str, idx + 2, \
			ft_strlen(token->str) - idx));
		add_token(&token, 1, T_IO_LL, ft_strdup(s));
		tmp = ft_substr(token->str, 0, idx);
		free(token->str);
		token->str = ft_strdup(tmp);
		free(tmp);
	}
}
