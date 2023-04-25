/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   after_split_chunk.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:00:31 by wbae              #+#    #+#             */
/*   Updated: 2023/04/25 14:14:12 by wbae             ###   ########.fr       */
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

static void	treat_redir(t_token *token)
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
}

int	check_special(t_token *token)
{
	while (token)
	{
		if (token->type == T_REDIR)
			treat_redir(token);
		else if (token->type == T_PIPE)
		{
			if (ft_strlen(token->str) != 1)
			{
				syntax_error(" near unexpected token `||'", 1, 0);
				ft_free_token(&token);
				return (FAIL);
			}
		}
		token = token->next;
	}
	return (SUCCESS);
}
