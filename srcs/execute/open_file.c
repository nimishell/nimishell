/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 21:42:06 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/03 16:16:27 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

// void	expand_env_in_str(char *str);

int	get_heredoc(char *limiter)
{
	int		pipe_heredoc[2];
	int		limiter_size;
	char	*input_str;

	if (pipe(pipe_heredoc) == -1)
		exit_with_errno("zsh", "pipe", EXIT_FAILURE);
	if (limiter != NULL)
		limiter_size = ft_strlen(limiter);
	input_str = readline("> ");
	while (input_str != NULL
		&& ft_strncmp(input_str, limiter, limiter_size) != 0)
	{
		// expand_env_in_str(input_str);
		ft_putstr_fd(input_str, pipe_heredoc[WR]);
		free(input_str);
		input_str = readline("> ");
	}
	if (input_str != NULL)
		free(input_str);
	close(pipe_heredoc[WR]);
	return (pipe_heredoc[RD]);
}

void	open_infile(t_cmd *cmd)
{
	t_redir	*in;

	in = cmd->redir_in;
	if (in->type == T_IO_L)
	{
		cmd->fd[INPUT] = open(in->file, O_RDONLY);
		if (cmd->fd[INPUT] == -1)
			exit_with_errno("zsh", in->file, EXIT_FAILURE);
	}
}

void	open_outfile(t_cmd *cmd, int pipe_fd[2])
{
	t_redir	*out;

	out = cmd->redir_out;
	cmd->fd[OUTPUT] = pipe_fd[WR];
	if (out->type == T_IO_R)
		cmd->fd[OUTPUT] = open(out->file, \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (out->type == T_IO_RR)
		cmd->fd[OUTPUT] = open(out->file, \
			O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		return ;
	if (cmd->fd[OUTPUT] == -1)
		exit_with_errno("zsh", out->file, EXIT_FAILURE);
}

void	close_unused_fd(t_cmd *cmd, int pipe_fd[2])
{
	close(pipe_fd[RD]);
	if (cmd->redir_in)
	{
		if (!(cmd->prev == NULL && cmd->redir_in->file == NULL))
		{
			dup2(cmd->fd[INPUT], STDIN_FILENO);
			close(cmd->fd[INPUT]);
		}
	}
	if (cmd->redir_out)
	{
		if (!(cmd->next == NULL && cmd->redir_out->file == NULL))
			dup2(cmd->fd[OUTPUT], STDOUT_FILENO);
		close(cmd->fd[OUTPUT]);
		if (cmd->redir_out->file != NULL)
			close(pipe_fd[WR]);
	}
}
