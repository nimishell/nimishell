/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:42:07 by wbae              #+#    #+#             */
/*   Updated: 2023/04/26 16:20:55 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin.h"

int	execute_builtin(char *command, char **argv)
{
	int	result;

	if (ft_strncmp(command, "cd", 3) == 0)
		result = ft_cd(argv);
	else if (ft_strncmp(command, "echo", 5) == 0)
		result = ft_echo(argv);
	else if (ft_strncmp(command, "env", 4) == 0)
		result = ft_env(argv);
	else if (ft_strncmp(command, "unset", 6) == 0)
		result = ft_unset(argv);
	else if (ft_strncmp(command, "pwd", 4) == 0)
		result = ft_pwd(argv);
	else if (ft_strncmp(command, "export", 7) == 0)
		result = ft_export(argv);
	else if (ft_strncmp(command, "exit", 5) == 0)
		result = ft_exit(argv);
	else
		result = 0;
	return (result);
}
