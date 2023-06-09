/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:23:50 by wbae              #+#    #+#             */
/*   Updated: 2023/05/15 16:39:38 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_list.h"
#include "envp.h"

static char	**is_cd_follow_default(t_token *token)
{
	char	**result;

	result = ft_calloc(3, sizeof(char *));
	if (result == NULL)
		return (NULL);
	result[0] = ft_strdup(token->str);
	result[1] = ft_strdup(find_value("HOME"));
	return (result);
}

static int	get_cmd_size(t_token *token)
{
	int		size;

	size = 0;
	while (token && token->type != T_PIPE)
	{
		size++;
		token = token->next;
	}
	return (size);
}

static char	**make_array(t_token *token, int size)
{
	int		idx;
	char	**result;

	result = ft_calloc(size, sizeof(char *));
	if (!result)
		return (NULL);
	idx = 0;
	while (--size)
	{
		result[idx] = ft_strdup(token->str);
		if (!result[idx])
		{
			ft_free_strings(&result);
			return (NULL);
		}
		idx++;
		token = token->next;
	}
	result[idx] = 0;
	return (result);
}

int	token_to_cmd(t_cmd *cmd, t_token *token)
{
	t_cmd_node	*tmp;
	int			size;

	while (token)
	{
		tmp = cmd_new();
		if (!tmp)
			return (FAIL);
		size = get_cmd_size(token) + 1;
		if (ft_strncmp(token->str, "cd", 3) == 0 \
			&& (token->next == NULL || !ft_strncmp(token->next->str, "~", 2)))
			tmp->argv = is_cd_follow_default(token);
		else
			tmp->argv = make_array(token, size);
		if (!tmp->argv)
			return (FAIL);
		cmd_add_back(cmd, tmp);
		while (--size && token->next)
			token = token->next;
		if (!token->next)
			break ;
		token = token->next;
	}
	return (SUCCESS);
}
