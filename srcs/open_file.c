/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 21:42:06 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/24 22:59:30 by yeongo           ###   ########.fr       */
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

void	open_infile(t_file *file, int redir[2])
{
	if (redir[INPUT] == 1)
	{
		file->infile_fd = open(file->infile, O_RDONLY);
		if (file->infile_fd == -1)
			exit_with_errno("zsh", file->infile, EXIT_FAILURE);
	}
	else
	{
		file->infile_fd = get_heredoc(file->infile);
		ft_free_str(&(file->infile));
	}
}

void	open_outfile(t_file *file, int redir[2])
{
	if (redir[OUTPUT] == 1)
		file->outfile_fd = open(file->outfile, \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		file->outfile_fd = open(file->outfile, \
			O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (file->outfile_fd == -1)
		exit_with_errno("zsh", file->outfile, EXIT_FAILURE);
}
