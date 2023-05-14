/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:30:42 by wbae              #+#    #+#             */
/*   Updated: 2023/05/14 19:30:44 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ms_free(char *p1, char *p2, char *p3, char *p4)
{
	if (p1)
		free(p1);
	if (p2)
		free(p2);
	if (p3)
		free(p3);
	if (p4)
		free(p4);
	return (NULL);
}
//
// void	ft_free_char_arr(char **p)
// {
// 	int	i;
//
// 	i = 0;
// 	while (p[i])
// 	{
// 		if (p[i])
// 		{
// 			free(p[i]);
// 			p[i] = NULL;
// 		}
// 		i++;
// 	}
// 	free(p);
// }
//
// void	ft_free_token(t_token **token)
// {
// 	t_token	*remove_token;
//
// 	if (!*token)
// 		return ;
// 	while (*token)
// 	{
// 		remove_token = *token;
// 		*token = (*token)->next;
// 		if (remove_token->str)
// 		{
// 			free(remove_token->str);
// 			remove_token->str = NULL;
// 		}
// 		free(remove_token);
// 	}
// }
//
// void	ft_free_cmd(t_cmd_node **cmd)
// {
// 	t_cmd_node	*remove_cmd;
//
// 	if (!*cmd)
// 		return ;
// 	while (*cmd)
// 	{
// 		remove_cmd = *cmd;
// 		*cmd = (*cmd)->next;
// 		if (remove_cmd->argv)
// 			ft_free_char_arr(remove_cmd->argv);
// 		free(remove_cmd);
// 	}
// }
