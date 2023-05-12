/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:53:08 by wbae              #+#    #+#             */
/*   Updated: 2023/05/12 19:49:19 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

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

static char	*translate_dollar(t_env *head, char **str)
{
	char	*tmp;

	if (*str[0] == '?' || *str[0] == '$')
	{
		free(*str);
		tmp = ft_itoa(head->status);
		*str = ft_strdup(tmp);
		free(tmp);
		return (*str);
	}
	while (head)
	{
		if (!ft_strncmp(*str, head->key, ft_strlen(*str) + 1))
		{
			free(*str);
			*str = ft_strdup(head->value);
			return (*str);
		}
		head = head->next;
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
	t_env	*head;

	while (token)
	{
		while (token->type == T_CHUNK && ft_strchr(token->str, '$'))
		{
			head = g_env;
			split = split_dollar(token->str);
			if ((*(ft_strchr(token->str, '$') + 1) != '\0'))
				split[1] = translate_dollar(head, &split[1]);
			else
			{
				split[1] = ft_strdup("$");
				free(token->str);
				token->str = join_split(split);
				ft_free_char_arr(split);
				break ;
			}
			free(token->str);
			token->str = join_split(split);
			ft_free_char_arr(split);
		}
		token = token->next;
	}
}
