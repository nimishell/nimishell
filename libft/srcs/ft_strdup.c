/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 15:09:28 by wbae              #+#    #+#             */
/*   Updated: 2023/04/06 17:25:01 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t		idx;
	size_t		size;
	char		*arr;

	size = 0;
	while (src[size])
		size++;
	arr = malloc(sizeof(char) * (size + 1));
	if (!arr)
		return (0);
	idx = -1;
	while (++idx < size)
		arr[idx] = src[idx];
	arr[idx] = '\0';
	return (arr);
}
