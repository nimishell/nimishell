/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:53:48 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/17 15:45:43 by wbae             ###   ########.fr       */
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
