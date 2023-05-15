/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:33:04 by wbae              #+#    #+#             */
/*   Updated: 2023/05/15 16:35:08 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_list.h"

char	*split_key(char *envp)
{
	char	*key;
	int		index;

	index = 0;
	while (envp[index] && envp[index] != '=')
		index++;
	key = ft_substr(envp, 0, index);
	return (key);
}

char	*split_value(char *envp)
{
	char	*value;
	int		index;

	index = 0;
	while (envp[index] && envp[index] != '=')
		index++;
	if (envp[index] == '\0')
		return (NULL);
	value = ft_strdup(&envp[index + 1]);
	return (value);
}

int	add_new_env(char *key, char *value)
{
	t_env_node	*new;

	new = env_new();
	if (new == NULL)
		return (0);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	if (new->value != NULL)
		new->is_value = 1;
	env_add_back(new);
	return (1);
}

void	get_env_lst(char **envp)
{
	int			index;
	char		*key;
	char		*value;

	index = 0;
	while (envp[index])
	{
		key = split_key(envp[index]);
		value = NULL;
		if (ft_strncmp(key, "OLDPWD", 7))
			value = split_value(envp[index]);
		add_new_env(key, value);
		ft_free_str(&key);
		if (value != NULL)
			ft_free_str(&value);
		index++;
	}
}

char	*find_value(char *key)
{
	t_env_node	*cur;

	cur = g_env.head;
	while (cur != NULL)
	{
		if (!ft_strncmp(cur->key, key, ft_strlen(key) + 1))
			return (cur->value);
		cur = cur->next;
	}
	return (NULL);
}
