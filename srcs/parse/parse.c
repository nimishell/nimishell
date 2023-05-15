/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:30:05 by wbae              #+#    #+#             */
/*   Updated: 2023/05/15 21:53:31 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_list.h"
#include "parsing.h"
#include "error.h"

static int	check_heredoc_limiter(t_token *token)
{
	while (token)
	{
		if (token->type == T_CHUNK)
		{
			if (!treat_heredoc(token, ft_strdup(token->str)))
			{
				ft_syntax_error(ft_strdup("\'"));
				return (FAIL);
			}
		}
		token = token->next;
	}
	return (SUCCESS);
}

static int	split_by_quote(t_token *token)
{
	char	**split;

	while (token)
	{
		while (token->type == T_CHUNK && \
			(ft_strchr(token->str, '\'') || ft_strchr(token->str, '\"')))
		{
			split = split_quote(token->str);
			if (split)
			{
				make_split_to_token(token, split);
				ft_free_strings(&split);
			}
			else
			{
				ft_syntax_error(ft_strdup("\'"));
				return (FAIL);
			}
		}
		token = token->next;
	}
	return (SUCCESS);
}

static int	free_token_exit(t_token **token)
{
	token_clear(token);
	return (FAIL);
}

int	tokenize(t_token *token)
{
	if (!check_heredoc_limiter(token) || !split_by_quote(token))
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

int	parse(t_cmd *cmd, char *rd_line)
{
	t_token	*token;

	token = token_new(rd_line, T_CHUNK);
	if (!tokenize(token))
		return (free_token_exit(&token));
	chunk_to_argv(&token);
	join_argv_tokens(&token);
	remove_empty_space(&token);
	if (!check_syntax(token))
		return (free_token_exit(&token));
	if (!token_to_cmd(cmd, token))
		return (free_token_exit(&token));
	treat_redir(cmd->head);
	token_clear(&token);
	return (SUCCESS);
}
