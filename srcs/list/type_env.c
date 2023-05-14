/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 22:21:29 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/14 21:29:01 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_list.h"
#include <stdio.h>

t_env_node	*env_new(void)
{
	t_env_node	*new;

	new = ft_calloc(1, sizeof(t_env_node));
	if (new == NULL)
		return (NULL);
	return (new);
}

void	env_add_back(t_env_node *new)
{
	if (new == NULL)
		return ;
	if (g_env.head == NULL)
		g_env.head = new;
	else
		g_env.tail->next = new;
	g_env.tail = new;
	g_env.key_count++;
	if (new->value != NULL)
		g_env.value_count++;
}

void	ft_free_env(t_env_node *node)
{
	free(node->key);
	if (node->value != NULL)
	{
		free(node->value);
		g_env.value_count--;
	}
	free(node);
	g_env.key_count--;
}

t_env_node	*env_last(void)
{
	t_env_node	*cur;

	cur = g_env.head;
	if (cur == NULL)
		return (NULL);
	while (cur->next != NULL)
		cur = cur->next;
	return (cur);
}

void	env_remove_if(t_env_node *target)
{
	t_env_node	*cur;
	t_env_node	*remove;

	cur = g_env.head;
	if (target == NULL || cur == NULL)
		return ;
	if (cur == target)
	{
		remove = cur;
		g_env.head = cur->next;
		ft_free_env(remove);
		return ;
	}
	while (cur != NULL && cur->next != NULL)
	{
		if (cur->next == target)
		{
			remove = cur->next;
			cur->next = cur->next->next;
			ft_free_env(remove);
			break ;
		}
		cur = cur->next;
	}
	g_env.tail = env_last();
}
