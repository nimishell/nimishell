/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:10:57 by wbae              #+#    #+#             */
/*   Updated: 2023/04/26 15:02:45 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	token_add_back(t_token **lst, t_token *new)
{
	t_token	*cur;

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
	cur->next = new;
}

void	remove_single_token(t_token **lst, t_token *target)
{
	t_token	*prev;

	if (*lst == NULL)
		return ;
	if (*lst == target)
		*lst = target->next;
	else
	{
		prev = *lst;
		while (prev->next && prev->next != target)
			prev = prev->next;
		if (prev->next == target)
			prev->next = target->next;
		else
			return ;
	}
	free(target->str);
	free(target);
}
