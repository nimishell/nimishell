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

static int	free_token_exit(t_token **token)
{
	token_clear(token);
	return (FAIL);
}

int	tokenize(t_token *token)
{
	if (!treat_heredoc(token) || !split_by_quote(token))
		return (FAIL);
	treat_dollar_in_chunk(token);
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
