/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 19:49:29 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/04 16:04:25 by wbae             ###   ########.fr       */
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
}

static int	remove_head(t_env *remove)
{
	g_env = remove->next;
	remove_node(&remove);
	return (1);
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
			return (remove_head(cur));
		while (cur != NULL && cur->next != NULL)
		{
			if (ft_strncmp(cur->next->key, argv[index], \
				ft_strlen(argv[index]) + 1) == 0)
				break ;
			cur = cur->next;
		}
		if (cur->next != NULL)
		{
			tmp = cur->next->next;
			remove_node(&cur->next);
			cur->next = tmp;
		}
	}
	return (0);
}
