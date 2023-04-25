/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:23:50 by wbae              #+#    #+#             */
/*   Updated: 2023/04/25 20:45:34 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

static t_token	*detach_token(t_token **token, int size)
{
	t_token	*head;
	t_token	*end_token;

	head = *token;
	while (--size)
		(*token) = (*token)->next;
	end_token = *token;
	if ((*token)->next != NULL)
	{
		(*token) = (*token)->next->next;
		free (end_token->next->str);
		free (end_token->next);
		end_token->next = NULL;
	}
	else
		*token = (*token)->next;
	return (head);
}

static int	get_cmd_size(t_token *token)
{
	int		size;

	size = 0;
	while (token && token->type != T_PIPE)
	{
		size++;
		token = token->next;
	}
	return (size);
}

int	token_into_cmd(t_cmd **cmd, t_token *token)
{
	t_cmd	*tmp;
	int		cnt;
	int		i;

	cnt = 0;
	while (token)
	{
		i = 0;
		tmp = ft_calloc(1, sizeof(t_cmd));
		if (!tmp)
			return (FAIL);
		tmp->size = get_cmd_size(token);
		cmd_add_back(cmd, tmp);
		tmp->token = detach_token(&token, tmp->size);
	}
	return (SUCCESS);
}

void	check_cmd(t_cmd *cmd)
{
	t_token	*cur;

	cur = cmd->token;
	while (cur)
	{
		if (cur->type == T_IO_L)
		{
			if (!cur->next)
				ft_syntax_error("near unexpected token `newline'", 1, 0);
			cmd->file->infile = ft_strdup(cur->next->str);
		}
		cur = cur->next;
	}
}

// if (cmd->token == NULL || (cur->next != NULL || cur->next->next == NULL || cur->next->next->type == T_PIPE))
