/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 21:42:06 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/22 21:48:08 by yeongo           ###   ########.fr       */
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
	input_str = get_next_line(0);
	while (input_str != NULL
		&& ft_strncmp(input_str, limiter, limiter_size) != 0)
	{
		ft_putstr_fd(input_str, pipe_heredoc[1]);
		free(input_str);
		input_str = get_next_line(0);
	}
	if (input_str != NULL)
		free(input_str);
	close(pipe_heredoc[1]);
	return (pipe_heredoc[0]);
}

void	open_infile(t_file_fd *file_fd, int redir[2])
{
	if (redir[INPUT] == 1)
	{
		file_fd->infile_fd = open(file_fd->infile, O_RDONLY);
		if (file_fd->infile_fd == -1)
			exit_with_errno("zsh", file_fd->infile, EXIT_FAILURE);
	}
	else
	{
		file_fd->infile_fd = get_heredoc(file_fd->infile);
		ft_free_str(&(file_fd->infile));
	}
}

void	open_outfile(t_file_fd *file_fd, int redir[2])
{
	if (redir[OUTPUT] == 1)
		file_fd->outfile_fd = open(file_fd->outfile, \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		file_fd->outfile_fd = open(file_fd->outfile, \
			O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (file_fd->outfile_fd == -1)
		exit_with_errno("zsh", file_fd->outfile, EXIT_FAILURE);
}
