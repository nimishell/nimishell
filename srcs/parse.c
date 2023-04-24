/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 21:32:19 by wbae              #+#    #+#             */
/*   Updated: 2023/04/24 15:44:30 by yeongo           ###   ########.fr       */
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
		token_clear(&token);
		return (NULL);
	}
	treat_dollar(token);
	remove_empty_token(&token);
	check_special(token);
	debug_print_tokens(token);
	return (token);
}

int	parse(t_cmd *cmd, char *rd_line)
{
	t_token	*token;

	cmd = ft_calloc(1, sizeof(t_cmd));
	token = NULL;
	token = tokenize(token, rd_line);
	if (!token)
	{
		syntax_error(NULL, 1, 0);
		return (0);
	}
	token_to_command(token, cmd);
	ft_free_token(token);
	return (1);
}
