/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:06:00 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/22 14:32:32 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"

extern char	**environ;

int	ft_env(char *command, char **argv)
{
	int	index_env;

	(void)command;
	if (argv[1] != NULL)
	{
		exit_with_message("env", NULL, "too many arguments", 1);
		return (0);
	}
	index_env = 0;
	while (environ[index_env])
	{
		ft_putstr_fd(environ[index_env], STDOUT_FILENO);
		index_env++;
	}
	return (1);
}

int	ft_export(char *command, char **argv);

int	ft_unset(char *command, char **argv);
