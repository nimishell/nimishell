/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 01:54:29 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/27 20:51:23 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

static int	show_export(void)
{
	t_env	*cur;

	cur = g_env;
	while (cur != NULL)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(cur->key, STDOUT_FILENO);
		if (cur->is_value == 1)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(cur->value, STDOUT_FILENO);
			ft_putstr_fd("\"\n", STDOUT_FILENO);
		}
		cur = cur->next;
	}
	return (0);
}

static void	change_value(t_env *cur, char *new_value)
{
	if (cur->value != NULL)
		free(cur->value);
	cur->value = new_value;
}

static int	add_env_value(char *key, char *value)
{
	t_env	*cur;

	cur = g_env;
	while (cur != NULL && cur->next != NULL)
		cur = cur->next;
	cur->next = ft_calloc(1, sizeof(t_env));
	if (cur->next == NULL)
		return (0);
	cur->next->key = key;
	cur->next->value = value;
	if (cur->next->value != NULL)
		cur->next->is_value = 1;
	return (1);
}

int	export_variable(char **key, char *value)
{
	t_env	*cur;

	cur = g_env;
	while (cur)
	{
		if (ft_strncmp(cur->key, *key, ft_strlen(*key) + 1) == 0)
			break ;
		cur = cur->next;
	}
	if (cur != NULL)
	{
		ft_free_str(key);
		if (value != NULL)
			change_value(cur, value);
	}
	else
	{
		if (add_env_value(*key, value))
			return (0);
	}
	return (1);
}

int	ft_export(char **argv)
{
	int		index_argv;
	char	*key;
	int		key_len;
	char	*value;

	if (argv[1] == NULL)
		return (show_export());
	index_argv = 1;
	while (argv[index_argv])
	{
		key_len = 0;
		while (argv[index_argv][key_len] != '\0' \
			&& argv[index_argv][key_len] != '=')
			key_len++;
		key = ft_substr(argv[index_argv], 0, key_len);
		if (argv[index_argv][key_len])
			value = ft_substr(argv[index_argv] + key_len, 1, \
					ft_strlen(argv[index_argv] + key_len) - 1);
		else
			value = NULL;
		export_variable(&key, value);
		index_argv++;
	}
	return (0);
}
