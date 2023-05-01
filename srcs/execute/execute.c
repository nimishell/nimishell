/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:30:06 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/02 01:16:04 by yeongo           ###   ########.fr       */
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

// 원래대로 돌려놔 다
//
// static void	execve_relative_path(char **command, char **path)
static void	execute_relative_path(char **command, char **path, char **envp)
{
	char	*command_tmp;
	int		index;

	command_tmp = ft_strjoin("/", command[0]);
	index = 0;
	while (path[index])
	{
		ft_free_str(&(command[0]));
		command[0] = ft_strjoin(path[index], command_tmp);
		execve(command[0], command, envp);
		index++;
	}
	ft_free_str(&command_tmp);
}
// {
// 	int	index;
//
// 	ft_strapp_front("/", &command[0]);
// 	index = 0;
// 	while (path[index])
// 	{
// 		ft_strapp_front(path[index], &command[0]);
// 		execve(command[0], command, envp);
// 		index++;
// 	}
// }

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

void	execute_command(char **command)
{
	char	**path;
	char	**envp;
	char	*command_org;

	path = get_path();
	envp = make_env_arr();
	command_org = ft_strdup(command[0]);
	if (path == NULL || ft_strchr(command[0], '/'))
		execute_absolute_path(command, envp);
	execute_relative_path(command, path, envp);
	ft_free_strings(&path);
	ft_free_strings(&command);
	ft_free_strings(&envp);
	exit_with_message(command_org, NULL, "Command not found", 127);
}
