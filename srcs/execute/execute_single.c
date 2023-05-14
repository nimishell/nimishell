/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:36:46 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/14 21:16:54 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"
#include "open_file.h"
#include "execute_command.h"
#include <unistd.h>

int	is_single_builtin(t_cmd_node *node)
{
	return (node->prev == NULL && node->next == NULL \
		&& node->argv[0] != NULL && is_builtin(node->argv[0]) == TRUE);
}

static void	init_backup_fd(int backup_fd[2])
{
	backup_fd[STDIN_FILENO] = -1;
	backup_fd[STDOUT_FILENO] = -1;
}

static void	backup_std_fd(t_cmd_node *cmd, int backup_fd[2])
{
	if (cmd->fds[INPUT] != STDIN_FILENO)
		backup_fd[STDIN_FILENO] = dup(STDIN_FILENO);
	if (cmd->fds[OUTPUT] != STDOUT_FILENO)
		backup_fd[STDOUT_FILENO] = dup(STDOUT_FILENO);
}

static void	recover_std_fd(int backup_fd[2])
{
	if (backup_fd[STDIN_FILENO] != -1)
		dup2(backup_fd[STDIN_FILENO], STDIN_FILENO);
	if (backup_fd[STDOUT_FILENO] != -1)
		dup2(backup_fd[STDOUT_FILENO], STDOUT_FILENO);
}

void	execute_single_process(t_cmd *cmd)
{
	t_cmd_node	*cur;
	int			backup_fd[2];

	cur = cmd->head;
	if (has_heredoc(cur))
		execute_heredoc(cur);
	open_infile(cur);
	init_backup_fd(backup_fd);
	backup_std_fd(cur, backup_fd);
	execute_builtin(cur->argv);
	recover_std_fd(backup_fd);
}
