/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:30:05 by wbae              #+#    #+#             */
/*   Updated: 2023/05/12 19:00:43 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

static void	check_heredoc_limiter(t_token *token)
{
	while (token)
	{
		if (token->type == T_CHUNK)
			treat_heredoc(token, ft_strdup(token->str));
		token = token->next;
	}
}

static int	free_token_exit(t_token **token)
{
	ft_free_token(token);
	return (FAIL);
}

static int	split_by_quote(t_token *token)
{
	char	**split;

	while (token)
	{
		if (token->str[0] == '\0')
			break ;
		if (token->type == T_CHUNK && \
			(ft_strchr(token->str, '\'') || ft_strchr(token->str, '\"')))
		{
			split = split_quote(token->str);
			if (split)
				make_split_to_token(token, split);
			else
			{
				ft_syntax_error("\'");
				return (FAIL);
			}
		}
		token = token->next;
	}
	return (SUCCESS);
}

int	tokenize(t_token *token)
{
	check_heredoc_limiter(token);
	if (!split_by_quote(token))
		return (FAIL);
	treat_dollar(token);
	split_by_parameter(token, " ");
	split_by_parameter(token, "|");
	split_by_parameter(token, "<<");
	split_by_parameter(token, ">>");
	split_by_parameter(token, "<");
	split_by_parameter(token, ">");
	return (SUCCESS);
}

int	parse(t_cmd **cmd, char *rd_line)
{
	t_token	*token;

	token = new_token(rd_line, T_CHUNK);
	if (!tokenize(token))
		return (free_token_exit(&token));
	chunk_to_argv(&token);
	join_argv_tokens(&token);
	remove_empty_space(&token);
	if (!check_syntax(token))
		return (free_token_exit(&token));
	debug_print_tokens(token);
	if (!token_into_cmd(cmd, token))
		return (free_token_exit(&token));
	treat_redir(*cmd);
	debug_print_cmd(*cmd);
	ft_free_token(&token);
	return (SUCCESS);
}
