/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:25:35 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/06 12:26:30 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	*expand_env(char **str, t_env *env, int position)
{
	size_t	len_str;
	size_t	len_key;
	size_t	len_val;
	size_t	m_size;
	char	*result;

	len_str = ft_strlen(*str);
	len_key = ft_strlen(env->key) + 1;
	len_val = ft_strlen(env->value);
	m_size = len_str + len_val - len_key;
	result = ft_calloc(m_size + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_memmove(result, *str, position);
	ft_memmove(&result[position], env->value, len_val);
	ft_memmove(&result[position + len_val], &(*str)[position + len_key], \
			len_str - position - len_key);
	ft_free_str(str);
	return (result);
}

static void	expand_env_in_str(char **str)
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
					ft_strlen(&(*str)[position])) != NULL)
			{
				*str = expand_env(str, cur, position);
				break ;
			}
			cur = cur->next;
		}
		position = ft_strcspn(*str, "$");
	}
}

static int	get_heredoc(char *limiter)
{
	int		pipe_heredoc[2];
	size_t	limiter_size;
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

void	execute_heredoc(t_cmd *cmd)
{
	t_redir	*cur;

	cur = cmd->redir_in;
	while (cur != NULL)
	{
		if (cur->type == T_IO_LL)
			cur->fd = get_heredoc(cur->file);
		cur = cur->next;
	}
}
