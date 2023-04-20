/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:37:37 by wbae              #+#    #+#             */
/*   Updated: 2023/04/20 22:18:58 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/errno.h>

void	ft_perror(char *cmd, char *arg)
{
	char	*err_message;

	err_message = strerror(errno);
	ft_putstr_fd("minishell: ", 2);
	if (cmd != NULL)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (arg != NULL)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(err_message, 2);
	ft_putstr_fd("\n", 2);
}

void	exit_with_perror(char *cmd, char *arg, int status)
{
	ft_perror(cmd, arg);
	exit(status);
}

void	exit_with_message(char *cmd, char *arg, char *messsage, int status)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd != NULL)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (arg != NULL)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(messsage, 2);
	ft_putstr_fd("\n", 2);
	exit(status);
}

void	syntax_error(char *message, int status, int flag)
{
	ft_putstr_fd("minishell: syntax error", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	if (!flag)
		g_env->status = status;
	if (flag)
		exit(status);
}
