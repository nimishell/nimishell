/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:00:31 by wbae              #+#    #+#             */
/*   Updated: 2023/05/14 20:37:37 by wbae             ###   ########.fr       */
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
				ft_syntax_error(ft_strdup("|"));
				return (FAIL);
			}
		}
		token = token->next;
	}
	return (SUCCESS);
}

static int	check_syntax_redir(t_token *token)
{
	if (ft_strcspn(token->str, ">>"))
		token->type = T_IO_RR;
	else if (ft_strcspn(token->str, "<<"))
		token->type = T_IO_LL;
	else if (ft_strcspn(token->str, ">"))
		token->type = T_IO_R;
	else if (ft_strcspn(token->str, "<"))
		token->type = T_IO_L;
	if (!token->next)
	{
		ft_syntax_error(ft_strdup("newline"));
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
		return (FAIL);
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
