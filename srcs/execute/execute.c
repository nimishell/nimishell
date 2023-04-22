/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:30:06 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/22 14:21:42 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"

extern char	**environ;

static char	**get_path(void)
{
	int		index;
	char	*path;
	char	**result;

	index = 0;
	while (environ[index])
	{
		path = ft_strnstr(environ[index], "PATH=", 5);
		if (path != NULL)
			break ;
		index++;
	}
	if (path == NULL)
		return (NULL);
	result = ft_split(path + 5, ':');
	return (result);
}

static void	execute_absolute_path(char **command)
{
	execve(command[0], command, environ);
	exit_with_errno("zsh", command[0], 127);
}

static void	execute_relative_path(char **command, char **path)
{
	int	index;

	ft_strapp_front("/", &command[0]);
	index = 0;
	while (path[index])
	{
		ft_strapp_front(path[index], &command[0]);
		execve(command[0], command, environ);
		index++;
	}
}

void	execute_command(char **command)
{
	char	*command_org;
	char	**path;

	path = get_path();
	if (path == NULL || ft_strchr(command[0], '/'))
		execute_absolute_path(command);
	command_org = ft_strdup(command[0]);
	execute_relative_path(command, path);
	ft_free_strings(&path);
	ft_free_strings(&command);
	ft_error_message(command_org, NULL, "Command not found");
	ft_free_str(&command_org);
	exit(127);
}
