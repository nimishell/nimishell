/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:34:11 by wbae              #+#    #+#             */
/*   Updated: 2023/05/08 21:25:19 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "libft.h"
#include "structure.h"

static int	is_redir_in(char *argv)
{
	if (!ft_strncmp(argv, "<", 2))
		return (T_IO_L);
	else if (!ft_strncmp(argv, "<<", 3))
		return (T_IO_LL);
	return (0);
}

static int	is_redir_out(char *argv)
{
	if (!ft_strncmp(argv, ">", 2))
		return (T_IO_R);
	else if (!ft_strncmp(argv, ">>", 3))
		return (T_IO_RR);
	return (0);
}

static t_redir	*init_redir_node(char **argv, int index)
{
	t_redir	*new_node;

	new_node = ft_calloc(1, sizeof(t_redir));
	new_node->type |= (is_redir_in(argv[index]) \
						| is_redir_out(argv[index]));
	new_node->fd = -1;
	new_node->file = ft_strjoin(argv[index + 1], "\n");
	return (new_node);
}

static void	shift_array(t_cmd *cmd, int tmp_idx)
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

void	treat_redir(t_cmd *cmd)
{
	int		idx;
	t_redir	*new;

	while (cmd)
	{
		idx = 0;
		while (cmd->argv[idx])
		{
			if (is_redir_in(cmd->argv[idx]))
			{
				new = init_redir_node(cmd->argv, idx);
				redir_add_back(&cmd->redir_in, new);
				shift_array(cmd, idx);
			}
			else if (is_redir_out(cmd->argv[idx]))
			{
				new = init_redir_node(cmd->argv, idx);
				redir_add_back(&cmd->redir_out, new);
				shift_array(cmd, idx);
			}
			else
				idx++;
		}
		cmd = cmd->next;
	}
}
