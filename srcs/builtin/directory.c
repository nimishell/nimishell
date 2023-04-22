/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:02:45 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/22 14:32:16 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include <sys/param.h>

int	ft_cd(char *command, char **argv)
{
	char	*dir;

	if (argv[1] == NULL)
		dir = "/Users/yeongo";
	else
		dir = argv[1];
	if (chdir(dir) == -1)
	{
		ft_perror(command, argv[1]);
		return (0);
	}
	return (1);
}

int	ft_pwd(char *command, char **argv)
{
	char	working_path[MAXPATHLEN];

	(void)command;
	if (argv[1] != NULL)
	{
		exit_with_message("pwd", NULL, "too many arguments", 1);
		return (0);
	}
	getcwd(working_path, MAXPATHLEN);
	ft_putstr_fd(working_path, STDOUT_FILENO);
	return (1);
}
