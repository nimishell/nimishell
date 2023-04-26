/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   after_split_chunk.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:00:31 by wbae              #+#    #+#             */
/*   Updated: 2023/04/26 13:52:04 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	remove_empty_space(t_token **lst)
{
	t_token	*rm;
	t_token	*cur;

	cur = *lst;
	while (cur && cur->next)
	{
		if (cur->next->str[0] == '\0' || cur->next->type == T_SPACE)
		{
			rm = cur->next;
			cur->next = cur->next->next;
			free(rm->str);
			free(rm);
		}
		cur = cur->next;
	}
	cur = *lst;
	if (cur && cur->type == T_SPACE)
	{
		*lst = cur->next;
		free(cur->str);
		free(cur);
	}
}

static int	treat_redir(t_token *token)
{
	if (token->str[0] == '>')
	{
		token->type = T_IO_R;
		if (token->str[1] == '>')
			token->type = T_IO_RR;
	}
	else if (token->str[0] == '<')
	{
		token->type = T_IO_L;
		if (token->str[1] == '<')
			token->type = T_IO_LL;
	}
	if (!token->next)
	{
		ft_syntax_error("newline", 1, 0);
		return (FAIL);
	}
	if (token->next->type != T_ECHUNK && token->next->type != T_CHUNK)
	{
		ft_syntax_error(ft_substr(token->next->str, 0, 2), 1, 0);
		return (FAIL);
	}
	return (SUCCESS);
}

static int	check_syntax(t_token *token)
{
	while (token)
	{
		if (token->type == T_PIPE)
		{
			if (ft_strlen(token->str) != 1 || !token->next)
			{
				ft_syntax_error(ft_substr(token->str, 0, 2), 1, 0);
				break ;
			}
		}
		token = token->next;
	}
	if (!token)
		return (SUCCESS);
	return (FAIL);
}

int	check_special(t_token *token)
{
	if (token && token->type == T_PIPE)
	{
		ft_syntax_error(ft_substr(token->str, 0, 2), 1, 0);
		return (FAIL);
	}
	while (token)
	{
		if (token->type == T_REDIR)
		{
			if (!treat_redir(token))
				return (FAIL);
		}
		if (token->type >= T_PIPE)
		{
			if (!check_syntax(token))
				return (FAIL);
		}
		token = token->next;
	}
	return (SUCCESS);
}
