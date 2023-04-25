/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:06:00 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/26 02:18:03 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "error.h"
#include "structure.h"

int	ft_env(char **argv)
{
	t_env	*cur;

	if (argv[1] != NULL)
	{
		exit_with_message("env", NULL, "too many arguments", 1);
		return (0);
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
	return (1);
}

void	remove_node(t_env **remove)
{
	free((*remove)->key);
	if ((*remove)->value != NULL)
		free((*remove)->value);
	free(*remove);
}

static int	remove_head(t_env *remove)
{
	g_env = remove->next;
	remove_node(&remove);
	return (1);
}

int	ft_unset(char **argv)
{
	int		index;
	t_env	*cur;
	t_env	*tmp;

	index = 1;
	while (argv[index] != NULL)
	{
		cur = g_env;
		if (ft_strncmp(cur->key, argv[index], ft_strlen(argv[index]) + 1) == 0)
			return (remove_head(cur));
		while (cur != NULL && cur->next != NULL)
		{
			if (ft_strncmp(cur->next->key, argv[index], \
				ft_strlen(argv[index]) + 1) == 0)
				break ;
			cur = cur->next;
		}
		if (cur->next != NULL)
		{
			tmp = cur->next->next;
			remove_node(&cur->next);
			cur->next = tmp;
		}
	}
	return (1);
}
