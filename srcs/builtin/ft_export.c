/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 01:54:29 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/15 16:30:35 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_list.h"
#include "envp.h"
#include "error.h"

static int	show_export(void)
{
	t_env_node	*cur;

	cur = g_env.head;
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

void	change_value(t_env_node *node, char *new_value)
{
	if (new_value == NULL)
		return ;
	if (node->value != NULL)
	{
		ft_free_str(&node->value);
		node->is_value = FALSE;
		g_env.value_count--;
	}
	node->value = ft_strdup(new_value);
	node->is_value = TRUE;
	g_env.value_count++;
}

int	export_variable(char **key, char *value)
{
	t_env_node	*cur;

	cur = g_env.head;
	while (cur)
	{
		if (ft_strncmp(cur->key, *key, ft_strlen(*key) + 1) == 0)
			break ;
		cur = cur->next;
	}
	if (cur != NULL)
		change_value(cur, value);
	else
		if (add_new_env(*key, value) == 0)
			return (0);
	return (1);
}

int	check_valid_identifier(char *argv)
{
	int	index;

	index = 0;
	while (argv[index] != '\0' && argv[index] != '=')
	{
		if (ft_isalnum(argv[index]) == FALSE && argv[index] != '_')
		{
			ft_error_message("export", argv, "not a valid identifier");
			return (0);
		}
		index++;
	}
	return (1);
}

int	ft_export(char **argv)
{
	int		index;
	char	*key;
	char	*value;

	if (argv[1] == NULL)
		return (show_export());
	index = 1;
	while (argv[index])
	{
		if (!check_valid_identifier(argv[index]))
			return (1);
		key = split_key(argv[index]);
		value = split_value(argv[index]);
		export_variable(&key, value);
		ft_free_str(&key);
		if (value != NULL)
			ft_free_str(&value);
		index++;
	}
	return (0);
}
