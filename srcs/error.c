/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:37:37 by wbae              #+#    #+#             */
/*   Updated: 2023/04/26 19:45:52 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <sys/errno.h>

void	ft_perror(char *cmd, char *arg)
{
	char	*err_message;

	printf("%d\n", errno);
	err_message = strerror(errno);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (cmd != NULL)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (arg != NULL)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(err_message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	exit_with_errno(char *cmd, char *arg, int status)
{
	ft_perror(cmd, arg);
	exit(status);
}

void	ft_error_message(char *cmd, char *arg, char *message)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (cmd != NULL)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (arg != NULL)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	exit_with_message(char *cmd, char *arg, char *message, int status)
{
	ft_error_message(cmd, arg, message);
	exit(status);
}

void	ft_syntax_error(char *argv, int status, int flag)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", \
		STDERR_FILENO);
	if (argv)
	{
		ft_putchar_fd('`', STDERR_FILENO);
		ft_putstr_fd(argv, STDERR_FILENO);
		ft_putchar_fd('\'', STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
	if (!flag)
		g_env->status = status;
	if (flag)
		exit(status);
}
