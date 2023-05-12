/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:08:22 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/12 21:26:29 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_command.h"
#include "heredoc.h"
#include "minishell.h"
#include "open_file.h"
#include "terminate.h"

int	is_builtin(char *command)
{
	const char	*builtin[7] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	int			index;

	index = 0;
	while (index < 7)
	{
		if (ft_strncmp(command, builtin[index], ft_strlen(builtin[index]) + 1) \
			== 0)
			return (TRUE);
		index++;
	}
	return (FALSE);
}

static void	child_process(t_cmd *cmd, int pipe_fd[2])
{
	int	result;

	set_sig(DEFAULT, DEFAULT);
	open_infile(cmd);
	open_outfile(cmd, pipe_fd);
	close_unused_fd(cmd, pipe_fd);
	if (cmd->argv[0] == NULL)
		exit(0);
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

int	set_fds_before_new_cmd(t_cmd **cur, int pipe_fd[2])
{
	close(pipe_fd[WR]);
	if ((*cur)->prev != NULL)
		close((*cur)->fds[INPUT]);
	if ((*cur)->next == NULL)
		return (0);
	*cur = (*cur)->next;
	(*cur)->fds[INPUT] = pipe_fd[RD];
	return (1);
}

void	execute_multi_process(t_cmd *cmd)
{
	t_cmd	*cur;
	int		pipe_fd[2];
	int		cmd_count;

	set_sig(IGNORE, IGNORE);
	signal(SIGPIPE, SIG_IGN);
	cur = cmd;
	if (has_heredoc(cur))
		execute_heredoc(cur);
	cmd_count = 0;
	while (cur != NULL)
	{
		if (pipe(pipe_fd) == -1)
			exit_with_errno(NULL, NULL, EXIT_FAILURE);
		cur->pid = fork();
		if (cur->pid < 0)
			exit_with_errno(NULL, NULL, EXIT_FAILURE);
		else if (cur->pid == 0)
			child_process(cur, pipe_fd);
		cmd_count++;
		if (set_fds_before_new_cmd(&cur, pipe_fd) == 0)
			break ;
	}
	close(pipe_fd[RD]);
	g_env->status = wait_child_process(cmd_count, cur->pid);
}
