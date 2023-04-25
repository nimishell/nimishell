/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 20:34:25 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/25 21:03:22 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

extern char	**environ;
//
// enum e_bool
// {
// 	FALSE,
// 	TRUE
// };
//
// char	**make_command(int argc, char **argv)
// {
// 	char	**result;
// 	int		index;
//
// 	result = malloc(sizeof(char *) * (argc + 1));
// 	result[0] = ft_strdup("echo");
// 	index = 1;
// 	while (index < argc)
// 	{
// 		result[index] = ft_strdup(argv[index]);
// 		index++;
// 	}
// 	result[index] = NULL;
// 	return (result);
// }

int	main(void)
{
	int	index;

	index = 0;
	while (environ[index])
	{
		free(environ[index]);
		index++;
	}
	free(environ);
	return (0);
}
