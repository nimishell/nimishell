/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   after_split_chunk.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:00:31 by wbae              #+#    #+#             */
/*   Updated: 2023/04/25 21:23:44 by wbae             ###   ########.fr       */
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
	if (cur && cur->str[0] == '\0')
	{
		*lst = cur->next;
		free(cur->str);
		free(cur);
	}
}

static int32_t	treat_redir(t_token *token)
{
	if (token->str[0] == '>')
	{
		token->type = T_IO_R;
		if (token->str[1] == '>')
			token->type = T_IO_RR;
		if (!token->next)
		{
			ft_syntax_error("newline", 1, 0);
			return (FAIL);
		}
	}
	else if (token->str[0] == '<')
	{
		token->type = T_IO_L;
		if (token->str[1] == '<')
			token->type = T_IO_LL;
		if (!token->next)
		{
			ft_syntax_error("newline", 1, 0);
			return (FAIL);
		}
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
	t_token	*head;
	int		flag;

	head = token;
	while (head)
	{
		if (head->type == T_REDIR)
		{
			if (!treat_redir(head))
				return (FAIL);
		}
		head = head->next;
	}
	head = token;
	while (head)
	{
		if (head->type >= T_PIPE)
			flag = check_syntax(head);
		if (!flag)
			return (FAIL);
		head = head->next;
	}
	return (SUCCESS);
}
