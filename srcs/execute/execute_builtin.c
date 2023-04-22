/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:42:07 by wbae              #+#    #+#             */
/*   Updated: 2023/04/22 14:33:19 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin.h"

int	execute_builtin(char *command, char **argv)
{
	int	result;

	if (ft_strncmp(command, "cd", 3) == 0)
		result = ft_cd(command, argv);
	else if (ft_strncmp(command, "echo", 5) == 0)
		result = ft_echo(command, argv);
	else if (ft_strncmp(command, "env", 4) == 0)
		result = ft_env(command, argv);
	else if (ft_strncmp(command, "unset", 6) == 0)
		result = ft_unset(command, argv);
	else if (ft_strncmp(command, "pwd", 4) == 0)
		result = ft_pwd(command, argv);
	else if (ft_strncmp(command, "export", 7) == 0)
		result = ft_export(command, argv);
	else if (ft_strncmp(command, "exit", 5) == 0)
		result = ft_exit(command, argv);
	else
		result = 0;
	return (result);
}
