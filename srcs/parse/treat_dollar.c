/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:53:08 by wbae              #+#    #+#             */
/*   Updated: 2023/05/15 16:41:55 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structure.h"

static char	*join_split(char **split)
{
	char	*ret;

	if (split[0][0] == '\0')
		ret = ft_strdup(split[1]);
	else
		ret = ft_strjoin(split[0], split[1]);
	if (split[2][0] != '\0')
		ft_strapp_back(&ret, split[2]);
	return (ret);
}

static char	*translate_dollar(char **str)
{
	t_env_node	*cur;

	if (*str[0] == '?' || *str[0] == '$')
	{
		free(*str);
		*str = ft_itoa(g_env.status);
		return (*str);
	}
	cur = g_env.head;
	while (cur)
	{
		if (!ft_strncmp(*str, cur->key, ft_strlen(*str) + 1))
		{
			if (cur->is_value == 0)
				break ;
			free(*str);
			*str = ft_strdup(cur->value);
			return (*str);
		}
		cur = cur->next;
	}
	free(*str);
	*str = ft_strdup("");
	return (*str);
}

static char	**split_dollar(char *str)
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
		split[1] = ft_strdup(&str[j]);
		split[2] = ft_substr(str, i + 2, ft_strlen(str) - i);
		split[3] = 0;
		return (split);
	}
	while (str[j] && str[j] != '$' && (ft_isalnum(str[j]) || str[j] == '_'))
		j++;
	split[1] = ft_substr(str, i + 1, j - i - 1);
	split[2] = ft_substr(str, j, ft_strlen(str) - j);
	split[3] = 0;
	return (split);
}

void	treat_dollar(t_token *token)
{
	char	**split;
	int		break_loop;

	while (token)
	{
		break_loop = FALSE;
		while (token->type == T_CHUNK && ft_strchr(token->str, '$'))
		{
			split = split_dollar(token->str);
			if ((*(ft_strchr(token->str, '$') + 1) != '\0'))
				split[1] = translate_dollar(&split[1]);
			else
			{
				split[1] = ft_strdup("$");
				break_loop = TRUE;
			}
			free(token->str);
			token->str = join_split(split);
			ft_free_strings(&split);
			if (break_loop == TRUE)
				break ;
		}
		token = token->next;
	}
}