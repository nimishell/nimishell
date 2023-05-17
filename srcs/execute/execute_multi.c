/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:08:22 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/17 21:47:08 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "heredoc.h"
#include "execute_command.h"
#include "open_file.h"
#include "ft_signal.h"
#include "terminate.h"
#include "error.h"

static void	child_process(t_cmd_node *cmd, int pipe_fd[2])
{
	int	result;

	set_sig(DEFAULT, DEFAULT);
	open_infile(cmd);
	open_outfile(cmd, pipe_fd);
	close_unused_fd(cmd, pipe_fd);
	if (cmd->argv[0] == NULL)
	{
		close(cmd->fds[INPUT]);
		exit(0);
	}
	else if (is_builtin(cmd->argv[0]) == TRUE)
	{
		result = execute_builtin(cmd->argv);
		exit(result);
	}
	else
		execute_command(cmd->argv);
}

int	wait_child_process(int count, pid_t last_pid)
{
	int		state;
	pid_t	cur_pid;
	int		result;

	while (count--)
	{
		cur_pid = wait(&state);
		if (cur_pid == -1)
			return (EXIT_FAILURE);
		else if (cur_pid == last_pid)
			result = state;
	}
	if (WIFEXITED(result))
		return (WEXITSTATUS(result));
	if (WIFSIGNALED(result))
	{
		print_terminate_code(result);
		return (WTERMSIG(result) + EXIT_SIGNAL);
	}
	else
		return (WSTOPSIG(result));
}

int	set_fds_before_new_cmd(t_cmd_node *cur, int pipe_fd[2])
{
	close(pipe_fd[WR]);
	if (cur->prev != NULL)
		close(cur->fds[INPUT]);
	if (cur->next == NULL)
		return (0);
	cur->next->fds[INPUT] = pipe_fd[RD];
	return (1);
}

void	execute_multi_process(t_cmd *cmd)
{
	t_cmd_node	*cur;
	int			pipe_fd[2];

	set_sig(IGNORE, IGNORE);
	cur = cmd->head;
	while (cur != NULL)
	{
		if (pipe(pipe_fd) == -1)
			exit_with_errno(NULL, NULL, EXIT_FAILURE);
		cur->pid = fork();
		if (cur->pid < 0)
			exit_with_errno(NULL, NULL, EXIT_FAILURE);
		else if (cur->pid == 0)
			child_process(cur, pipe_fd);
		if (set_fds_before_new_cmd(cur, pipe_fd) == 0)
			break ;
		cur = cur->next;
	}
	close(pipe_fd[RD]);
	g_env.status = wait_child_process(cmd->size, cur->pid);
}
