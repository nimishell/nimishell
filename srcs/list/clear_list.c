/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:03:45 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/15 16:52:08 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "ft_free.h"
#include <stddef.h>

void	cmd_clear(t_cmd *cmd)
{
	t_cmd_node	*remove;

	remove = cmd->head;
	if (remove == NULL)
		return ;
	while (remove != NULL)
	{
		cmd->head = remove->next;
		ft_free_cmd(cmd, remove);
		remove = cmd->head;
	}
	cmd->tail = NULL;
}

void	env_clear(void)
{
	t_env_node	*remove;

	remove = g_env.head;
	if (remove == NULL)
		return ;
	while (remove != NULL)
	{
		g_env.head = remove->next;
		ft_free_env(remove);
		remove = g_env.head;
	}
	g_env.tail = NULL;
}

void	redir_clear(t_redir **redir)
{
	t_redir	*remove;

	remove = *redir;
	if (remove == NULL)
		return ;
	while (remove != NULL)
	{
		*redir = remove->next;
		ft_free_redir(remove);
		remove = *redir;
	}
	*redir = NULL;
}

void	token_clear(t_token **token)
{
	t_token	*remove;

	remove = *token;
	if (remove == NULL)
		return ;
	while (remove != NULL)
	{
		*token = remove->next;
		ft_free_token(remove);
		remove = *token;
	}
	*token = NULL;
}
