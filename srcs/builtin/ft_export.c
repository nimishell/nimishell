/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 01:54:29 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/13 20:42:53 by yeongo           ###   ########.fr       */
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
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		cur = cur->next;
	}
	return (0);
}

static void	change_value(t_env *cur, char *new_value)
{
	if (cur->value != NULL)
		free(cur->value);
	else
		cur->is_value = 1;
	cur->value = ft_strdup(new_value);
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
	cur->next->key = ft_strdup(key);
	cur->next->value = ft_strdup(value);
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
		if (add_env_value(*key, value) == 0)
			return (0);
	}
	return (1);
}

int	ft_export(char **argv)
{
	int		index;
	char	*key;
	int		key_len;
	char	*value;

	if (argv[1] == NULL)
		return (show_export());
	index = 1;
	while (argv[index])
	{
		key_len = 0;
		while (argv[index][key_len] != '\0' && argv[index][key_len] != '=')
		{
			if (ft_isalnum(argv[index][key_len]) == FALSE \
				&& argv[index][key_len] != '_')
			{
				ft_error_message(argv[0], argv[index], \
					"not a valid identifier");
				return (1);
			}
			key_len++;
		}
		key = ft_substr(argv[index], 0, key_len);
		value = NULL;
		if (argv[index][key_len])
			value = ft_substr(argv[index] + key_len, 1, \
						ft_strlen(argv[index] + key_len) - 1);
		export_variable(&key, value);
		ms_free(key, value, NULL, NULL);
		index++;
	}
	return (0);
}
