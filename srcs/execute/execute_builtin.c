/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:42:07 by wbae              #+#    #+#             */
/*   Updated: 2023/05/03 16:20:16 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin.h"
#include <stdio.h>

int	execute_builtin(char **command)
{
	int	result;

	printf("hi, builtin\n");
	if (ft_strncmp(command[0], "cd", 3) == 0)
		result = ft_cd(command);
	else if (ft_strncmp(command[0], "echo", 5) == 0)
		result = ft_echo(command);
	else if (ft_strncmp(command[0], "env", 4) == 0)
		result = ft_env(command);
	else if (ft_strncmp(command[0], "unset", 6) == 0)
		result = ft_unset(command);
	else if (ft_strncmp(command[0], "pwd", 4) == 0)
		result = ft_pwd(command);
	else if (ft_strncmp(command[0], "export", 7) == 0)
		result = ft_export(command);
	else if (ft_strncmp(command[0], "exit", 5) == 0)
		result = ft_exit(command);
	else
		result = 1;
	exit(result);
}
