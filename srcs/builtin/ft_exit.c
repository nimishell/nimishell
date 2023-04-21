/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:06:26 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/21 19:23:53 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"

static int	is_digit_array(char *str)
{
	int	index;

	index = 0;
	while (ft_isspace(str[index]))
		index++;
	if (ft_issign(str[index]))
		index++;
	if (str[index] == '\0')
		return (FALSE);
	while (str[index])
	{
		if (ft_isdigit(str[index]) == 0)
			return (FALSE);
		index++;
	}
	return (TRUE);
}

int	ft_exit(char *path, char **argv)
{
	char	status;

	(void)path;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (argv[1] == NULL)
		exit(g_env->status);
	if (is_digit_array(argv[1]) == FALSE)
		exit_with_message("exit", argv[1], "numeric argument required", 255);
	if (argv[2] != NULL)
	{
		ft_error_message("exit", argv[1], "too many arguments");
		return (1);
	}
	status = (char)ft_atoi(argv[1]);
	exit(status);
}
