/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:34:11 by wbae              #+#    #+#             */
/*   Updated: 2023/05/14 18:46:43 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "libft.h"
#include "ft_list.h"

static int	is_redir(char *argv)
{
	if (!ft_strncmp(argv, "<", 2))
		return (T_IO_L);
	else if (!ft_strncmp(argv, "<<", 3))
		return (T_IO_LL);
	else if (!ft_strncmp(argv, ">", 2))
		return (T_IO_R);
	else if (!ft_strncmp(argv, ">>", 3))
		return (T_IO_RR);
	return (0);
}

static t_redir	*init_redir_node(char **argv, int index)
{
	t_redir	*new;

	new = redir_new();
	new->type = is_redir(argv[index]);
	new->fd = -1;
	if (new->type == T_IO_LL)
		new->file = ft_strjoin(argv[index + 1], "\n");
	else
		new->file = ft_strdup(argv[index + 1]);
	return (new);
}

static void	shift_array(t_cmd_node *cmd, int tmp_idx)
{
	ft_free_str(&cmd->argv[tmp_idx++]);
	ft_free_str(&cmd->argv[tmp_idx++]);
	while (cmd->argv[tmp_idx] != NULL)
	{
		cmd->argv[tmp_idx - 2] = ft_strdup(cmd->argv[tmp_idx]);
		ft_free_str(&cmd->argv[tmp_idx]);
		tmp_idx++;
	}
	cmd->argv[tmp_idx] = NULL;
}

void	treat_redir(t_cmd_node *node)
{
	int		idx;
	int		redir;
	t_redir	*new;

	while (node)
	{
		idx = 0;
		while (node->argv[idx])
		{
			redir = is_redir(node->argv[idx]);
			if (redir)
			{
				new = init_redir_node(node->argv, idx);
				if (redir == T_IO_L || redir == T_IO_LL)
					redir_add_back(&node->redir_in, new);
				else
					redir_add_back(&node->redir_out, new);
				shift_array(node, idx);
			}
			else
				idx++;
		}
		node = node->next;
	}
}
