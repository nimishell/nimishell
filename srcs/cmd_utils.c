/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:34:56 by wbae              #+#    #+#             */
/*   Updated: 2023/04/26 14:39:55 by wbae             ###   ########.fr       */
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
	ret->file = malloc(sizeof(t_file));
	if (!ret->file)
		return (NULL);
	ret->file->infile = NULL;
	ret->file->outfile = NULL;
	ret->file->infile_fd = -1;
	ret->file->outfile_fd = -1;
	ret->next = NULL;
	ret->prev = NULL;
	ret->redir[0] = 0;
	ret->redir[1] = 0;
	return (ret);
}
