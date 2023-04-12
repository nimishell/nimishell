/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:24:57 by wbae              #+#    #+#             */
/*   Updated: 2023/04/12 20:38:52 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	tokenize_redirection(t_token *token)
{
	t_token	*head;

	head = token;
	while (token)
	{
		if (token->type == T_CHUNK)
			before_split_io(token, token->str);
		token = token->next;
	}
	while (head)
	{
		if (head->type == T_RED)
			change_type_red(head);
		head = head->next;
	}
}

void	before_split_io(t_token *token, char *str)
{
	int	flag;
	int	i;

	i = 0;
	while (str[i] && str[i] != '<' && str[i] != '>')
		i++;
	if (!str[i])
		return ;
	flag = 0;
	if (str[i] == '<')
	{
		if (str[i + 1] == '<' && flag == 0)
			flag = 1;
		split_io(token, ft_strdup("<"), i, flag);
	}
	else if (str[i] == '>')
	{
		if (str[i + 1] == '>' && flag == 0)
			flag = 1;
		split_io(token, ft_strdup(">"), i, flag);
	}
}

void	split_io(t_token *token, char *s, int idx, int flag)
{
	char	*tmp;

	if (flag == 0)
	{
		add_token(&token, 2, T_CHUNK, ft_substr(token->str, idx + 1, \
			ft_strlen(token->str) - idx));
		add_token(&token, 1, T_RED, ft_strdup(s));
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
		add_token(&token, 1, T_RED, ft_strdup(s));
		tmp = ft_substr(token->str, 0, idx);
		free(token->str);
		token->str = ft_strdup(tmp);
		free(tmp);
	}
}

void	change_type_red(t_token *token)
{
	if (*(token->str) == '<')
	{
		if (ft_strncmp(token->str, "<<", 2))
		{
			token->type = T_IO_LL;
			return ;
		}
		token->type = T_IO_L;
		return ;
	}
	else
	{
		if (ft_strncmp(token->str, ">>", 2))
		{
			token->type = T_IO_RR;
			return ;
		}
		token->type = T_IO_R;
		return ;
	}
}
