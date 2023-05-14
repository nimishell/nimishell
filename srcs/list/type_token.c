/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 14:35:41 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/14 15:05:16 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structure.h"

t_token	*token_new(char *str, int type)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->str = ft_strdup(str);
	new->type = type;
	return (new);
}

t_token	*token_last(t_token *token)
{
	t_token	*cur;

	cur = token;
	if (cur == NULL)
		return (NULL);
	while (cur->next != NULL)
		cur = cur->next;
	return (cur);
}

void	token_add_back(t_token **token, t_token *new)
{
	t_token	*tail;

	if (new == NULL)
		return ;
	if (*token == NULL)
	{
		*token = new;
		return ;
	}
	tail = token_last(*token);
	tail->next = new;
}

void	ft_free_token(t_token *remove)
{
	if (remove->str != NULL)
		ft_free_str(&remove->str);
	free(remove);
}

void	token_remove_if(t_token **token, t_token *target)
{
	t_token	*cur;
	t_token	*remove;

	cur = *token;
	if (target == NULL || cur == NULL)
		return ;
	if (cur == target)
	{
		remove = cur;
		*token = cur->next;
		ft_free_token(remove);
		return ;
	}
	while (cur != NULL && cur->next != NULL)
	{
		if (cur->next == target)
		{
			remove = cur->next;
			cur->next = cur->next->next;
			ft_free_token(remove);
			break ;
		}
		cur = cur->next;
	}
}
