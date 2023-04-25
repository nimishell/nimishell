/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:30:06 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/26 03:36:56 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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

static void	execute_absolute_path(char **command, char **envp)
{
	execve(command[0], command, envp);
	exit_with_errno("zsh", command[0], 127);
}

static void	execute_relative_path(char **command, char **path, char **envp)
{
	int	index;

	ft_strapp_front("/", &command[0]);
	index = 0;
	while (path[index])
	{
		ft_strapp_front(path[index], &command[0]);
		execve(command[0], command, envp);
		index++;
	}
}

char	**make_env_arr(void)
{
	t_env	*cur;
	int		env_size;
	char	**result;
	int		index;

	cur = g_env;
	env_size = 0;
	while (cur)
	{
		env_size++;
		cur = cur->next;
	}
	result = ft_calloc(env_size + 1, sizeof(char *));
	if (result == NULL)
		return (NULL);
	index = 0;
	cur = g_env;
	while (cur)
	{
		result[index] = ft_strjoin(cur->key, "=");
		ft_strapp_back(&result[index], cur->value);
		cur = cur->next;
	}
	return (result);
}

void	execute_command(char *command, char **argv)
{
	char	**path;
	char	**envp;

	path = get_path();
	envp = make_env_arr();
	if (path == NULL || ft_strchr(argv[0], '/'))
		execute_absolute_path(argv, envp);
	execute_relative_path(argv, path, envp);
	ft_free_strings(&path);
	ft_free_strings(&argv);
	ft_free_strings(&envp);
	ft_error_message(command, NULL, "Command not found");
	exit(127);
}
