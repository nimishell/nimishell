/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 21:32:19 by wbae              #+#    #+#             */
/*   Updated: 2023/05/03 19:21:02 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	check_heredoc_delimiter(t_token *token)
{
	while (token)
	{
		if (token->type == T_IO_LL)
			token->next->type = T_CHUNK;
		token = token->next;
	}
}

t_token	*tokenize(t_token *token, char *rd_line)
{
	rd_line = ft_strtrim(rd_line, " ");
	if (rd_line == NULL)
		return (NULL);
	if (ft_split_token(&token, rd_line) == FAIL)
		return (NULL);
	remove_empty_space(&token);
	return (token);
}

int	parse(t_cmd **cmd, char *rd_line)
{
	t_token	*token;

	token = NULL;
	token = tokenize(token, rd_line);
	if (!check_syntax(token))
	{
		ft_free_token(&token);
		return (FAIL);
	}
	check_heredoc_delimiter(token);
	treat_dollar(token);
	debug_print_tokens(token);
	if (!token_into_cmd(cmd, token))
	{
		ft_free_token(&token);
		return (FAIL);
	}
	treat_redir(*cmd);
	debug_print_cmd(*cmd);
	ft_free_token(&token);
	return (SUCCESS);
}
