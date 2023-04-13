/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:54:53 by wbae              #+#    #+#             */
/*   Updated: 2023/04/13 21:03:42 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	tokenize_pipe(t_token *token)
{
	while (token)
	{
		if (token->type == T_CHUNK)
			split_pipe(token, token->str);
		token = token->next;
	}
}

void	split_pipe(t_token *token, char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	while (str[i] && str[i] != '|')
		i++;
	if (!str[i])
		return ;
	add_token(&token, 2, T_CHUNK, ft_substr(str, i + 1, ft_strlen(str) - i));
	add_token(&token, 1, T_PIPE, ft_strdup("|"));
	tmp = ft_substr(str, 0, i);
	free(token->str);
	token->str = ft_strdup(tmp);
	free(tmp);
}
