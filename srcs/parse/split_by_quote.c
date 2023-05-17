/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:56:15 by wbae              #+#    #+#             */
/*   Updated: 2023/05/15 16:54:12 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_list.h"
#include "envp.h"
#include "error.h"
#include "ft_free.h"
#include "parsing.h"

void	make_split_to_token(t_token *token, char **arr)
{
	t_token	*save_token;

	save_token = token->next;
	token->next = NULL;
	free(token->str);
	token->str = ft_strdup(arr[0]);
	token_add_back(&token, token_new(arr[1], T_ARGV));
	token_add_back(&token, token_new(arr[2], T_CHUNK));
	token = token_last(token);
	token->next = save_token;
}

static char	*translate_dollar_in_quote(char *str)
{
	if (!ft_strchr(str, '$'))
		return (str);
	translate_dollar(&str);
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

static char	**split_quote(char *str)
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

int	split_by_quote(t_token *token)
{
	char	**split;

	while (token)
	{
		while (token->type == T_CHUNK && \
			(ft_strchr(token->str, '\'') || ft_strchr(token->str, '\"')))
		{
			split = split_quote(token->str);
			if (split)
			{
				make_split_to_token(token, split);
				ft_free_strings(&split);
			}
			else
			{
				ft_syntax_error(ft_strdup("\'"));
				return (FAIL);
			}
		}
		token = token->next;
	}
	return (SUCCESS);
}
