/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:34:11 by wbae              #+#    #+#             */
/*   Updated: 2023/05/02 20:29:33 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "libft.h"

static int	is_redir(char *argv)
{
	int	len;

	len = ft_strlen(argv);
	if (!ft_strncmp(argv, "<", len))
		return (T_IO_L);
	else if (!ft_strncmp(argv, "<<", len))
		return (T_IO_LL);
	else if (!ft_strncmp(argv, ">", len))
		return (T_IO_R);
	else if (!ft_strncmp(argv, ">>", len))
		return (T_IO_RR);
	return (0);
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

static void	handle_io(t_cmd *cmd)
{
	int		idx;
	int		tmp_idx;
	t_redir	*new;

	idx = 0;
	while (cmd->argv[idx])
	{
		if (is_redir(cmd->argv[idx]))
		{
			new = ft_calloc(1, sizeof(t_redir));
			new->type = is_redir(cmd->argv[idx]);
			new->file = ft_strdup(cmd->argv[idx + 1]);
			redir_add_back(&cmd->redir, new);
			tmp_idx = idx;
			shift_array(cmd, tmp_idx);
		}
		else
			idx++;
	}
}

void	treat_redir(t_cmd *cmd)
{
	while (cmd)
	{
		handle_io(cmd);
		cmd = cmd->next;
	}
}
