/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   after_split_chunk.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:00:31 by wbae              #+#    #+#             */
/*   Updated: 2023/04/16 21:56:24 by wbae             ###   ########.fr       */
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


void	translate_dollar(t_token *token, t_env *g_env)
{
	t_env	*head;
	int		i;
	char	*target;
	char	*prev;

	head = g_env;
	while (token)
	{
		i = 0;
		while (token->type == T_ECHUNK && token->str[i])
		{
			if (token->str[i] == '$')
			{
				target = ft_substr(token->str, i + 1, ft_strlen(token->str) - i);
				printf("target : %s\n", target);
				prev = ft_substr(token->str, 0, i);
				g_env = head;
				while (g_env)
				{
					if (!ft_strncmp(target, g_env->key, ft_strlen(target)))
					{
						printf("trans : %s\n", g_env->value);
						free(token->str);
						if (!prev)
							token->str = ft_strdup(g_env->value);
						else
							token->str = ft_strjoin(prev, g_env->value);
					}
					else
					{
						free(token->str);
						token->str = ft_strdup(prev);
					}
					g_env = g_env->next;
				}
			}
			i++;
		}
		token = token->next;
	}
}
