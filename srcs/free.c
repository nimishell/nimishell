/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:30:42 by wbae              #+#    #+#             */
/*   Updated: 2023/05/12 19:19:15 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ms_free(char *p1, char *p2, char *p3, char *p4)
{
	if (p1)
		free(p1);
	if (p2)
		free(p2);
	if (p3)
		free(p3);
	if (p4)
		free(p4);
	return (NULL);
}

void	ft_free_char_arr(char **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		if (p[i])
		{
			free(p[i]);
			p[i] = NULL;
		}
		i++;
	}
	free(p);
}

void	ft_free_token(t_token **token)
{
	t_token	*remove_token;

	if (!*token)
		return ;
	while (*token)
	{
		remove_token = *token;
		*token = (*token)->next;
		if (remove_token->str)
		{
			free(remove_token->str);
			remove_token->str = NULL;
		}
		free(remove_token);
	}
}

void	ft_free_cmd(t_cmd **cmd)
{
	t_cmd	*remove_cmd;

	if (!*cmd)
		return ;
	while (*cmd)
	{
		remove_cmd = *cmd;
		*cmd = (*cmd)->next;
		if (remove_cmd->argv)
			ft_free_char_arr(remove_cmd->argv);
		if (remove_cmd->redir_in)
			ft_free_redir(&remove_cmd->redir_in);
		if (remove_cmd->redir_out)
			ft_free_redir(&remove_cmd->redir_out);
		free(remove_cmd);
	}
}

void	ft_free_redir(t_redir **redir)
{
	t_redir	*remove_redir;

	if (!*redir)
		return ;
	while (*redir)
	{
		remove_redir = *redir;
		*redir = (*redir)->next;
		if (remove_redir->file)
		{
			free(remove_redir->file);
			remove_redir->file = NULL;
		}
		free(remove_redir);
	}
}
