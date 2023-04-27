/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:02:45 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/27 20:48:20 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include <sys/param.h>

int	ft_cd(char **argv)
{
	char	*dir;
	char	old_dir[MAXPATHLEN];
	char	*old_pwd_key;
	char	*pwd_key;

	getcwd(old_dir, MAXPATHLEN);
	dir = ft_strdup(argv[1]);
	if (chdir(dir) == -1)
	{
		ft_perror("cd", argv[1]);
		return (1);
	}
	old_pwd_key = ft_strdup("OLDPWD");
	pwd_key = ft_strdup("PWD");
	export_variable(&old_pwd_key, old_dir);
	export_variable(&pwd_key, dir);
	return (0);
}

int	ft_pwd(char **argv)
{
	char	working_path[MAXPATHLEN];

	if (argv[1] != NULL)
	{
		exit_with_message("pwd", NULL, "too many arguments", 1);
		return (1);
	}
	getcwd(working_path, MAXPATHLEN);
	ft_putstr_fd(working_path, STDOUT_FILENO);
	return (0);
}
