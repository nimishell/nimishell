/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:08:22 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/25 13:34:34 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "minishell.h"
#include "execute.h"
#include "pipe.h"
#include "open_file.h"
#include "terminate.h"

static int	is_builtin(char *command)
{
	const char	*builtin[7] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	int			index;

	index = 0;
	while (index < 7)
	{
		if (ft_strncmp(command, builtin[index], ft_strlen(builtin[index]) + 1))
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
	if (command == NULL)
		exit_with_errno(NULL, NULL, EXIT_FAILURE);
	if (close(pipe_fd[RD]) == -1)
		exit_with_errno(command[0], command[1], EXIT_FAILURE);
	if (cmd->file->infile != NULL)
		open_infile(cmd->file, cmd->redir);
	if (dup2(cmd->file->infile_fd, STDIN_FILENO) == -1 \
		&& close(cmd->file->infile_fd) == -1)
		exit_with_errno(command[0], command[1], EXIT_FAILURE);
	if (cmd->file->outfile != NULL)
		open_outfile(cmd->file, cmd->redir);
	if (dup2(cmd->file->outfile_fd, STDOUT_FILENO) == -1)
		exit_with_errno(command[0], command[1], EXIT_FAILURE);
	if (cmd->file->outfile != NULL \
		&& close(cmd->file->outfile_fd) == -1)
		exit_with_errno(command[0], command[1], EXIT_FAILURE);
	free_cmd(&cmd);
	if (close(pipe_fd[WR]) == -1)
		exit_with_errno(command[0], command[1], EXIT_FAILURE);
	if (is_builtin(command[0]) == FALSE)
		execute_command(command[0], command);
	execute_builtin(command[0], command);
}

static void	wait_child_process(t_cmd *cmd, pid_t last_pid)
{
	int		state;
	pid_t	cur_pid;
	int		result;

	while (cmd != NULL)
	{
		cur_pid = wait(&state);
		if (cur_pid == -1)
			exit_with_errno(NULL, NULL, EXIT_FAILURE);
		else if (cur_pid == last_pid)
			result = state;
		cmd = cmd->next;
	}
	if (WIFEXITED(result))
		exit(WEXITSTATUS(result));
	if (WIFSIGNALED(result))
	{
		print_terminate_code(result);
		exit(WTERMSIG(result) + EXIT_SIGNAL);
	}
}

void	execute_multi_process(t_cmd *cmd)
{
	t_cmd	*cur;
	int		pipe_fd[2];

	cur = cmd;
	while (cur != NULL)
	{
		if (pipe(pipe_fd) == -1)
			exit_with_errno(NULL, NULL, EXIT_FAILURE);
		cur->pid = fork();
		if (cur->pid < 0)
			exit_with_errno(NULL, NULL, EXIT_FAILURE);
		else if (cur->pid == 0)
			child_process(cmd, pipe_fd);
		close(pipe_fd[WR]);
		close(cur->file->infile_fd);
		cur->file->infile_fd = pipe_fd[RD];
		cur = cur->next;
	}
	close(pipe_fd[RD]);
	wait_child_process(cmd, cur->pid);
}
