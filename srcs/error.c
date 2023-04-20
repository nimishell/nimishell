/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:37:37 by wbae              #+#    #+#             */
/*   Updated: 2023/04/20 21:03:16 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/errno.h>

extern int	errno;

void	ft_perror(char *p_name, char *argument, int code)
{
	char	*str;

	str = strerror(errno);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(p_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(argument, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	exit(code);
}

void	print_error(char *str, int code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	exit(code);
}

void	cmd_error(char *str, int code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	exit(code);
}

void	print_cmd_error(char *str, char *cmd, int code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	exit(code);
}

void	syntax_error(char *str, int exit_code, int flag)
{
	ft_putstr_fd("minishell: syntax error", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	if (!flag)
		g_env->status = exit_code;
	if (flag)
		exit(exit_code);
}
