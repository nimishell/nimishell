/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:25:35 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/17 15:45:20 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "execute_process.h"
#include "ft_signal.h"
#include "error.h"
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>

int	has_heredoc(t_cmd_node *cmd)
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

static void	expand_env_in_str(char **str)
{
	t_env_node	*cur;
	int			position;

	position = ft_strcspn(*str, "$");
	while ((*str)[position] != '\0')
	{
		cur = g_env.head;
		while (cur != NULL)
		{
			if (ft_strnstr(&(*str)[position], cur->key, \
					ft_strlen(&(*str)[position]) + 1) != NULL)
			{
				*str = ft_replace_str(str, cur->key, cur->value, position);
				break ;
			}
			else
			{
				*str = ft_strdup("");
				break ;
			}
			cur = cur->next;
		}
		position = ft_strcspn(*str, "$");
	}
}

static void	get_heredoc(char *limiter, int pipe_fd[2])
{
	size_t	limiter_size;
	char	*input_str;

	set_sig(HEREDOC, IGNORE);
	close(pipe_fd[RD]);
	limiter_size = ft_strlen(limiter);
	input_str = readline("> ");
	while ((input_str != NULL || input_str[0] == '\0') \
		&& ft_strncmp(input_str, limiter, limiter_size + 1) != 0)
	{
		expand_env_in_str(&input_str);
		ft_putendl_fd(input_str, pipe_fd[WR]);
		free(input_str);
		input_str = readline("> ");
	}
	if (input_str != NULL)
		free(input_str);
	close(pipe_fd[WR]);
	exit(0);
}

void	execute_heredoc(t_cmd_node *cmd)
{
	t_redir	*cur;
	int		pipe_fd[2];

	cur = cmd->redir_in;
	while (cur != NULL)
	{
		if (cur->type == T_IO_LL)
		{
			if (pipe(pipe_fd) == -1)
				exit_with_errno(NULL, "pipe", EXIT_FAILURE);
			cur->pid = fork();
			if (cur->pid < 0)
				exit_with_errno(NULL, NULL, EXIT_FAILURE);
			else if (cur->pid == 0)
				get_heredoc(cur->file, pipe_fd);
			close(pipe_fd[WR]);
			cur->fd = pipe_fd[RD];
		}
		g_env.status = wait_child_process(1, cur->pid);
		if (cur->next == NULL)
			break ;
		cur = cur->next;
	}
}
