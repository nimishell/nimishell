/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:21:38 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/24 16:01:42 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

static char	**is_cd_follow_no_dir(t_token *token)
{
	char	**result;

	result = ft_calloc(3, sizeof(char *));
	if (result == NULL)
		return (NULL);
	result[0] = ft_strdup(token->str);
	result[1] = get_value("$HOME");
	return (result);
}

static int	token_size(t_token *token)
{
	t_token	*cur;
	int		size;

	cur = token;
	size = 0;
	while (cur != NULL)
	{
		size++;
		cur = cur->next;
	}
	return (size);
}

static char	**tmp_name(t_token *token)
{
	t_token	*cur;
	int		m_size;
	char	**result;
	int		index;

	cur = token;
	m_size = token_size(cur) + 1;
	result = ft_calloc(m_size, sizeof(char *));
	if (result == NULL)
		return (NULL);
	index = 0;
	while (cur != NULL)
	{
		result[index] = ft_strdup(cur->str);
		if (result[index] == NULL)
		{
			ft_free_strings(&result);
			return (NULL);
		}
		index++;
		cur = cur->next;
	}
	return (result);
}

char	**token_to_command(t_token *token)
{
	char	**result;

	if (ft_strncmp(token->str, "cd", 3) == 0 \
		&& token->next == NULL)
		result = is_cd_follow_no_dir(token);
	else
		result = tmp_name(token);
	if (result == NULL)
		return (NULL);
	token_clear(&token);
	return (result);
}
