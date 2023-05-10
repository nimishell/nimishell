/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:25:17 by wbae              #+#    #+#             */
/*   Updated: 2023/05/10 20:09:41 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	remove_empty_space(t_token **lst)
{
	t_token	**head;
	t_token	*cur;

	head = lst;
	cur = *lst;
	while (cur)
	{
		if (cur->type == T_SPACE)
		{
			cur = remove_single_token(head, cur);
			continue ;
		}
		cur = cur->next;
	}
	// if (*lst && (*lst)->str[0] == '\0')
	// {
	// 	free((*lst)->str);
	// 	free(*lst);
	// }
}

void	chunk_to_argv(t_token **lst)
{
	t_token	**head;
	t_token	*cur;

	head = lst;
	cur = *lst;
	while (cur)
	{
		if (cur->type == T_CHUNK)
		{
			if (cur->str[0] != '\0')
			{
				cur->type = T_ARGV;
				cur = cur->next;
			}
			else
			{
				cur = remove_single_token(head, cur);
			}
		}
		else
			cur = cur->next;
	}
}
