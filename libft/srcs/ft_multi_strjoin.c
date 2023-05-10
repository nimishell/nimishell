/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_strjoin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:18:20 by wbae              #+#    #+#             */
/*   Updated: 2023/05/10 16:42:06 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_multi_strjoin(char *str1, char *str2, char *str3)
{
	char	*str;
	int		size;
	int		i;

	size = ft_strlen(str1) + ft_strlen(str2) + ft_strlen(str3);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	i = 0;
	if (str1)
		while (*str1)
			str[i++] = *str1++;
	if (str2)
		while (*str2)
			str[i++] = *str2++;
	if (str3)
		while (*str3)
			str[i++] = *str3++;
	str[size] = '\0';
	return (str);
}
