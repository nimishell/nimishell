/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 21:32:19 by wbae              #+#    #+#             */
/*   Updated: 2023/04/12 20:08:17 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

t_token	*tokenize(char *rd_line)
{
	t_token	*token;

	token = make_new_token();
	if (!token)
		return (NULL);
	token->type = T_CHUNK;
	token->str = rd_line;
	tokenize_quote(token);
	tokenize_space(token);
	tokenize_pipe(token);
	tokenize_special(token);
	return (token);
}

int	parse(t_cmd *cmd, char *rd_line)
{
	t_token	*token;

	cmd->size = 1;
	cmd->syntax = 0;
	cmd->token = NULL;
	if (!check_quote(rd_line))
	{
		syntax_error("syntax error", 1, 0);
		return (0);
	}
	token = tokenize(rd_line);
	token->rd_line = rd_line;
	debug_print_tokens(token);
	ft_free_token(token);
	return (1);
}
