/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:34:56 by wbae              #+#    #+#             */
/*   Updated: 2023/05/03 11:28:46 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*ret;

	ret = ft_calloc(1, sizeof(t_cmd));
	if (!ret)
		return (NULL);
	ret->fd[INPUT] = STDIN_FILENO;
	ret->fd[OUTPUT] = STDOUT_FILENO;
	return (ret);
}
