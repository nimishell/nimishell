/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:53:48 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/05 13:09:34 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

size_t	ft_strcspn(const char *str, const char *charset)
{
	size_t	position;

	position = 0;
	while (str[position])
	{
		if (ft_strchr(charset, str[position]) != NULL)
			break ;
		position++;
	}
	return (position);
}
