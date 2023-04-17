/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:23:50 by wbae              #+#    #+#             */
/*   Updated: 2023/04/17 20:07:20 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	token_to_cmd(t_token *token, t_cmd *cmd)
{
	while (token)
	{
		cmd->token = token->str;
		cmd->syntax = 0;
		cmd->size++;
		token = token->next;
	}
}
