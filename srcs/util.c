/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:30:42 by wbae              #+#    #+#             */
/*   Updated: 2023/04/12 16:24:44 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_free(void *p1, void *p2, void *p3, void *p4)
{
	if (p1)
		free(p1);
	if (p2)
		free(p2);
	if (p3)
		free(p3);
	if (p4)
		free(p4);
	return (NULL);
}

void	*ft_free_char_arr(char **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		if (p[i])
			free(p[i]);
		i++;
	}
	free(p);
	return (NULL);
}

void	ft_free_token(t_token *tok)
{
	t_token	*cur;
	t_token	*next;

	cur = tok;
	while (cur)
	{
		next = cur->next;
		free(cur->str);
		free(cur);
		cur = next;
	}
}
