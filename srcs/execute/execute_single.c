/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:36:46 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/12 05:30:13 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"
#include "open_file.h"
#include "execute_command.h"
#include <unistd.h>

int	is_single_builtin(t_cmd *cmd)
{
	return (cmd->prev == NULL && cmd->next == NULL \
		&& cmd->argv[0] != NULL && is_builtin(cmd->argv[0]) == TRUE);
}

static void	init_backup_fd(int backup_fd[2])
{
	backup_fd[STDIN_FILENO] = -1;
	backup_fd[STDOUT_FILENO] = -1;
}

static void	backup_std_fd(t_cmd *cmd, int backup_fd[2])
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
	t_cmd	*cur;
	int		backup_fd[2];

	cur = cmd;
	if (has_heredoc(cur))
		execute_heredoc(cur);
	open_infile(cmd);
	init_backup_fd(backup_fd);
	backup_std_fd(cmd, backup_fd);
	execute_builtin(cmd->argv);
	recover_std_fd(backup_fd);
}
