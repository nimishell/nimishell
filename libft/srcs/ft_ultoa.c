/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 15:39:00 by wbae              #+#    #+#             */
/*   Updated: 2023/04/20 21:03:54 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(unsigned long n)
{
	int	i;

	i = 0;
	while (n / 10 != 0)
	{
		n /= 10;
		i++;
	}
	return (i + 1);
}

char	*ft_ultoa(unsigned long n)
{
	char	*ret;
	int		n_len;

	n_len = ft_nbrlen(n);
	ret = malloc(sizeof(char) * (n_len + 1));
	if (!ret)
		return (0);
	ret[n_len] = '\0';
	n_len--;
	while (n / 10 != 0)
	{
		ret[n_len] = (n % 10) + '0';
		n /= 10;
		n_len--;
	}
	ret[n_len] = '0';
	return (ret);
}
