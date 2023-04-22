/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:08:22 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/22 21:56:26 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "execute.h"
#include "open_file.h"
#include "signal.h"

char	**token_to_cmd(t_token *token);

int	is_builtin(char *cmd)
{
	const char	*builtin[7] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	int			index;

	index = 0;
	while (index < 7)
	{
		if (ft_strncmp(cmd, builtin[index], ft_strlen(builtin[index]) + 1))
			return (TRUE);
		index++;
	}
	return (FALSE);
}

static void	child_process(t_cmd *cmd, int pipe_fd[2])
{
	char	**command;

	command = token_to_cmd(cmd->token);
	if (close(pipe_fd[RD]) == -1)
		exit_with_errno(command[0], command[1], EXIT_FAILURE);
	if (cmd->file_fd->infile != NULL)
		open_infile(cmd->file_fd, cmd->redir);
	if (dup2(cmd->file_fd->infile_fd, STDIN_FILENO) == -1)
		exit_with_errno(command[0], command[1], EXIT_FAILURE);
	if (close(cmd->file_fd->infile_fd) == -1)
		exit_with_errno(command[0], command[1], EXIT_FAILURE);
	if (cmd->file_fd->outfile != NULL)
		open_outfile(cmd->file_fd, cmd->redir);
	if (dup2(cmd->file_fd->outfile_fd, STDOUT_FILENO) == -1)
		exit_with_errno(command[0], command[1], EXIT_FAILURE);
	if (cmd->file_fd->outfile != NULL)
	{
		if (close(cmd->file_fd->outfile_fd) == -1)
			exit_with_errno(command[0], command[1], EXIT_FAILURE);
	}
	if (close(pipe_fd[WR]) == -1)
		exit_with_errno(command[0], command[1], EXIT_FAILURE);
	if (is_builtin(command[0]) == TRUE)
		execute_builtin(command[0], command);
	else
		execute_command(command);
}

static void	wait_child_prcess(t_cmd *cmd, pid_t last_pid)
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

void	execute_multi_process(t_cmd *cmd, int pipe_fd[2])
{
	t_cmd	*cur_cmd;

	cur_cmd = cmd;
	while (cur_cmd != NULL)
	{
		if (pipe(pipe_fd) == -1)
			exit_with_errno(NULL, NULL, EXIT_FAILURE);
		cur_cmd->pid = fork();
		if (cur_cmd->pid < 0)
			exit_with_errno(NULL, NULL, EXIT_FAILURE);
		else if (cur_cmd->pid == 0)
			child_process(cmd, pipe_fd);
		close(pipe_fd[WR]);
		close(cur_cmd->file_fd->infile_fd);
		cur_cmd->file_fd->infile_fd = pipe_fd[RD];
		cur_cmd = cur_cmd->next;
	}
	close(pipe_fd[RD]);
	wait_child_prcess(cmd, cur_cmd->pid);
}
