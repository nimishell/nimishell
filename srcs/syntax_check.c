/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:00:31 by wbae              #+#    #+#             */
/*   Updated: 2023/05/10 21:02:19 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

static int	check_syntax_pipe(t_token *token)
{
	while (token)
	{
		if (token->type == T_PIPE)
		{
			if (ft_strlen(token->str) != 1 || !token->next)
			{
				ft_syntax_error(ft_substr(token->str, 0, 2));
				return (FAIL);
			}
		}
		token = token->next;
	}
	return (SUCCESS);
}

static int	check_syntax_redir(t_token *token)
{
	if (token->str[0] == '>')
	{
		token->type = T_IO_R;
		if (token->str[1] == '>')
			token->type = T_IO_RR;
	}
	else if (token->str[0] == '<')
	{
		token->type = T_IO_L;
		if (token->str[1] == '<')
			token->type = T_IO_LL;
	}
	if (!token->next)
	{
		ft_syntax_error("newline");
		return (FAIL);
	}
	if (token->next->type != T_ARGV)
	{
		ft_syntax_error(ft_substr(token->next->str, 0, 2));
		return (FAIL);
	}
	return (SUCCESS);
}

int	check_syntax(t_token *token)
{
	if (!token)
	{
		ft_syntax_error("\'");
		return (FAIL);
	}
	if (token && token->type == T_PIPE)
	{
		ft_syntax_error(ft_substr(token->str, 0, 2));
		return (FAIL);
	}
	while (token)
	{
		if (token->type == T_REDIR)
			if (!check_syntax_redir(token))
				return (FAIL);
		if (token->type >= T_PIPE)
			if (!check_syntax_pipe(token))
				return (FAIL);
		token = token->next;
	}
	return (SUCCESS);
}
