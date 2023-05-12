/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_argv_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:01:44 by wbae              #+#    #+#             */
/*   Updated: 2023/05/12 19:12:14 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	join_argv_tokens(t_token **lst)
{
	t_token	**head;
	t_token	*cur;
	char	*ret;

	head = lst;
	cur = *lst;
	while (cur && cur->next)
	{
		if (cur->type == T_ARGV && cur->next->type == T_ARGV)
		{
			ret = ft_strjoin(cur->str, cur->next->str);
			free(cur->str);
			cur->str = ret;
			remove_single_token(head, cur->next);
		}
		else
			cur = cur->next;
	}
}
