/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:36:50 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/05 10:57:16 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_free_str(char **str)
{
	if (*str != NULL)
	{
		free(*str);
		*str = NULL;
	}
}

void	ft_free_strings(char ***strings)
{
	int	index;

	if (*strings != NULL)
	{
		index = 0;
		while ((*strings)[index] != NULL)
		{
			ft_free_str(&(*strings)[index]);
			index++;
		}
		free(*strings);
		*strings = NULL;
	}
}

void	ft_free_void(void ***ptr, int index_max)
{
	if (*ptr != NULL)
	{
		while (--index_max >= 0)
		{
			if ((*ptr)[index_max] != NULL)
				free((*ptr)[index_max]);
			(*ptr)[index_max] = NULL;
		}
		free(*ptr);
		*ptr = NULL;
	}
}
