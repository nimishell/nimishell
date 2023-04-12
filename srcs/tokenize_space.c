/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:46:42 by wbae              #+#    #+#             */
/*   Updated: 2023/04/11 17:59:58 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize_space(t_token *token)
{
	t_token	*head;

	head = token;
	while (token)
	{
		if (token->type == T_CHUNK && ft_isspace_str(token->str))
			split_space(token);
		token = token->next;
	}
}

void	split_space(t_token *token)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (token->str[++i] && token->str[i] != ' ')
		;
	j = i;
	while (token->str[++j])
		;
	add_token(&token, 1, T_CHUNK, ft_substr(token->str, i + 1, j - i));
	tmp = ft_substr(token->str, 0, i);
	free(token->str);
	token->str = ft_strdup(tmp);
	free(tmp);
}
