/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_parameter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:04:55 by wbae              #+#    #+#             */
/*   Updated: 2023/05/10 17:31:56 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

static void	where_param(char *str, char *param, int *start, int *end)
{
	*start = ft_strcspn(str, param);
	if (!str[*start])
		return ;
	*end = *start + ft_strlen(param);
}

static char	**split_str(char *str, char *param)
{
	char	**arr;
	int		start;
	int		end;

	start = 0;
	end = -1;
	where_param(str, param, &start, &end);
	if (start > end)
		return (NULL);
	arr = malloc(sizeof(char *) * 4);
	if (!arr)
		return (NULL);
	arr[0] = ft_substr(str, 0, start);
	arr[1] = ft_substr(str, start, end - start);
	arr[2] = ft_substr(str, end, ft_strlen(str) - end);
	arr[3] = 0;
	return (arr);
}

static void	add_arr_in_token(t_token *token, char **arr, char *param)
{
	t_token	*tmp;

	tmp = token->next;
	token->next = NULL;
	free(token->str);
	token->str = ft_strdup(arr[0]);
	if (param[0] == ' ')
		token_add_back(&token, new_token(arr[1], T_SPACE));
	else if (param[0] == '|')
		token_add_back(&token, new_token(arr[1], T_PIPE));
	else
		token_add_back(&token, new_token(arr[1], T_REDIR));
	token = token_add_back(&token, new_token(arr[2], T_CHUNK));
	ft_free_char_arr(arr);
	token->next = tmp;
}

void	split_by_parameter(t_token *token, char *param)
{
	char	**arr;

	while (token)
	{
		if (token->type == T_CHUNK)
		{
			arr = split_str(token->str, param);
			if (arr)
				add_arr_in_token(token, arr, param);
		}
		token = token->next;
	}
}
