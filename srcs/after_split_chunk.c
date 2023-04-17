/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   after_split_chunk.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:00:31 by wbae              #+#    #+#             */
/*   Updated: 2023/04/17 16:51:53 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	remove_empty_token(t_token **lst)
{
	t_token	*rm;
	t_token	*cur;

	cur = *lst;
	while (cur && cur->next)
	{
		if (cur->next->str[0] == '\0')
		{
			rm = cur->next;
			cur->next = cur->next->next;
			free(rm->str);
			free(rm);
		}
		cur = cur->next;
	}
	cur = *lst;
	if (cur && cur->str[0] == '\0')
	{
		*lst = cur->next;
		free(cur->str);
		free(cur);
	}
}

void	treat_dollar(t_token *token)
{
	char	**split;
	t_env	*head;

	while (token)
	{
		while (token->type == T_ECHUNK && ft_strchr(token->str, '$'))
		{
			split = split_dollar(token->str);
			head = g_env;
			split[1] = translate_dollar(head, &split[1]);
			free(token->str);
			token->str = ft_strjoin(split[0], split[1]);
			token->str = ft_strjoin(token->str, split[2]);
			ft_free(split[0], split[1], split[2], NULL);
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
	while (str[j] && str[j] != '$')
		j++;
	split[0] = ft_substr(str, 0, i);
	split[1] = ft_substr(str, i + 1, j - i - 1);
	split[2] = ft_substr(str, j, ft_strlen(str) - j);
	split[3] = 0;
	return (split);
}

char	*translate_dollar(t_env *head, char **str)
{
	while (head)
	{
		if (!ft_strncmp(*str, head->key, ft_strlen(*str)))
		{
			printf("trans : %s\n", head->value);
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
