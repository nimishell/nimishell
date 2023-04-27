/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:08:22 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/27 21:14:40 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "minishell.h"
#include "execute.h"
#include "pipe.h"
#include "open_file.h"
#include "terminate.h"
#include <sys/errno.h>

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

static void	child_process(char **command)
{
	// char	**command;
	//
	// if (command == NULL)
	// 	exit_with_errno(NULL, NULL, EXIT_FAILURE);
	// if (close(pipe_fd[RD]) == -1)
	// 	exit_with_errno(command[0], command[1], EXIT_FAILURE);
	//
	// if (dup2(cmd->file->infile_fd, STDIN_FILENO) == -1 \
	// 	|| close(cmd->file->infile_fd) == -1)
	// 	exit_with_errno(command[0], command[1], EXIT_FAILURE);
	//
	// if (dup2(cmd->file->outfile_fd, STDOUT_FILENO) == -1)
	// 	exit_with_errno(command[0], command[1], EXIT_FAILURE);
	// if (cmd->file->outfile != NULL \
	// 	|| close(cmd->file->outfile_fd) == -1)
	// 	exit_with_errno(command[0], command[1], EXIT_FAILURE);
	//
	// if (close(pipe_fd[WR]) == -1)
	// 	exit_with_errno(command[0], command[1], EXIT_FAILURE);
	//
	if (is_builtin(command[0]) == FALSE)
		execute_command(command[0], command);
	execute_builtin(command[0], command);
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
			exit_with_errno(NULL, NULL, EXIT_FAILURE);
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
	// if (WIFSTOPPED(result))
	else
		return (WSTOPSIG(result));
	// return (0);
}

void	execute_multi_process(t_cmd *cmd)
{
	t_cmd	*cur;
	int		pipe_fd[2];
	char	**command;

	cur = cmd;
	while (cur != NULL)
	{
		if (pipe(pipe_fd) == -1)
			exit_with_errno(NULL, NULL, EXIT_FAILURE);
		cur->pid = fork();
		if (cur->pid < 0)
			exit_with_errno(NULL, NULL, EXIT_FAILURE);
		else if (cur->pid == 0)
		{
			command = token_to_command(cmd->token);
			open_infile(cmd);
			open_outfile(cmd, pipe_fd);
			// printf("hi 1\n");
			close_unused_fd(cmd, pipe_fd);
			// printf("hi 2\n");
			child_process(command);
		}
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
