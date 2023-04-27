/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 21:42:06 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/27 21:14:35 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_heredoc(char *limiter)
{
	int		pipe_heredoc[2];
	int		limiter_size;
	char	*input_str;

	if (pipe(pipe_heredoc) == -1)
		exit_with_errno("zsh", "pipe", EXIT_FAILURE);
	limiter_size = ft_strlen(limiter);
	input_str = readline(MINISHELL);
	while (input_str != NULL
		&& ft_strncmp(input_str, limiter, limiter_size) != 0)
	{
		ft_putstr_fd(input_str, pipe_heredoc[1]);
		free(input_str);
		input_str = readline(MINISHELL);
	}
	if (input_str != NULL)
		free(input_str);
	close(pipe_heredoc[1]);
	return (pipe_heredoc[0]);
}

void	open_infile(t_cmd *cmd)
{
	if (cmd->redir[INPUT] == 1)
	{
		cmd->file->infile_fd = open(cmd->file->infile, O_RDONLY);
		if (cmd->file->infile_fd == -1)
			exit_with_errno("zsh", cmd->file->infile, EXIT_FAILURE);
	}
	else if (cmd->redir[INPUT] == 2)
	{
		cmd->file->infile_fd = get_heredoc(cmd->file->infile);
		ft_free_str(&(cmd->file->infile));
	}
}

void	open_outfile(t_cmd *cmd, int pipe_fd[2])
{
	cmd->file->outfile_fd = pipe_fd[WR];
	printf("hi 1\n");
	if (cmd->redir[OUTPUT] == 1)
		cmd->file->outfile_fd = open(cmd->file->outfile, \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		cmd->file->outfile_fd = open(cmd->file->outfile, \
			O_WRONLY | O_APPEND | O_CREAT, 0644);
	printf("hi 2\n");
	if (cmd->file->outfile_fd == -1)
		exit_with_errno("zsh", cmd->file->outfile, EXIT_FAILURE);
	printf("hi 3\n");
}

void	close_unused_fd(t_cmd *cmd, int pipe_fd[2])
{
	close(pipe_fd[RD]);
	if (cmd->prev != NULL || cmd->file->infile_fd != -1)
	{
		dup2(cmd->file->infile_fd, STDIN_FILENO);
		close(cmd->file->infile_fd);
	}
	if (cmd->next != NULL || cmd->file->outfile != NULL)
		dup2(cmd->file->outfile_fd, STDOUT_FILENO);
	if (cmd->file->outfile != NULL)
		close(cmd->file->outfile_fd);
	close(pipe_fd[WR]);
}
