/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:25:17 by wbae              #+#    #+#             */
/*   Updated: 2023/05/14 19:26:48 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
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
			token_remove_if(head, cur);
		cur = cur->next;
	}
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
				cur->type = T_ARGV;
			else
				token_remove_if(head, cur);
		}
		cur = cur->next;
	}
}
