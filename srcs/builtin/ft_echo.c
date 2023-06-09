/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:58:05 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/12 04:10:05 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structure.h"

static int	find_option(char *str)
{
	int	index;

	if (str == NULL)
		return (FALSE);
	index = 0;
	if (str[index] != '-')
		return (FALSE);
	index++;
	if (str[index] == '\0')
		return (FALSE);
	while (str[index] != '\0')
	{
		if (str[index] != 'n')
			return (FALSE);
		index++;
	}
	return (TRUE);
}

int	ft_echo(char **argv)
{
	int	is_option;
	int	first_argv;
	int	index_argv;

	is_option = FALSE;
	index_argv = 1;
	while (find_option(argv[index_argv]) == TRUE)
	{
		is_option = TRUE;
		index_argv++;
	}
	first_argv = TRUE;
	while (argv[index_argv] != NULL)
	{
		if (first_argv == FALSE)
			ft_putchar_fd(' ', STDOUT_FILENO);
		else
			first_argv = FALSE;
		ft_putstr_fd(argv[index_argv], STDOUT_FILENO);
		index_argv++;
	}
	if (is_option == FALSE)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
