/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:56:15 by wbae              #+#    #+#             */
/*   Updated: 2023/05/12 21:28:37 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	make_split_to_token(t_token *lst, char **arr)
{
	t_token	*tmp;

	tmp = lst->next;
	lst->next = NULL;
	free(lst->str);
	lst->str = ft_strdup(arr[0]);
	token_add_back(&lst, new_token(arr[1], T_ARGV));
	lst = token_add_back(&lst, new_token(arr[2], T_CHUNK));
	ft_free_char_arr(arr);
	lst->next = tmp;
}

static int	where_dollar_in_quote(char *str, int *dollar_idx, int *next_idx)
{
	*dollar_idx = ft_strcspn(str, "$");
	if (!str[*dollar_idx])
		return (0);
	*next_idx = *dollar_idx + 1;
	if (str[*next_idx] == '?' || str[*next_idx] == '$' || ft_isdigit(str[*next_idx])
		|| (!ft_isalpha(str[*next_idx]) && str[*next_idx] != '_'))
	{
		*next_idx += 1;
		return (1);
	}
	if (str[*next_idx] == '\0'
		|| (!ft_isalnum(str[*next_idx]) && str[*next_idx] != '_'))
		return (0);
	while (str[*next_idx]
		&& (ft_isalnum(str[*next_idx]) || str[*next_idx] == '_'))
		*next_idx += 1;
	return (1);
}

static char	*translate_dollar_in_quote(char *str)
{
	char	*arr[3];
	char	*tmp;
	int		dollar_idx;
	int		next_idx;

	while (where_dollar_in_quote(str, &dollar_idx, &next_idx))
	{
		arr[0] = ft_substr(str, 0, dollar_idx);
		if (str[dollar_idx + 1] == '?' || str[dollar_idx + 1] == '$')
			arr[1] = ft_itoa(g_env->status);
		else
		{
			tmp = ft_substr(str, dollar_idx + 1, next_idx - dollar_idx - 1);
			arr[1] = ft_strdup(get_value(tmp));
			if (!arr[1])
				arr[1] = ft_strdup("");
			free(tmp);
		}
		arr[2] = ft_substr(str, next_idx, ft_strlen(str) - next_idx);
		free(str);
		str = ft_multi_strjoin(arr[0], arr[1], arr[2]);
		ms_free(arr[0], arr[1], arr[2], NULL);
	}
	return (str);
}

static int	where_quote(char *str, int *start, int *end)
{
	*start = 0;
	while (str[*start] && str[*start] != '\'' && str[*start] != '\"')
		*start += 1;
	if (!str[*start])
		return (FAIL);
	*end = *start + 1;
	while (str[*end] && str[*end] != str[*start])
		*end += 1;
	if (!str[*end])
		return (FAIL);
	return (SUCCESS);
}

char	**split_quote(char *str)
{
	char	**ret;
	int		start;
	int		end;

	if (!where_quote(str, &start, &end))
		return (NULL);
	ret = malloc(sizeof(char *) * 4);
	if (!ret)
		return (NULL);
	if (start > 0 && str[start - 1] == '$')
		ret[0] = ft_substr(str, 0, start - 1);
	else
		ret[0] = ft_substr(str, 0, start);
	ret[1] = ft_substr(str, start + 1, end - start - 1);
	if (str[start] == '\"')
		ret[1] = translate_dollar_in_quote(ret[1]);
	ret[2] = ft_substr(str, end + 1, ft_strlen(str) - end - 1);
	ret[3] = 0;
	return (ret);
}
