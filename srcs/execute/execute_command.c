/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:30:06 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/15 16:31:33 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structure.h"
#include "error.h"

static char	**get_path(char **envp)
{
	int		index;
	char	*path;
	char	**result;

	index = 0;
	while (envp[index])
	{
		path = ft_strnstr(envp[index], "PATH=", 5);
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
	exit_with_errno(command[0], command[1], 127);
}

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

char	**make_env_arr(void)
{
	t_env_node	*cur;
	char		**result;
	int			index;

	result = ft_calloc(g_env.value_count + 1, sizeof(char *));
	if (result == NULL)
		return (NULL);
	index = 0;
	cur = g_env.head;
	while (cur)
	{
		if (cur->is_value == TRUE)
		{
			result[index] = ft_strjoin(cur->key, "=");
			ft_strapp_back(&result[index], cur->value);
			index++;
		}
		cur = cur->next;
	}
	return (result);
}

void	execute_command(char **command)
{
	char	**path;
	char	**envp;
	char	*command_org;

	envp = make_env_arr();
	path = get_path(envp);
	command_org = ft_strdup(command[0]);
	if (path == NULL || ft_strchr(command[0], '/'))
		execute_absolute_path(command, envp);
	execute_relative_path(command, path, envp);
	ft_free_strings(&path);
	ft_free_strings(&envp);
	exit_with_message(command_org, command[1], "command not found", 127);
}
