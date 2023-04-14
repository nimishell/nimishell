/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   after_split_chunk.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:00:31 by wbae              #+#    #+#             */
/*   Updated: 2023/04/14 17:42:17 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	remove_empty_token(t_token **lst)
{
	t_token	*rm;
	t_token	*cur;

	cur = *lst;
	while (cur && cur->next)
	{
		if (cur->next->str[0] == '\0')
		{
			rm = cur->next;
			cur->next = cur->next->next;
			free(rm->str);
			free(rm);
		}
		cur = cur->next;
	}
	cur = *lst;
	if (cur && cur->str[0] == '\0')
	{
		*lst = cur->next;
		free(cur->str);
		free(cur);
	}
}

