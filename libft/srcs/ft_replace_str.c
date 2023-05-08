/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:30:24 by wbae              #+#    #+#             */
/*   Updated: 2023/05/08 16:42:30 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_replace_str(char **str, char *target, char *replace, int position)
{
	size_t	len_str;
	size_t	len_target;
	size_t	len_replace;
	size_t	m_size;
	char	*result;

	len_str = ft_strlen(*str);
	len_target = ft_strlen(target) + 1;
	len_replace = ft_strlen(replace);
	m_size = len_str + len_replace - len_target;
	result = ft_calloc(m_size + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_memmove(result, *str, position);
	ft_memmove(&result[position], replace, len_replace);
	ft_memmove(&result[position + len_replace], &(*str)[position + len_target], \
			len_str - position - len_target);
	ft_free_str(str);
	return (result);
}
