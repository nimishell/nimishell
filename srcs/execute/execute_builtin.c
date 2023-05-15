/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:42:07 by wbae              #+#    #+#             */
/*   Updated: 2023/05/15 16:31:13 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structure.h"
#include "builtin.h"

int	execute_builtin(char **command)
{
	int	result;

	if (ft_strncmp(command[0], "cd", 3) == 0)
		result = ft_cd(command);
	else if (ft_strncmp(command[0], "echo", 5) == 0)
		result = ft_echo(command);
	else if (ft_strncmp(command[0], "env", 4) == 0)
		result = ft_env(command);
	else if (ft_strncmp(command[0], "unset", 6) == 0)
		result = ft_unset(command);
	else if (ft_strncmp(command[0], "pwd", 4) == 0)
		result = ft_pwd();
	else if (ft_strncmp(command[0], "export", 7) == 0)
		result = ft_export(command);
	else if (ft_strncmp(command[0], "exit", 5) == 0)
		result = ft_exit(command);
	else
		result = 1;
	g_env.status = result;
	return (result);
}
