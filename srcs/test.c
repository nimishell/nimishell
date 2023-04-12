/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 20:34:25 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/12 22:48:54 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>

int	main(void)
{
	char	before_path[MAXPATHLEN];
	char	after_path[MAXPATHLEN];

	getcwd(before_path, MAXPATHLEN);
	printf("%s\n", before_path);
	system("ls");
	chdir("/Users/yeongo");
	getcwd(after_path, MAXPATHLEN);
	printf("%s\n", after_path);
	system("ls");
	return (0);
}
