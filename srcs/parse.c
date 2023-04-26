/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 21:32:19 by wbae              #+#    #+#             */
/*   Updated: 2023/04/26 17:46:20 by wbae             ###   ########.fr       */
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
	return (token);
}

int	parse(t_cmd **cmd, char *rd_line)
{
	t_token	*token;

	token = NULL;
	token = tokenize(token, rd_line);
	if (!token)
	{
		ft_syntax_error("\'", 1, 0);
		return (FAIL);
	}
	treat_dollar(token);
	remove_empty_space(&token);
	if (!check_special(token))
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
