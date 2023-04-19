/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   after_split_chunk.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:00:31 by wbae              #+#    #+#             */
/*   Updated: 2023/04/19 18:09:06 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	remove_empty_token(t_token **lst)
{
	t_token	*rm;
	t_token	*cur;

	cur = *lst;
	while (cur && cur->next)
	{
		if (cur->next->str[0] == '\0')
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

void	check_special(t_token *token)
{
	while (token)
	{
		if (token->type == T_REDIR)
		{
			if (token->str[0] == '>')
			{
				token->type = T_IO_R;
				if (token->str[1] == '>')
				{
					token->type = T_IO_RR;
					free(token->str);
					token->str = ft_strdup(">>");
				}
			}
			else
				treat_heredoc(token);
		}
		else if (token->type == T_PIPE)
		{
			free (token->str);
			token->str = ft_strdup("|");
		}
		token = token->next;
	}
}

void	treat_heredoc(t_token *token)
{
	if (token->str[0] == '<')
	{
		token->type = T_IO_L;
		if (token->str[1] == '<')
		{
			token->type = T_IO_LL;
			free(token->str);
			token->str = ft_strdup("<<");
			while (token && token->type != T_ECHUNK)
				token = token->next;
			if (!token)
				return ;
			// if (!token)
			// 	syntax error.......
			token->type = T_CHUNK;
		}
	}
}
