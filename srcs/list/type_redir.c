/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 22:41:20 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/15 16:51:20 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structure.h"

t_redir	*redir_new(void)
{
	t_redir	*new;

	new = ft_calloc(1, sizeof(t_redir));
	if (new == NULL)
		return (NULL);
	return (new);
}

t_redir	*redir_last(t_redir *redir)
{
	t_redir	*cur;

	cur = redir;
	if (cur == NULL)
		return (NULL);
	while (cur->next != NULL)
		cur = cur->next;
	return (cur);
}

void	redir_add_back(t_redir **redir, t_redir *new)
{
	t_redir	*tail;

	if (new == NULL)
		return ;
	if (*redir == NULL)
	{
		*redir = new;
		return ;
	}
	tail = redir_last(*redir);
	tail->next = new;
}
