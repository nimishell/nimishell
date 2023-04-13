/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   after_split_chunk.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:00:31 by wbae              #+#    #+#             */
/*   Updated: 2023/04/13 16:18:29 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	after_split_chunk(t_token *token)
{
	t_token *next;

	next = token->next;
	// if (!ft_strncmp(token->str, " ", 1))
	// {

	// }
	while (next)
	{
		if (!ft_strncmp(next->str, " ", 1))
			remove_one_token(token, next);
		next = token->next;
	}
}
