/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:37:37 by wbae              #+#    #+#             */
/*   Updated: 2023/04/04 19:16:57 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	standard_error(int code)
{
	char	*str;

	str = strerror(code);
	ft_putstr_fd("minishell: ", 2);
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
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	if (!flag)
		g_env->status = exit_code;
	if (flag)
		exit(exit_code);
}
