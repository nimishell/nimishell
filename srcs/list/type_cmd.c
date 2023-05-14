/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:39:58 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/14 20:21:02 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_list.h"
#include <stdio.h>

t_cmd_node	*cmd_new(void)
{
	t_cmd_node	*new;

	new = ft_calloc(1, sizeof(t_cmd_node));
	if (new == NULL)
		return (NULL);
	new->fds[INPUT] = STDIN_FILENO;
	new->fds[OUTPUT] = STDOUT_FILENO;
	return (new);
}

void	cmd_add_back(t_cmd *cmd, t_cmd_node *new)
{
	if (new == NULL)
		return ;
	new->prev = cmd->tail;
	if (cmd->head == NULL)
		cmd->head = new;
	else
		cmd->tail->next = new;
	cmd->tail = new;
	cmd->size++;
}

void	ft_free_cmd(t_cmd_node *node)
{
	ft_free_strings(&node->argv);
	if (node->redir_in != NULL)
		redir_clear(&node->redir_in);
	if (node->redir_out != NULL)
		redir_clear(&node->redir_out);
	free(node);
	g_env.key_count--;
}

void	cmd_remove_back(t_cmd *cmd)
{
	t_cmd_node	*remove;

	if (cmd->tail == NULL)
		return ;
	remove = cmd->tail;
	cmd->tail = cmd->tail->prev;
	if (cmd->tail == NULL)
		cmd->head = NULL;
	else
		cmd->tail->next = NULL;
	ft_free_strings(&remove->argv);
	free(remove);
	cmd->size--;
}
