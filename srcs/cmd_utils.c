/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:34:56 by wbae              #+#    #+#             */
/*   Updated: 2023/05/02 17:49:37 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*ret;

	ret = malloc(sizeof(t_cmd));
	if (!ret)
		return (NULL);
	ret->redir = NULL;
	ret->fd[0] = STDIN_FILENO;
	ret->fd[1] = STDOUT_FILENO;
	ret->next = NULL;
	ret->prev = NULL;
	return (ret);
}
