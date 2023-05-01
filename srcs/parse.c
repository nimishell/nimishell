/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 21:32:19 by wbae              #+#    #+#             */
/*   Updated: 2023/05/02 03:29:30 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

t_token	*tokenize(t_token *token, char *rd_line)
{
	rd_line = ft_strtrim(rd_line, " ");
	if (rd_line == NULL)
		return (NULL);
	if (ft_split_token(&token, rd_line) == FAIL)
	{
		ft_free_token(&token);
		return (NULL);
	}
	treat_dollar(token);
	remove_empty_space(&token);
	return (token);
}

int	parse(t_cmd **cmd, char *rd_line)
{
	t_token	*token;

	token = NULL;
	token = tokenize(token, rd_line);
	if (!token)
	{
		ft_syntax_error("\'");
		return (FAIL);
	}
	if (!check_syntax(token))
		return (FAIL);
	debug_print_tokens(token);
	if (!token_into_cmd(cmd, token))
	{
		ft_free_token(&token);
		return (FAIL);
	}
	check_cmd(*cmd);
	debug_print_cmd(*cmd);
	token = (*cmd)->token;
	// ft_free_token(&token);
	return (SUCCESS);
}
