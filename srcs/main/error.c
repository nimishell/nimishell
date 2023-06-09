/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:37:37 by wbae              #+#    #+#             */
/*   Updated: 2023/05/15 16:35:47 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structure.h"
#include <string.h>
#include <sys/errno.h>

void	ft_perror(char *cmd, char *arg)
{
	char	*err_message;

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
	g_env.status = status;
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
	g_env.status = status;
	exit(status);
}

void	ft_syntax_error(char *argv)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", \
		STDERR_FILENO);
	if (argv)
	{
		ft_putchar_fd('`', STDERR_FILENO);
		ft_putstr_fd(argv, STDERR_FILENO);
		ft_putchar_fd('\'', STDERR_FILENO);
		free(argv);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
	g_env.status = 258;
}
