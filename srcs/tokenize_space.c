/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:46:42 by wbae              #+#    #+#             */
/*   Updated: 2023/04/13 20:39:40 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	tokenize_space(t_token *token)
{
	while (token)
	{
		if (token->type == T_CHUNK && ft_isspace_str(token->str))
			split_space(token, token->str);
		token = token->next;
	}
}

void	split_space(t_token *token, char *str)
{
	int		i;
	char	*prev;
	char	*next;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	next = ft_substr(str, i + 1, ft_strlen(str) - i);
	add_token(&token, 2, T_CHUNK, next);
	add_token(&token, 1, T_SPACE, ft_strdup(" "));
	prev = ft_substr(str, 0, i);
	free(token->str);
	token->str = ft_strdup(prev);
	free(prev);
}
