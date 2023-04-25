/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 01:54:29 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/26 02:47:31 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (1);
}

static void	change_value(t_env *cur, char *new_value)
{
	free(cur->value);
	cur->value = new_value;
}

int	export_variable(char *key, char *value)
{
	t_env	*cur;

	cur = g_env;
	while (cur)
	{
		if (ft_strncmp(cur->key, key, ft_strlen(key) + 1) == 0)
			break ;
		cur = cur->next;
	}
	if (cur != NULL && value != NULL)
		change_value(cur, value);
	else
		return (0);
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
		if (export_variable(key, value) == 0)
			making_env(argv[index_argv]);
		index_argv++;
	}
	return (1);
}
