/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:42:07 by wbae              #+#    #+#             */
/*   Updated: 2023/04/21 16:06:55 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin.h"

int	execute_builtin(char *path, char **argv)
{
	int	result;

	if (ft_strncmp(path, "cd", 3) == 0)
		result = ft_cd(path, argv);
	else if (ft_strncmp(path, "echo", 5) == 0)
		result = ft_echo(path, argv);
	else if (ft_strncmp(path, "env", 4) == 0)
		result = ft_env(path, argv);
	else if (ft_strncmp(path, "unset", 6) == 0)
		result = ft_unset(path, argv);
	else if (ft_strncmp(path, "pwd", 4) == 0)
		result = ft_pwd(path, argv);
	else if (ft_strncmp(path, "export", 7) == 0)
		result = ft_export(path, argv);
	else if (ft_strncmp(path, "exit", 5) == 0)
		result = ft_exit(path, argv);
	else
		result = 0;
	return (result);
}
