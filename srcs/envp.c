/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:33:04 by wbae              #+#    #+#             */
/*   Updated: 2023/05/12 05:42:27 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static char	*copy_key(char *envp)
{
	char	*key;
	int		i;

	i = 0;
	while (envp[i] && envp[i] != '=')
		i++;
	key = ft_substr(envp, 0, i);
	return (key);
}

static char	*copy_value(char *envp)
{
	char	*val;
	int		i;

	i = 0;
	while (envp[i] && envp[i] != '=')
		i++;
	if (envp[i] == '\0')
		return (NULL);
	val = ft_strdup(&envp[i + 1]);
	return (val);
}

static void	making_env(char *envp)
{
	t_env	*tmp;

	tmp = g_env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = malloc(sizeof(t_env));
	tmp = tmp->next;
	tmp->key = copy_key(envp);
	if (ft_strncmp(g_env->key, "OLDPWD", 7) == 0)
		tmp->value = NULL;
	else
		tmp->value = copy_value(envp);
	if (tmp->value == NULL)
		tmp->is_value = 0;
	else
		tmp->is_value = 1;
	tmp->next = NULL;
}

void	copy_env(char *envp[])
{
	int	i;

	if (!g_env)
	{
		g_env = malloc(sizeof(t_env));
		g_env->key = copy_key(envp[0]);
		if (ft_strncmp(g_env->key, "OLDPWD", 7) == 0)
			g_env->value = NULL;
		else
			g_env->value = copy_value(envp[0]);
		if (g_env->value == NULL)
			g_env->is_value = 0;
		else
			g_env->is_value = 1;
		g_env->next = NULL;
	}
	i = 0;
	while (envp[++i])
		making_env(envp[i]);
}

char	*get_value(char *key)
{
	t_env	*cur;

	cur = g_env;
	while (cur != NULL)
	{
		if (!ft_strncmp(cur->key, key, ft_strlen(key) + 1))
			return (cur->value);
		cur = cur->next;
	}
	return (NULL);
}
