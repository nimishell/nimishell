/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:53:08 by wbae              #+#    #+#             */
/*   Updated: 2023/04/25 14:00:15 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

static int	env_maxlen(const char *s1, const char *s2)
{
	int	len1;
	int	len2;
	int	i;

	i = 0;
	len1 = ft_strlen(s1);
	while (s2[i] && (ft_isalnum(s2[i]) || s2[0] == '_'))
		i++;
	len2 = i;
	if (len1 >= len2)
		return (len1);
	return (len2);
}

static char	**treat_special(char **split, char *str, char c, int i)
{
	split[1] = ft_strdup(&c);
	split[2] = ft_substr(str, i + 2, ft_strlen(str) - i);
	split[3] = 0;
	return (split);
}

void	treat_dollar(t_token *token)
{
	char	**split;
	t_env	*head;

	while (token)
	{
		while (token->type == T_ECHUNK && ft_strchr(token->str, '$'))
		{
			head = g_env;
			split = split_dollar(token->str);
			if (split[1][0] == '$')
				split[1] = ft_strdup("42");
			else
				split[1] = translate_dollar(head, &split[1]);
			free(token->str);
			if (split[0][0] == '\0')
				token->str = ft_strdup(split[1]);
			else
				token->str = ft_strjoin(split[0], split[1]);
			if (split[2][0] != '\0')
				token->str = ft_strjoin(token->str, split[2]);
			ft_free_char_arr(split);
		}
		token = token->next;
	}
}

char	**split_dollar(char *str)
{
	int		i;
	int		j;
	char	**split;

	split = malloc(sizeof(char *) * 4);
	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	j = i + 1;
	split[0] = ft_substr(str, 0, i);
	if (str[j] == '$' || str[j] == '?')
	{
		split = treat_special(split, str, str[j], i);
		return (split);
	}
	while (str[j] && str[j] != '$' && (ft_isalnum(str[j]) || str[j] == '_'))
		j++;
	split[1] = ft_substr(str, i + 1, j - i - 1);
	split[2] = ft_substr(str, j, ft_strlen(str) - j);
	split[3] = 0;
	return (split);
}

char	*translate_dollar(t_env *head, char **str)
{
	int	target;

	if (*str[0] == '?')
	{
		free(*str);
		*str = ft_strdup(ft_itoa(g_env->status));
		return (*str);
	}
	while (head)
	{
		target = env_maxlen(head->key, *str);
		if (!ft_strncmp(*str, head->key, target))
		{
			free(*str);
			*str = ft_strdup(head->value);
			break ;
		}
		head = head->next;
	}
	if (!head)
	{
		free(*str);
		*str = ft_strdup("");
	}
	return (*str);
}
