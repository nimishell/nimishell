/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:10:57 by wbae              #+#    #+#             */
/*   Updated: 2023/04/11 16:00:08 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*make_new_token(void)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->rd_line = NULL;
	new->str = NULL;
	new->type = 0;
	new->next = NULL;
	return (new);
}

t_token	*add_token(t_token **tokens, int idx, int type, char *str)
{
	t_token	*new;

	if (!tokens)
		return (NULL);
	new = make_new_token();
	if (!new)
		return (NULL);
	new->type = type;
	new->str = ft_strdup(str);
	if (!new->str)
	{
		free(new);
		return (NULL);
	}
	if (!*tokens || idx == 0)
	{
		new->next = (*tokens);
		(*tokens) = new;
		return (new);
	}
	add_back_token(tokens, idx, new);
	return (new);
}

t_token	*add_back_token(t_token **tokens, int idx, t_token *new)
{
	t_token	*prev;

	prev = (*tokens);
	while (prev->next != NULL && --idx > 0)
		prev = prev->next;
	new->next = prev->next;
	prev->next = new;
	return (NULL);
}

void	remove_token_array(t_token *tokens)
{
	t_token	*next;

	next = tokens;
	while (next)
	{
		if (next->str)
			free(next->str);
		if (next->rd_line)
			free(next->rd_line);
		tokens = next;
		next = next->next;
		free (tokens);
	}
}
