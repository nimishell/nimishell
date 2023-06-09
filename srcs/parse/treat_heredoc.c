/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:23:57 by wbae              #+#    #+#             */
/*   Updated: 2023/05/17 16:32:51 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_list.h"
#include "error.h"

static int	where_limiter(char *s)
{
	int	i;
	int	lim_len;

	i = 0;
	while (s[i] && ft_strncmp(s + i, "<<", 2))
	{
		lim_len = 1;
		if (s[i] == '\'' || s[i] == '\"')
		{
			while (s[i + lim_len] && s[i + lim_len] != s[i])
				lim_len++;
			lim_len++;
		}
		i += lim_len;
		if (i >= ft_strlen(s))
			return (-1);
	}
	return (i);
}

static int	check_quote_in_limiter(t_token *token, char *s, int i)
{
	int		lim_len;
	char	*str;

	lim_len = 1;
	while (s[i + lim_len] && s[i + lim_len] != s[i])
		lim_len++;
	if (!s[i + lim_len])
		return (0);
	str = ft_substr(s, i + 1, lim_len - 1);
	if (str[0])
		token_add_back(&token, token_new(str, T_ARGV));
	free(str);
	return (i + lim_len + 1);
}

static int	check_heredoc_arg(t_token *token, char *s, int i)
{
	int		lim;
	char	*str;

	while (s[i] && !(s[i] == ' ' || s[i] == '|' || \
		s[i] == '<' || s[i] == '>' || s[i] == '\0'))
	{
		if (s[i] == '\'' || s[i] == '\"')
			i = check_quote_in_limiter(token, s, i);
		else
		{
			lim = 1;
			while (s[i + lim] && !(s[i + lim] == ' ' || s[i + lim] == '|' || \
				s[i + lim] == '<' || s[i + lim] == '>' || s[i + lim] == '\0') \
				&& s[i + lim] != '\'' && s[i + lim] != '\"')
				lim++;
			str = ft_substr(s, i, lim);
			token_add_back(&token, token_new(str, T_ARGV));
			i += lim;
			free(str);
		}
	}
	return (i);
}

static int	check_heredoc_limiter(t_token *token, char *s)
{
	int		i;
	char	*str;

	i = where_limiter(s);
	if (i < 0 || !s[i])
	{
		ft_free_str(&s);
		return (SUCCESS);
	}
	i += 2;
	while (s[i] == ' ')
		i++;
	free(token->str);
	token->str = ft_substr(s, 0, i);
	i = check_heredoc_arg(token, s, i);
	if (!i)
	{
		ft_free_str(&s);
		return (FAIL);
	}
	str = ft_substr(s, i, ft_strlen(s) - i);
	token_add_back(&token, token_new(str, T_CHUNK));
	ft_free_str(&str);
	ft_free_str(&s);
	return (SUCCESS);
}

int	treat_heredoc(t_token *token)
{
	while (token)
	{
		if (token->type == T_CHUNK)
		{
			if (!check_heredoc_limiter(token, ft_strdup(token->str)))
			{
				ft_syntax_error(ft_strdup("\'"));
				return (FAIL);
			}
		}
		token = token->next;
	}
	return (SUCCESS);
}
