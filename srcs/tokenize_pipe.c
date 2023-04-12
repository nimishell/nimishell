/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:54:53 by wbae              #+#    #+#             */
/*   Updated: 2023/04/12 20:10:40 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	tokenize_pipe(t_token *token)
{
	t_token	*next;
	t_token	*head;

	head = token;
	while (token)
	{
		next = token->next;
		if (token->type == T_CHUNK)
			sub_pipeline(token);
		token = next;
	}
	sep_pipeline(head);
}

void	sub_pipeline(t_token *token)
{
	t_token	*ret;
	char	**split;
	char	*str;
	int		i;

	split = ft_split(token->str, '|');
	i = 0;
	if (!split || split[0] == NULL)
		return ;
	str = ft_strdup(split[0]);
	if (!str)
	{
		ft_free_char_arr(split);
		return ;
	}
	free(token->str);
	token->str = str;
	ret = token;
	while (split[++i] && ret)
		ret = add_token(&token, i, T_CHUNK, split[i]);
	i = 0;
	ft_free_char_arr(split);
	return ;
}

void	sep_pipeline(t_token *token)
{
	t_token	*ret;

	while (token)
	{
		if (token->type == T_CHUNK && *(token->str) == '|')
		{
			ret = add_token(&token, 1, T_CHUNK, (token->str) + 1);
			if (!ret)
				return ;
			free (token->str);
			token->type = T_PIPE;
			token->str = ft_strdup("|");
			token = ret;
		}
		token = token->next;
	}
}
