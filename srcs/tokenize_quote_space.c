/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_quote_space.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:33:28 by wbae              #+#    #+#             */
/*   Updated: 2023/04/14 18:53:52 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	check_quote(char *line)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (line[++i])
	{
		if (line[i] == '\'' && flag == 0)
			flag = 1;
		else if (line[i] == '\'' && flag == 1)
			flag = 0;
		else if (line[i] == '\"' && flag == 0)
			flag = 2;
		else if (line[i] == '\"' && flag == 2)
			flag = 0;
	}
	if (flag != 0)
		return (0);
	return (1);
}

char	**seperate_array_quote(char *str, int start, int end)
{
	char	**ret;

	ret = (char **)malloc(sizeof(char *) * 4);
	if (!ret)
		return (NULL);
	ret[0] = ft_substr(str, 0, start);
	if (!ret[0])
		return (ft_free_char_arr((void *)ret));
	ret[1] = ft_substr(str, start + 1, end - start - 1);
	if (!ret[1])
		return (ft_free_char_arr((void *)ret));
	ret[2] = ft_substr(str, end + 1, ft_strlen(str));
	if (!ret[2])
		return (ft_free_char_arr((void *)ret));
	ret[3] = NULL;
	return (ret);
}

char	**split_quote(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] && str[i] != '\'' && str[i] != '\"')
		i++;
	if (!str[i])
		return (NULL);
	j = i;
	if (str[i] == '\'')
	{
		while (str[++j] && str[j] != '\'')
			;
		if (str[j] == '\'')
			return (seperate_array_quote(str, i, j));
	}
	if (str[i] == '\"')
	{
		while (str[++j] && str[j] != '\"')
			;
		if (str[j] == '\"')
			return (seperate_array_quote(str, i, j));
	}
	return (NULL);
}

void	tokenize_quote(t_token *token)
{
	char	**split;

	while (token)
	{
		if (token->type == T_CHUNK)
		{
			split = split_quote(token->str);
			if (split)
			{
				add_token(&token, 1, T_CHUNK, split[2]);
				add_token(&token, 1, T_ARGV, split[1]);
				free(token->str);
				token->str = ft_strdup(split[0]);
				ft_free_char_arr((void *)split);
				token = token->next;
			}
		}
		if (token)
			token = token->next;
	}
}

void	tokenize_space(t_token *token)
{
	int		i;
	char	*prev;
	char	*next;

	while (token)
	{
		if (token->type == T_CHUNK && ft_isspace_str(token->str))
		{
			i = 0;
			while (token->str[i] && token->str[i] != ' ')
				i++;
			next = ft_substr(token->str, i + 1, ft_strlen(token->str) - i);
			add_token(&token, 2, T_CHUNK, next);
			add_token(&token, 1, T_SPACE, ft_strdup(" "));
			prev = ft_substr(token->str, 0, i);
			free(token->str);
			token->str = ft_strdup(prev);
			free(prev);
		}
		token = token->next;
	}
}