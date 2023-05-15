/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 19:48:04 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/15 16:30:46 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/param.h>

int	ft_pwd(void)
{
	char	working_path[MAXPATHLEN];

	getcwd(working_path, MAXPATHLEN);
	ft_putendl_fd(working_path, STDOUT_FILENO);
	return (0);
}
