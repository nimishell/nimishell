/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:52:18 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/21 21:01:17 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strapp_front(const char *src, char **dst)
{
	char	*result;

	result = ft_strjoin(src, *dst);
	if (result == NULL)
		return (0);
	free(*dst);
	*dst = result;
	return (1);
}

int	ft_strapp_back(char **dst, const char *src)
{
	char	*result;

	result = ft_strjoin(*dst, src);
	if (result == NULL)
		return (0);
	free(*dst);
	*dst = result;
	return (1);
}
