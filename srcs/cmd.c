/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:23:50 by wbae              #+#    #+#             */
/*   Updated: 2023/04/26 15:42:56 by wbae             ###   ########.fr       */
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
		free(end_token->next->str);
		free(end_token->next);
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
		tmp = new_cmd();
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
	while (cmd)
	{
		treat_input(cmd);
		treat_output(cmd);
		cmd = cmd->next;
	}
}

void	treat_input(t_cmd *cmd)
{
	t_token	*cur;

	while (cmd->token && \
		(cmd->token->type == T_IO_L || cmd->token->type == T_IO_LL))
	{
		cur = cmd->token;
		cmd->file->infile = ft_strdup(cur->next->str);
		cmd->file->infile_fd = -1;
		cmd->token = cmd->token->next->next;
		remove_single_token(&cur, cur->next);
		remove_single_token(&cur, cur);
	}
	cur = cmd->token;
	while (cur && cur->next)
	{
		if (cur->next->type == T_IO_L || cur->next->type == T_IO_LL)
		{
			cmd->file->infile = ft_strdup(cur->next->next->str);
			cmd->file->infile_fd = -1;
			remove_single_token(&cur, cur->next->next);
			remove_single_token(&cur, cur->next);
		}
		cur = cur->next;
	}
}

void	treat_output(t_cmd *cmd)
{
	t_token	*cur;

	while (cmd->token && \
		(cmd->token->type == T_IO_R || cmd->token->type == T_IO_RR))
	{
		cur = cmd->token;
		cmd->file->outfile = ft_strdup(cur->next->str);
		cmd->file->outfile_fd = -1;
		cmd->token = cmd->token->next->next;
		remove_single_token(&cur, cur->next);
		remove_single_token(&cur, cur);
	}
	cur = cmd->token;
	while (cur && cur->next)
	{
		if (cur->next->type == T_IO_R || cur->next->type == T_IO_RR)
		{
			cmd->file->outfile = ft_strdup(cur->next->next->str);
			cmd->file->outfile_fd = -1;
			remove_single_token(&cur, cur->next->next);
			remove_single_token(&cur, cur->next);
		}
		cur = cur->next;
	}
}
