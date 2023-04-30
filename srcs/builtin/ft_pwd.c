/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 19:48:04 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/30 20:37:22 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include <sys/param.h>

int	ft_pwd(char **argv)
{
	char	working_path[MAXPATHLEN];

	if (argv[1] != NULL)
	{
		exit_with_message("pwd", NULL, "too many arguments", 1);
		return (1);
	}
	getcwd(working_path, MAXPATHLEN);
	ft_putstr_fd(working_path, STDOUT_FILENO);
	return (0);
}
