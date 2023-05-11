/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 19:49:29 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/12 04:03:29 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structure.h"

extern t_env	*g_env;

void	remove_node(t_env **remove)
{
	free((*remove)->key);
	if ((*remove)->value != NULL)
		free((*remove)->value);
	free(*remove);
	*remove = NULL;
}

static void	remove_head(t_env **cur)
{
	t_env	*remove;

	remove = *cur;
	g_env = (*cur)->next;
	*cur = (*cur)->next;
	remove_node(&remove);
}

int	ft_unset(char **argv)
{
	int		index;
	t_env	*cur;
	t_env	*tmp;

	index = 1;
	while (argv[index] != NULL)
	{
		cur = g_env;
		if (ft_strncmp(cur->key, argv[index], ft_strlen(argv[index]) + 1) == 0)
			remove_head(&cur);
		while (cur != NULL && cur->next != NULL)
		{
			if (ft_strncmp(cur->next->key, argv[index], \
					ft_strlen(argv[index]) + 1) == 0)
			{
				tmp = cur->next->next;
				remove_node(&cur->next);
				cur->next = tmp;
				break ;
			}
			cur = cur->next;
		}
		index++;
	}
	return (0);
}
