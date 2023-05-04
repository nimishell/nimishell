/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:08:22 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/04 16:47:01 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (ft_strncmp(command, builtin[index], ft_strlen(builtin[index]) + 1) \
			== 0)
			return (TRUE);
		index++;
	}
	return (FALSE);
}

void	free_cmd(t_cmd **cmd)
{
	ft_free_strings(&((*cmd)->argv));
	free(*cmd);
	*cmd = NULL;
}

static void	child_process(t_cmd *cmd, int pipe_fd[2])
{
	open_infile(cmd);
	open_outfile(cmd, pipe_fd);
	close_unused_fd(cmd, pipe_fd);
	set_sig(IGNORE, IGNORE);
	if (cmd->argv[0])
	{
		if (is_builtin(cmd->argv[0]) == TRUE)
			execute_builtin(cmd->argv);
		else
			execute_command(cmd->argv);
	}
}

static int	wait_child_process(t_cmd *cmd, pid_t last_pid)
{
	int		state;
	pid_t	cur_pid;
	int		result;

	result = 0;
	while (cmd != NULL)
	{
		cur_pid = wait(&state);
		if (cur_pid == -1)
		{
			// ft_perror("hi", "bye");
			return (EXIT_FAILURE);
		}
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
	t_redir	*cur;

	cur = cmd->redir_in;
	while (cur != NULL)
	{
		if (cur->type == T_IO_LL)
			return (TRUE);
		cur = cur->next;
	}
	return (FALSE);
}

void	execute_heredoc(t_cmd *cmd)
{
	t_redir	*cur;

	cur = cmd->redir_in;
	while (cur != NULL)
	{
		if (cur->type == T_IO_LL)
		{
			cur->fd = get_heredoc(cur->file);
			ft_free_str(&(cur->file));
		}
		cur = cur->next;
	}
}

int	set_fds_before_new_cmd(t_cmd **cur, int pipe_fd[2])
{
	close(pipe_fd[WR]);
	if (!((*cur)->prev == NULL && (*cur)->fd[INPUT] == STDIN_FILENO))
		close((*cur)->fd[INPUT]);
	if ((*cur)->next == NULL)
		return (0);
	*cur = (*cur)->next;
	(*cur)->fd[INPUT] = pipe_fd[RD];
	return (1);
}

void	execute_multi_command(t_cmd *cmd)
{
	t_cmd	*cur;
	int		pipe_fd[2];

	cur = cmd;
	if (has_heredoc(cur))
		execute_heredoc(cur);
	while (cur != NULL)
	{
		if (pipe(pipe_fd) == -1)
			exit_with_errno(NULL, NULL, EXIT_FAILURE);
		set_sig(DEFAULT, DEFAULT);
		cur->pid = fork();
		if (cur->pid < 0)
			exit_with_errno(NULL, NULL, EXIT_FAILURE);
		else if (cur->pid == 0)
			child_process(cur, pipe_fd);
		else
			if (set_fds_before_new_cmd(&cur, pipe_fd) == 0)
				break ;
	}
	close(pipe_fd[RD]);
	wait_child_process(cmd, cur->pid);
}
