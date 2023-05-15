/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:39:58 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/15 16:51:20 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_list.h"

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
