/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:23:57 by wbae              #+#    #+#             */
/*   Updated: 2023/05/10 20:50:48 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

static int	is_valid_metacha(char c)
{
	return (c == ' ' || c == '|' || c == '<' || c == '>' || c == '\0');
}

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
	{
		printf("!!!\n");
		ft_putstr_fd("minishell: quotes error\n", STDERR_FILENO);
	}
	str = ft_substr(s, i + 1, lim_len - 1);
	if (str[0])
		token_add_back(&token, new_token(str, T_ARGV));
	free(str);
	return (i + lim_len + 1);

}

static int	check_heredoc_arg( t_token *token, char *s, int i)
{
	int		lim_len;
	char	*str;

	while (s[i] && !is_valid_metacha(s[i]))
	{
		if (s[i] == '\'' || s[i] == '\"')
			i = check_quote_in_limiter(token, s, i);
		else
		{
			lim_len = 1;
			while (s[i + lim_len] && !is_valid_metacha(s[i + lim_len]) \
				&& s[i + lim_len] != '\'' && s[i + lim_len] != '\"')
				lim_len++;
			str = ft_substr(s, i, lim_len);
			token_add_back(&token, new_token(str, T_ARGV));
			i += lim_len;
			free(str);
		}
	}
	return (i);
}

void	treat_heredoc(t_token *token, char *s)
{
	int		i;
	char	*str;

	i = where_limiter(s);
	if (!s[i])
	{
		free(s);
		return ;
	}
	i += 2;
	while (s[i] == ' ')
		i++;
	free(token->str);
	token->str = ft_substr(s, 0, i);
	i = check_heredoc_arg(token, s, i);
	str = ft_substr(s, i, ft_strlen(s) - i);
	token_add_back(&token, new_token(str, T_CHUNK));
	ft_free_str(&str);
	ft_free_str(&s);
}
