/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:42:07 by wbae              #+#    #+#             */
/*   Updated: 2023/04/04 19:55:21 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_builtin(t_token *token)
{
	char	*str;

	str = token->str;
	if (!ft_strcmp(str, "cd"))
		cd(~);
	else if (!ft_strcmp(str, "echo"))
		echo(~);
	else if (!ft_strcmp(str, "env"))
		env(~);
	else if (!ft_strcmp(str, "unset"))
		unset(~);
	else if (!ft_strcmp(str, "pwd"))
		unset(~);
	else if (!ft_strcmp(str, "export"))
		unset(~);
	else if (!ft_strcmp(str, "exit"))
		unset(~);
}
