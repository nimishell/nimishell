/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:42:07 by wbae              #+#    #+#             */
/*   Updated: 2023/04/20 22:57:26 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "error.h"
#include <sys/param.h>
#include <sys/errno.h>

extern char	**environ;

int	ft_cd(char *path, char **argv)
{
	char	*dir;

	if (argv[1] == NULL)
		dir = "/Users/yeongo";
	else
		dir = argv[1];
	if (chdir(dir) == -1)
	{
		ft_perror(path, argv[1]);
		return (0);
	}
	return (1);
}

int	ft_echo(char *path, char **argv)
{
	int	followd_new_line;
	int	index_argv;

	(void)path;
	followd_new_line = 1;
	index_argv = 1;
	if (argv[index_argv] != NULL
		&& ft_strncmp(argv[index_argv], "-n", 3) == 0)
	{
		followd_new_line = 0;
		index_argv++;
	}
	while (argv[index_argv] != NULL)
	{
		ft_putstr_fd(argv[index_argv], STDOUT_FILENO);
		index_argv++;
	}
	if (followd_new_line == 1)
		ft_putchar_fd('\n', 1);
	return (1);
}

int	ft_env(char *path, char **argv)
{
	int	index_env;

	// (void)path;
	// if (argv[1] != NULL)
	// 	return (0);
	index_env = 0;
	while (environ[index_env])
	{
		ft_putstr_fd(environ[index_env], STDOUT_FILENO);
		index_env++;
	}
	return (1);
}

int	ft_unset(t_token *token);

int	ft_pwd(t_token *token)
{
	t_token	*next_token;
	char	working_path[MAXPATHLEN];

	next_token = token->next;
	if (next_token != NULL)
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		return (0);
	}
	getcwd(working_path, MAXPATHLEN);
	ft_putstr_fd(working_path, 1);
	return (1);
}

int	ft_export(t_token *token);
int	ft_exit(t_token *token);

int	is_builtin(t_token *token)
{
	char	*str;
	int		result;

	str = token->str;
	if (ft_strncmp(str, "cd", 3) == 0)
		result = ft_cd(token);
	else if (ft_strncmp(str, "echo", 5) == 0)
		result = ft_echo(token);
	else if (ft_strncmp(str, "env", 4) == 0)
		result = ft_env(token);
	else if (ft_strncmp(str, "unset", 6) == 0)
		result = ft_unset(token);
	else if (ft_strncmp(str, "pwd", 4) == 0)
		result = ft_pwd(token);
	else if (ft_strncmp(str, "export", 7) == 0)
		result = ft_export(token);
	else if (ft_strncmp(str, "exit", 5) == 0)
		result = ft_exit(token);
	else
		result = 0;
	return (result);
}
