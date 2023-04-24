/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:42:07 by wbae              #+#    #+#             */
/*   Updated: 2023/04/24 13:32:13 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin.h"

int	execute_builtin(char *command, char **argument)
{
	int	result;

	if (ft_strncmp(command, "cd", 3) == 0)
		result = ft_cd(command, argument);
	else if (ft_strncmp(command, "echo", 5) == 0)
		result = ft_echo(command, argument);
	else if (ft_strncmp(command, "env", 4) == 0)
		result = ft_env(command, argument);
	else if (ft_strncmp(command, "unset", 6) == 0)
		result = ft_unset(command, argument);
	else if (ft_strncmp(command, "pwd", 4) == 0)
		result = ft_pwd(command, argument);
	else if (ft_strncmp(command, "export", 7) == 0)
		result = ft_export(command, argument);
	else if (ft_strncmp(command, "exit", 5) == 0)
		result = ft_exit(command, argument);
	else
		result = 0;
	return (result);
}
