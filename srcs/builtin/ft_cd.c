/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:02:45 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/05 20:46:31 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "builtin.h"
#include <sys/param.h>

int	ft_cd(char **argv)
{
	char	*dir;
	char	old_dir[MAXPATHLEN];
	char	new_dir[MAXPATHLEN];
	char	*old_pwd_key;
	char	*pwd_key;

	getcwd(old_dir, MAXPATHLEN);
	dir = ft_strdup(argv[1]);
	if (chdir(dir) == -1)
	{
		ft_perror("cd", argv[1]);
		return (1);
	}
	getcwd(new_dir, MAXPATHLEN);
	old_pwd_key = ft_strdup("OLDPWD");
	pwd_key = ft_strdup("PWD");
	export_variable(&old_pwd_key, old_dir);
	export_variable(&pwd_key, new_dir);
	return (0);
}
