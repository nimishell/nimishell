/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:08:22 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/02 02:57:01 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "pipe.h"
#include "open_file.h"
#include "terminate.h"
#include <stdio.h>

static int	is_builtin(char *command)
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

void	free_cmd(t_cmd **cmd)
{
	free((*cmd)->file);
	free(*cmd);
	*cmd = NULL;
}

static void	child_process(t_cmd *cmd, int pipe_fd[2])
{
	char	**command;

	command = token_to_command(cmd->token);
	open_infile(cmd);
	open_outfile(cmd, pipe_fd);
	close_unused_fd(cmd, pipe_fd);
	if (is_builtin(command[0]) == TRUE)
		execute_builtin(command);
	else
		execute_command(command);
}

static int	wait_child_process(t_cmd *cmd, pid_t last_pid)
{
	int		state;
	pid_t	cur_pid;
	int		result;

	while (cmd != NULL)
	{
		cur_pid = wait(&state);
		if (cur_pid == -1)
			exit_with_errno("hi", "bye", EXIT_FAILURE);
		else if (cur_pid == last_pid)
			result = state;
		cmd = cmd->next;
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

int	has_heredoc(t_cmd *cmd)
{
	t_cmd	*cur;

	cur = cmd;
	while (cur != NULL)
	{
		if (cur->redir[INPUT] == 2)
			return (TRUE);
		cur = cur->next;
	}
	return (FALSE);
}

void	heredoc(t_cmd *cmd)
{
	t_cmd	*cur;

	cur = cmd;
	while (cur != NULL)
	{
		if (cur->redir[INPUT] == 2)
			cur->file->infile_fd = get_heredoc(cur->file->infile);
		ft_free_str(&(cur->file->infile));
		cur = cur->next;
	}
}

void	execute_multi_command(t_cmd *cmd)
{
	t_cmd	*cur;
	int		pipe_fd[2];

	cur = cmd;
	if (has_heredoc(cur))
		heredoc(cur);
	while (cur != NULL)
	{
		if (pipe(pipe_fd) == -1)
			exit_with_errno(NULL, NULL, EXIT_FAILURE);
		cur->pid = fork();
		if (cur->pid < 0)
			exit_with_errno(NULL, NULL, EXIT_FAILURE);
		else if (cur->pid == 0)
			child_process(cur, pipe_fd);
		close(pipe_fd[WR]);
		if (cmd->prev != NULL)
			close(cmd->file->infile_fd);
		cur->file->infile_fd = pipe_fd[RD];
		if (cur->next == NULL)
			break ;
		cur = cur->next;
	}
	close(pipe_fd[RD]);
	wait_child_process(cmd, cur->pid);
}
