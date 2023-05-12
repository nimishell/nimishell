/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:10:57 by wbae              #+#    #+#             */
/*   Updated: 2023/05/12 21:38:29 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

t_token	*new_token(char *str, int type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = ft_strdup(str);
	new->type = type;
	new->next = NULL;
	return (new);
}

t_token	*token_add_back(t_token **lst, t_token *new)
{
	t_token	*cur;

	if (new == NULL)
		return (NULL);
	if (*lst == NULL)
	{
		*lst = new;
		return (new);
	}
	cur = *lst;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = new;
	return (new);
}

t_token	*remove_single_token(t_token **lst, t_token *target)
{
	t_token	*prev;
	t_token	*cur;

	if (*lst == NULL || target == NULL)
		return (NULL);
	if (*lst == target)
	{
		free(target->str);
		target = target->next;
		free(*lst);
		*lst = target;
		return (target);
	}
	cur = *lst;
	while (cur != target)
	{
		prev = cur;
		cur = cur->next;
	}
	prev->next = cur->next;
	free(cur->str);
	free(cur);
	return (prev->next);
}

void	cmd_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*cur;

	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	cur = *lst;
	while (cur->next != NULL)
		cur = cur->next;
	new->prev = cur;
	cur->next = new;
}

void	redir_add_back(t_redir **lst, t_redir *new)
{
	t_redir	*cur;

	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	cur = *lst;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = new;
}
