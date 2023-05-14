/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 19:49:29 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/14 16:07:40 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_list.h"

int	ft_unset(char **argv)
{
	int			index;
	t_env_node	*remove;

	index = 1;
	while (argv[index] != NULL)
	{
		remove = g_env.head;
		while (remove != NULL)
		{
			if (ft_strncmp(remove->key, argv[index], \
					ft_strlen(argv[index]) + 1) == 0)
			{
				env_remove_if(remove);
				break ;
			}
			remove = remove->next;
		}
		index++;
	}
	return (0);
}
