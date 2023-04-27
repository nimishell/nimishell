/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:06:26 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/27 20:51:00 by yeongo           ###   ########.fr       */
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

int	ft_exit(char **argv)
{
	int	status;

	ft_putendl_fd("exit", STDOUT_FILENO);
	if (argv[1] == NULL)
		return (0);
	if (is_digit_array(argv[1]) == FALSE)
	{
		ft_error_message("exit", argv[1], "numeric argument required");
		return (255);
	}
	if (argv[2] != NULL)
	{
		ft_error_message("exit", argv[1], "too many arguments");
		return (1);
	}
	status = ft_atoi(argv[1]) % 256;
	return (status);
}
