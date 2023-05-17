/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:42:07 by wbae              #+#    #+#             */
/*   Updated: 2023/05/17 21:47:10 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structure.h"
#include "builtin.h"

int	is_builtin(char *command)
{
	const char	*builtin[7] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	int			index;

	index = 0;
	while (index < 7)
	{
		if (ft_strncmp(command, builtin[index], \
				ft_strlen(builtin[index]) + 1) == 0)
			return (TRUE);
		index++;
	}
	return (FALSE);
}

int	execute_builtin(char **command)
{
	int	result;

	if (ft_strncmp(command[0], "cd", sizeof "cd") == 0)
		result = ft_cd(command);
	else if (ft_strncmp(command[0], "echo", sizeof "echo") == 0)
		result = ft_echo(command);
	else if (ft_strncmp(command[0], "env", sizeof "env") == 0)
		result = ft_env(command);
	else if (ft_strncmp(command[0], "unset", sizeof "unset") == 0)
		result = ft_unset(command);
	else if (ft_strncmp(command[0], "pwd", sizeof "pwd") == 0)
		result = ft_pwd();
	else if (ft_strncmp(command[0], "export", sizeof "export") == 0)
		result = ft_export(command);
	else if (ft_strncmp(command[0], "exit", sizeof "exit") == 0)
		result = ft_exit(command);
	else
		result = 1;
	g_env.status = result;
	return (result);
}
