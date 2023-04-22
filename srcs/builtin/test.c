/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 20:34:25 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/22 16:44:05 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/inc/libft.h"
#include <stdlib.h>
#include <stdio.h>

extern char	**environ;

void	print_test(char *cmd, char **argv)
{
	printf("Before:\n cmd: %s\n argv[0]: %s\n\n", cmd, argv[0]);
	ft_strapp_front("after modify string ", &argv[0]);
	printf("After: \n cmd: %s\n argv[0]: %s\n\n", cmd, argv[0]);
}

int	main(int argc, char **argv)
{
	char	**test;
	int		index_argv;
	int		index_test;

	test = malloc(sizeof(char *) * argc);
	index_argv = 1;
	index_test = 0;
	while (argv[index_argv])
	{
		test[index_test] = ft_strdup(argv[index_argv]);
		index_argv++;
		index_test++;
	}
	test[index_test] = NULL;
	print_test(test[0], test);
	return (0);
}
