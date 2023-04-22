/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:08:22 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/22 23:05:33 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "execute.h"
#include "open_file.h"
#include "terminate.h"

int	token_size(t_token *token)
{
	t_token	*cur;
	int		size;

	cur = token;
	size = 0;
	while (cur != NULL)
	{
		size++;
		cur = cur->next;
	}
	return (size);
}

char	**is_cd_follow_no_dir(t_token *token)
{
	char	**result;

	result = ft_calloc(3, sizeof(char *));
	if (result == NULL)
		return (0);
	result[0] = ft_strdup(token->str);
	result[1] = ft_strdup("$HOME");
	return (result);
}

char	**token_to_cmd(t_token *token)
{
	t_token	*cur;
	int		m_size;
	char	**result;
	int		index;

	if (ft_strncmp(token->str, "cd", 3) == 0 \
		&& token->next == NULL)
	{
		result = is_cd_follow_no_dir(token);
		return (result);
	}
	cur = token;
	m_size = token_size(cur) + 1;
			m_size++;
	result = ft_calloc(m_size, sizeof(char *));
	index = 0;
	while (cur != NULL)
	{
		result[index] = ft_strdup(cur->str);
		index++;
		cur = cur->next;
	}
	return (result);
}

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
	if (is_builtin(command[0]) == FALSE)
		execute_command(command);
	execute_builtin(command[0], command);
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
