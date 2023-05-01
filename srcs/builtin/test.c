/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 20:34:25 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/02 00:36:10 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

extern char	**environ;
//
// enum e_bool
// {
// 	FALSE,
// 	TRUE
// };

char	**dup_argv(int argc, char **argv)
{
	char	**result;
	int		index;

	result = malloc(sizeof(char *) * (argc + 1));
	index = 0;
	while (index < argc)
	{
		result[index] = ft_strdup(argv[index]);
		index++;
	}
	result[index] = NULL;
	return (result);
}

static char	**get_path(void)
{
	int		index;
	char	*path;
	char	**result;

	index = 0;
	while (environ[index])
	{
		path = ft_strnstr(environ[index], "PATH=", 5);
		if (path != NULL)
			break ;
		index++;
	}
	if (path == NULL)
		return (NULL);
	result = ft_split(path + 5, ':');
	return (result);
}

int	print_modified_argv(int argc, char **command, int index)
{
	const int	max = 2;
	int			jndex;

	index = 0;
	while (index < max - 1)
	{
		printf("==========  %d start  ==========\n", index);
		jndex = 0;
		while (jndex < argc)
		{
			printf("command[%d] (%p): %s\n", jndex, command[jndex], command[jndex]);
			jndex++;
		}
		printf("==========  %d  end   ==========\n", index);
		printf("\n");
		index++;
	}
	return (0);
}

int	append_path(int argc, char **command, char **path)
{
	int	index;

	ft_strapp_front("/", &command[0]);
	index = 0;
	while (path[index])
	{
		ft_strapp_front(path[index], &command[0]);
		print_modified_argv(argc, command, index);
		index++;
	}
	return (0);
}

int	print_test(int argc, char *cmd, char **argv)
{
	char	**path;

	path = get_path();
	printf("\n");
	printf("before command(%p): %s\n\n", cmd, cmd);
	append_path(argc, argv, path);
	printf("after command(%p): %s\n\n", cmd, cmd);
	return (0);
}

int	main(int argc, char **argv)
{
	char	**duplicated_argv;

	duplicated_argv = dup_argv(argc, argv);
	print_test(argc, duplicated_argv[0], duplicated_argv);
	return (0);
}
