/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:56:30 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/15 08:23:03 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_token.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	ft_issep(char c, char const *sep)
{
	while (*sep)
	{
		if (c == *sep)
			return (1);
		sep++;
	}
	return (0);
}

void	token_add_back(t_token **lst, t_token *new)
{
	t_token	*cur;

	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	cur = *lst;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = new;
}

int	split_squote(t_token **token, char **read_line, t_token *new_token)
{
	char *const	line_start = *read_line;
	int			line_length;
	int			count_squote;

	line_length = 0;
	count_squote = 1;
	(*read_line)++;
	while (**read_line && **read_line != '\'')
	{
		line_length++;
		(*read_line)++;
	}
	if (**read_line == '\'')
		count_squote++;
	if (count_squote != 2)
		return (FAIL);
	new_token->str = ft_substr(line_start, 1, line_length);
	if (new_token->str == NULL)
		return (FAIL);
	new_token->type = T_CHUNK;
	token_add_back(token, new_token);
	if (**read_line != '\0')
		(*read_line)++;
	return (SUCCESS);
}

int	split_dquote(t_token **token, char **read_line, t_token *new_token)
{
	char *const	line_start = *read_line;
	int			line_length;
	int			count_dquote;

	line_length = 0;
	count_dquote = 1;
	(*read_line)++;
	while (**read_line && **read_line != '\"')
	{
		line_length++;
		(*read_line)++;
	}
	if (**read_line == '\"')
		count_dquote++;
	if (count_dquote != 2)
		return (FAIL);
	new_token->str = ft_substr(line_start, 1, line_length);
	if (new_token->str == NULL)
		return (FAIL);
	new_token->type = T_ECHUNK;
	token_add_back(token, new_token);
	if (**read_line != '\0')
		(*read_line)++;
	return (SUCCESS);
}

int	split_pipe(t_token **token, char **read_line, t_token *new_token)
{
	char *const	line_start = *read_line;
	int			line_length;

	line_length = 0;
	while (**read_line == '|')
	{
		line_length++;
		(*read_line)++;
	}
	new_token->str = ft_substr(line_start, 0, line_length);
	if (new_token->str == NULL)
		return (FAIL);
	new_token->type = T_PIPE;
	token_add_back(token, new_token);
	return (SUCCESS);
}

int	split_redir(t_token **token, char **read_line, \
		t_token *new_token, char redir_char)
{
	char *const	line_start = *read_line;
	int			line_length;

	line_length = 0;
	while (**read_line == redir_char)
	{
		line_length++;
		(*read_line)++;
	}
	new_token->str = ft_substr(line_start, 0, line_length);
	if (new_token->str == NULL)
		return (FAIL);
	new_token->type = T_REDIR;
	token_add_back(token, new_token);
	return (SUCCESS);
}

int	split_space(t_token **token, char **read_line, t_token *new_token)
{
	char *const	line_start = *read_line;
	int			line_length;

	line_length = 0;
	while (**read_line == ' ' || **read_line == '\t' || **read_line == '\n')
	{
		line_length++;
		(*read_line)++;
	}
	new_token->str = ft_substr(line_start, 0, line_length);
	if (new_token->str == NULL)
		return (FAIL);
	new_token->type = T_SPACE;
	token_add_back(token, new_token);
	return (SUCCESS);
}

int	split_str(t_token **token, char **read_line, t_token *new_token)
{
	char *const	line_start = *read_line;
	int			line_length;

	line_length = 0;
	while (**read_line && !ft_issep(**read_line, "\'\"|<> "))
	{
		line_length++;
		(*read_line)++;
	}
	new_token->str = ft_substr(line_start, 0, line_length);
	if (new_token->str == NULL)
		return (FAIL);
	new_token->type = T_ECHUNK;
	token_add_back(token, new_token);
	return (SUCCESS);
}

int	ft_split_token(t_token **token_head, char *read_line)
{
	t_token	*new_token;
	int		result;

	while (*read_line)
	{
		new_token = ft_calloc(1, sizeof(t_token));
		if (new_token == NULL)
			return (FAIL);
		if (*read_line == '\'')
			result = split_squote(token_head, &read_line, new_token);
		else if (*read_line == '\"')
			result = split_dquote(token_head, &read_line, new_token);
		else if (*read_line == '|')
			result = split_pipe(token_head, &read_line, new_token);
		else if (*read_line == '<' || *read_line == '>')
			result = split_redir(token_head, &read_line, new_token, *read_line);
		else if (*read_line == ' ' || *read_line == '\t' || *read_line == '\n')
			result = split_space(token_head, &read_line, new_token);
		else
			result = split_str(token_head, &read_line, new_token);
		if (result == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}

void	token_clear(t_token **token)
{
	t_token	*remove_token;

	if (*token == NULL)
		return ;
	while (*token != NULL)
	{
		remove_token = *token;
		*token = (*token)->next;
		free(remove_token->str);
		free(remove_token);
	}
}

void	print_tokens(t_token *token)
{
	t_token	*cur;

	cur = token;
	while (cur != NULL)
	{
		printf("token : {%s} (%d)\n", cur->str, cur->type);
		cur = cur->next;
	}
}

int	main(int ac, char **av)
{
	t_token	*token;
	char	*read_line;

	if (ac != 2)
		return (1);
	read_line = ft_strtrim(av[1], " ");
	if (read_line == NULL)
		return (1);
	printf("read_line : {%s}\n\n", read_line);
	if (ft_split_token(&token, read_line) == FAIL)
	{
		token_clear(&token);
		return (1);
	}
	print_tokens(token);
	return (0);
}
