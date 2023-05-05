/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 21:42:06 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/05 13:21:31 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <string.h>

static char	*expand_env(char **str, t_env *env, int position)
{
	size_t	len_str;
	size_t	len_key;
	size_t	len_val;
	size_t	m_size;
	char	*result;

	len_str = ft_strlen(*str);
	len_key = ft_strlen(env->key);
	len_val = ft_strlen(env->value);
	m_size = len_str + len_val - len_key;
	result = ft_calloc(m_size, sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_memmove(result, str, position);
	ft_memmove(&result[position], env->value, len_val);
	ft_memmove(&result[position + len_val], &str[position + len_key + 1], \
			len_str - position - len_key - 1);
	ft_free_str(str);
	return (result);
}

void	expand_env_in_str(char **str)
{
	t_env	*cur;
	int		position;

	position = ft_strcspn(*str, "$");
	while ((*str)[position] != '\0')
	{
		cur = g_env;
		while (cur != NULL)
		{
			if (ft_strnstr(&(*str)[position], cur->key, \
				ft_strlen(&(*str)[position])))
			{
				*str = expand_env(str, cur, position);
				break ;
			}
			cur = cur->next;
		}
		position = strcspn(*str, "$");
	}
}

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
	if (input_str != NULL)
		ft_strapp_back(&input_str, "\n");
	while (input_str != NULL
		&& ft_strncmp(input_str, limiter, limiter_size) != 0)
	{
		expand_env_in_str(&input_str);
		ft_putstr_fd(input_str, pipe_heredoc[WR]);
		free(input_str);
		input_str = readline("> ");
		if (input_str != NULL)
			ft_strapp_back(&input_str, "\n");
	}
	if (input_str != NULL)
		free(input_str);
	close(pipe_heredoc[WR]);
	return (pipe_heredoc[RD]);
}

void	remove_redir(t_redir **redir)
{
	t_redir	*cur;

	cur = *redir;
	while (cur != NULL)
	{
		if (cur->next != NULL && cur->fd != -1)
			close(cur->fd);
		ft_free_str(&cur->file);
		*redir = cur->next;
		free(cur);
		cur = *redir;
	}
}

void	open_infile(t_cmd *cmd)
{
	t_redir	*cur;

	cur = cmd->redir_in;
	if (cur == NULL)
		return ;
	while (cur != NULL)
	{
		if (cur->type == T_IO_L)
		{
			cur->fd = open(cur->file, O_RDONLY);
			if (cur->fd == -1)
				exit_with_errno("zsh", cur->file, EXIT_FAILURE);
		}
		if (cur->next == NULL)
			break ;
		cur = cur->next;
	}
	cmd->fds[INPUT] = cur->fd;
	remove_redir(&cmd->redir_in);
}

void	open_outfile(t_cmd *cmd, int pipe_fd[2])
{
	t_redir	*cur;

	if (cmd->next != NULL)
		cmd->fds[OUTPUT] = pipe_fd[WR];
	cur = cmd->redir_out;
	if (cur == NULL)
		return ;
	while (cur != NULL)
	{
		if (cur->type == T_IO_R)
			cur->fd = open(cur->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (cur->type == T_IO_RR)
			cur->fd = open(cur->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (cur->fd == -1)
			exit_with_errno("zsh", cur->file, EXIT_FAILURE);
		if (cur->next == NULL)
			break ;
		cur = cur->next;
	}
	cmd->fds[OUTPUT] = cur->fd;
	remove_redir(&cmd->redir_out);
}

void	close_unused_fd(t_cmd *cmd, int pipe_fd[2])
{
	close(pipe_fd[RD]);
	if (!(cmd->prev == NULL && cmd->fds[INPUT] == STDIN_FILENO))
	{
		dup2(cmd->fds[INPUT], STDIN_FILENO);
		close(cmd->fds[INPUT]);
	}
	if (!(cmd->next == NULL && cmd->fds[OUTPUT] == STDOUT_FILENO))
	{
		dup2(cmd->fds[OUTPUT], STDOUT_FILENO);
		close(cmd->fds[OUTPUT]);
	}
	if (cmd->fds[OUTPUT] != pipe_fd[WR])
		close(pipe_fd[WR]);
}
