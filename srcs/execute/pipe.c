/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:08:22 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/22 15:14:21 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

# define EXIT_SIGNAL 128

static void	child(t_fd *fd, t_argument *args, int index)
{
	char	**command;

	command = ft_split(args->vector[index], ' ');
	if (close(fd->pipe[0]) == -1)
		exit_with_perror("zsh", command[0], EXIT_FAILURE);
	if (index == 2 + args->heredoc->is_heredoc)
		open_infile(fd, args);
	if (dup2(fd->infile, STDIN_FILENO) == -1)
		exit_with_perror("zsh", command[0], EXIT_FAILURE);
	if (close(fd->infile) == -1)
		exit_with_perror("zsh", command[0], EXIT_FAILURE);
	if (dup2(fd->pipe[1], STDOUT_FILENO) == -1)
		exit_with_perror("zsh", command[0], EXIT_FAILURE);
	if (close(fd->pipe[1]) == -1)
		exit_with_perror("zsh", command[0], EXIT_FAILURE);
	execve_command(command, args->env_path);
}

static void	child_last(t_fd *fd, t_argument *args, int index)
{
	char	**command;

	command = ft_split(args->vector[index], ' ');
	if (close(fd->pipe[0]) == -1)
		exit_with_perror("zsh", command[0], EXIT_FAILURE);
	if (dup2(fd->infile, STDIN_FILENO) == -1)
		exit_with_perror("zsh", command[0], EXIT_FAILURE);
	if (close(fd->infile) == -1)
		exit_with_perror("zsh", command[0], EXIT_FAILURE);
	open_outfile(fd, args);
	if (dup2(fd->outfile, STDOUT_FILENO) == -1)
		exit_with_perror("zsh", command[0], EXIT_FAILURE);
	if (close(fd->outfile) == -1)
		exit_with_perror("zsh", command[0], EXIT_FAILURE);
	if (close(fd->pipe[1]) == -1)
		exit_with_perror("zsh", command[0], EXIT_FAILURE);
	execve_command(command, args->env_path);
}

static void	wait_child_prcess(int count, pid_t last_pid)
{
	int	state;
	int	cur_pid;
	int	result;

	while (count)
	{
		cur_pid = wait(&state);
		if (cur_pid == -1)
			exit_with_errno(NULL, NULL, EXIT_FAILURE);
		else if (cur_pid == last_pid)
			result = state;
		count--;
	}
	if (WIFEXITED(result))
		exit(WEXITSTATUS(result));
	if (WIFSIGNALED(result))
	{
		print_terminate_code(result);
		exit(WTERMSIG(result) + EXIT_SIGNAL);
	}
}

void	execute_multi_process(t_argument *args, t_process *process, t_fd *fd)
{
	int	index;

	index = 1;
	while (index <= process->child_count)
	{
		if (pipe(fd->pipe) == -1)
			exit_with_errno(NULL, NULL, EXIT_FAILURE);
		process->id = fork();
		if (process->id < 0)
			exit_with_errno(NULL, NULL, EXIT_FAILURE);
		else if (process->id == 0)
		{
			if (index < process->child_count)
				child(fd, args, index + 1 + args->heredoc->is_heredoc);
			else
				child_last(fd, args, index + 1 + args->heredoc->is_heredoc);
		}
		close(fd->pipe[1]);
		if (index != 1)
			close(fd->infile);
		fd->infile = fd->pipe[0];
		index++;
	}
	close(fd->pipe[0]);
	wait_child_prcess(process->child_count, process->id);
}
