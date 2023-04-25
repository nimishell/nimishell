/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:30:06 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/25 13:23:36 by wbae             ###   ########.fr       */
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

static void	free_and_exit(char *command, char ***argument, char ***path)
{
	ft_free_strings(path);
	ft_free_strings(argument);
	ft_error_message(command, NULL, "Command not found");
	exit(127);
}

void	execute_command(char *command, char **argument)
{
	char	**path;

	path = get_path();
	if (path == NULL || ft_strchr(argument[0], '/'))
		execute_absolute_path(argument);
	execute_relative_path(argument, path);
	free_and_exit(command, &argument, &path);
}
