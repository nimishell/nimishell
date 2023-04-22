/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:23:50 by wbae              #+#    #+#             */
/*   Updated: 2023/04/22 16:56:33 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	token_to_cmd(t_token *token, t_cmd *cmd)
{
	t_cmd	*tmp;
	int i = 0;

	while (token)
	{
		cmd->token = token;
		cmd->str = ft_strdup(token->str);
		if (token->type == T_CHUNK)
			cmd->syntax = 1;
		cmd->size++;
		printf("cmd [%d] %s\n", ++i, cmd->str);
		if (token->next)
		{
			tmp = ft_calloc(1, sizeof(t_cmd));
			cmd->next = tmp;
			tmp->prev = cmd;
			cmd = cmd->next;
		}
		token = token->next;
	}
}
