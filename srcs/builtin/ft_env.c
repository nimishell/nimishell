/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:06:00 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/30 20:37:00 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structure.h"
#include "error.h"

extern t_env	*g_env;

int	ft_env(char **argv)
{
	t_env	*cur;

	if (argv[1] != NULL)
	{
		ft_error_message("env", NULL, "too many arguments");
		return (1);
	}
	cur = g_env;
	while (cur)
	{
		if (cur->is_value == 1)
		{
			ft_putstr_fd(cur->key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putstr_fd(cur->value, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		cur = cur->next;
	}
	return (0);
}
