/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:02:45 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/15 16:53:55 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "envp.h"
#include "builtin.h"
#include "ft_free.h"
#include "error.h"
#include <sys/param.h>

int	ft_cd(char **argv)
{
	char	*dir;
	char	old_dir[MAXPATHLEN];
	char	new_dir[MAXPATHLEN];
	char	*old_pwd_key;
	char	*pwd_key;

	getcwd(old_dir, MAXPATHLEN);
	if (argv[1] == NULL || !ft_strncmp(argv[1], "~", 2))
		dir = ft_strdup(find_value("HOME"));
	else
		dir = ft_strdup(argv[1]);
	if (chdir(dir) == -1)
	{
		free(dir);
		ft_perror("cd", argv[1]);
		return (1);
	}
	getcwd(new_dir, MAXPATHLEN);
	old_pwd_key = ft_strdup("OLDPWD");
	pwd_key = ft_strdup("PWD");
	export_variable(&old_pwd_key, old_dir);
	export_variable(&pwd_key, new_dir);
	ft_free_ptrs(old_pwd_key, pwd_key, dir);
	return (0);
}
