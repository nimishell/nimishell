/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:55:15 by wbae              #+#    #+#             */
/*   Updated: 2023/04/20 21:03:34 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parsing.h"

int	split_squote(t_token **token, char **rd_line, t_token *new)
{
	char *const	line_start = *rd_line;
	int			line_length;
	int			count_squote;

	line_length = 0;
	count_squote = 1;
	(*rd_line)++;
	while (**rd_line && **rd_line != '\'')
	{
		line_length++;
		(*rd_line)++;
	}
	if (**rd_line == '\'')
		count_squote++;
	if (count_squote != 2)
		return (FAIL);
	new->str = ft_substr(line_start, 1, line_length);
	if (new->str == NULL)
		return (FAIL);
	new->type = T_CHUNK;
	token_add_back(token, new);
	if (**rd_line != '\0')
		(*rd_line)++;
	return (SUCCESS);
}

int	split_dquote(t_token **token, char **rd_line, t_token *new)
{
	char *const	line_start = *rd_line;
	int			line_length;
	int			count_dquote;

	line_length = 0;
	count_dquote = 1;
	(*rd_line)++;
	while (**rd_line && **rd_line != '\"')
	{
		line_length++;
		(*rd_line)++;
	}
	if (**rd_line == '\"')
		count_dquote++;
	if (count_dquote != 2)
		return (FAIL);
	new->str = ft_substr(line_start, 1, line_length);
	if (new->str == NULL)
		return (FAIL);
	new->type = T_ECHUNK;
	token_add_back(token, new);
	if (**rd_line != '\0')
		(*rd_line)++;
	return (SUCCESS);
}

int	split_pipe(t_token **token, char **rd_line, t_token *new)
{
	char *const	line_start = *rd_line;
	int			line_length;

	line_length = 0;
	while (**rd_line == '|')
	{
		line_length++;
		(*rd_line)++;
	}
	new->str = ft_substr(line_start, 0, line_length);
	if (new->str == NULL)
		return (FAIL);
	new->type = T_PIPE;
	token_add_back(token, new);
	return (SUCCESS);
}

int	split_redir(t_token **token, char **rd_line, t_token *new, char rd)
{
	char *const	line_start = *rd_line;
	int			line_length;

	line_length = 0;
	while (**rd_line == redir_char)
	{
		line_length++;
		(*rd_line)++;
	}
	new->str = ft_substr(line_start, 0, line_length);
	if (new->str == NULL)
		return (FAIL);
	new->type = T_REDIR;
	token_add_back(token, new);
	return (SUCCESS);
}

int	split_space(t_token **token, char **rd_line, t_token *new)
{
	char *const	line_start = *rd_line;
	int			line_length;

	line_length = 0;
	while (**rd_line == ' ' || **rd_line == '\t' || **rd_line == '\n')
	{
		line_length++;
		(*rd_line)++;
	}
	new->str = ft_substr(line_start, 0, line_length);
	if (new->str == NULL)
		return (FAIL);
	new->type = T_SPACE;
	token_add_back(token, new);
	return (SUCCESS);
}
