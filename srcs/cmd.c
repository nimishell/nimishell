/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:23:50 by wbae              #+#    #+#             */
/*   Updated: 2023/05/02 03:21:01 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parsing.h"

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

	while (token)
	{
		tmp = new_cmd();
		if (!tmp)
			return (FAIL);
		tmp->size = get_cmd_size(token);
		cmd_add_back(cmd, tmp);
		tmp->token = detach_token(&token, tmp->size);
	}
	return (SUCCESS);
}

static int	is_redir_in(t_token *token)
{
	return (token->type == T_IO_L || token->type == T_IO_LL);
}

static int	is_redir_out(t_token *token)
{
	return (token->type == T_IO_R || token->type == T_IO_RR);
}

void	treat_input(t_cmd *cmd)
{
	t_token	*cur;
	t_token	*tmp;

	cur = cmd->token;
	while (cur != NULL)
	{
		if (is_redir_in(cur))
		{
			cmd->redir[INPUT] = ft_strlen(cur->str);
			cmd->file->infile = ft_strdup(cur->next->str);
			tmp = cur;
			cur = cur->next->next;
			remove_single_token(&cmd->token, tmp->next);
			remove_single_token(&cmd->token, tmp);
		}
		else
			cur = cur->next;
	}
}

void	treat_output(t_cmd *cmd)
{
	t_token	*cur;
	t_token	*tmp;

	cur = cmd->token;
	while (cur != NULL)
	{
		if (is_redir_out(cur))
		{
			cmd->redir[OUTPUT] = ft_strlen(cur->str);
			cmd->file->outfile = ft_strdup(cur->next->str);
			tmp = cur;
			cur = cur->next->next;
			remove_single_token(&cmd->token, tmp->next);
			remove_single_token(&cmd->token, tmp);
		}
		else
			cur = cur->next;
	}
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
//
// void	treat_input(t_cmd *cmd)
// {
// 	t_token	*cur;
//
// 	while (cmd->token && \
// 		(cmd->token->type == T_IO_L || cmd->token->type == T_IO_LL))
// 	{
// 		cur = cmd->token;
// 		cmd->redir[INPUT] = ft_strlen(cur->str);
// 		cmd->file->infile = ft_strdup(cur->next->str);
// 		cmd->file->infile_fd = STDIN_FILENO;
// 		cmd->token = cmd->token->next->next;
// 		remove_single_token(&cur, cur->next);
// 		remove_single_token(&cur, cur);
// 	}
// 	cur = cmd->token;
// 	while (cur && cur->next)
// 	{
// 		if (cur->next->type == T_IO_L || cur->next->type == T_IO_LL)
// 		{
// 			cmd->redir[INPUT] = ft_strlen(cur->str);
// 			cmd->file->infile = ft_strdup(cur->next->next->str);
// 			cmd->file->infile_fd = STDIN_FILENO;
// 			remove_single_token(&cur, cur->next->next);
// 			remove_single_token(&cur, cur->next);
// 		}
// 		cur = cur->next;
// 	}
// }
//
// void	treat_output(t_cmd *cmd)
// {
// 	t_token	*cur;
//
// 	while (cmd->token && \
// 		(cmd->token->type == T_IO_R || cmd->token->type == T_IO_RR))
// 	{
// 		cur = cmd->token;
// 		cmd->redir[OUTPUT] = ft_strlen(cur->str);
// 		cmd->file->outfile = ft_strdup(cur->next->str);
// 		cmd->file->outfile_fd = STDOUT_FILENO;
// 		cmd->token = cmd->token->next->next;
// 		remove_single_token(&cur, cur->next);
// 		remove_single_token(&cur, cur);
// 	}
// 	cur = cmd->token;
// 	while (cur && cur->next)
// 	{
// 		if (cur->next->type == T_IO_R || cur->next->type == T_IO_RR)
// 		{
// 			cmd->redir[OUTPUT] = ft_strlen(cur->str);
// 			cmd->file->outfile = ft_strdup(cur->next->next->str);
// 			cmd->file->outfile_fd = STDOUT_FILENO;
// 			remove_single_token(&cur, cur->next->next);
// 			remove_single_token(&cur, cur->next);
// 		}
// 		cur = cur->next;
// 	}
// }
