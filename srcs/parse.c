/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 21:32:19 by wbae              #+#    #+#             */
/*   Updated: 2023/04/22 14:15:22 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	tokenize(t_token *token, char *rd_line)
{
	rd_line = ft_strtrim(rd_line, " ");
	if (rd_line == NULL)
		return (FAIL);
	if (ft_split_token(&token, rd_line) == FAIL)
	{
		token_clear(&token);
		return (FAIL);
	}
	treat_dollar(token);
	remove_empty_token(&token);
	check_special(token);
	debug_print_tokens(token);
	return (SUCCESS);
}

int	parse(t_cmd *cmd, char *rd_line)
{
	t_token	*token;
	int		flag;

	cmd = ft_calloc(1, sizeof(t_cmd));
	token = NULL;
	flag = tokenize(token, rd_line);
	if (!flag)
	{
		syntax_error(NULL, 1, 0);
		return (0);
	}
	ft_free_token(token);
	return (1);
}
