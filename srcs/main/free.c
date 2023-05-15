/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:30:42 by wbae              #+#    #+#             */
/*   Updated: 2023/05/15 16:53:20 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_list.h"
#include <stdlib.h>

void	ft_free_cmd(t_cmd *cmd, t_cmd_node *node)
{
	ft_free_strings(&node->argv);
	if (node->redir_in != NULL)
		redir_clear(&node->redir_in);
	if (node->redir_out != NULL)
		redir_clear(&node->redir_out);
	free(node);
	cmd->size--;
}

void	ft_free_env(t_env_node *node)
{
	free(node->key);
	if (node->value != NULL)
	{
		free(node->value);
		g_env.value_count--;
	}
	free(node);
	g_env.key_count--;
}

void	ft_free_redir(t_redir *remove)
{
	if (remove->fd != -1)
		close(remove->fd);
	ft_free_str(&remove->file);
	free(remove);
}

void	ft_free_token(t_token *remove)
{
	if (remove->str != NULL)
		ft_free_str(&remove->str);
	free(remove);
}

void	*ft_free_ptrs(char *ptr1, char *ptr2, char *ptr3)
{
	if (ptr1 != NULL)
		free(ptr1);
	if (ptr2 != NULL)
		free(ptr2);
	if (ptr3 != NULL)
		free(ptr3);
	return (NULL);
}
