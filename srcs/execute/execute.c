/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:30:06 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/21 20:34:54 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"

extern char	**environ;

static void	execve_absolute_path(char **command)
{
	execve(command[0], command, environ);
	exit_with_perror("zsh", command[0], 127);
}

static void	execve_relative_path(char **command, char **path)
{
	char	*command_tmp;
	int		index;

	command_tmp = ft_strjoin("/", command[0]);
	index = 0;
	while (path[index])
	{
		ft_free_str(&(command[0]));
		command[0] = ft_strjoin(path[index], command_tmp);
		execve(command[0], command, environ);
		index++;
	}
	ft_free_str(&command_tmp);
}

void	execve_command(char **command, char **path)
{
	char	*command_org;

	command_org = ft_strdup(command[0]);
	if (path == NULL || ft_strchr(command[0], '/'))
		execve_absolute_path(command);
	execve_relative_path(command, path);
	ft_free_strings(&path);
	ft_free_strings(&command);
	exit_with_message("zsh", command_org, "Command not found", 127);
}
