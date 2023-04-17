/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 20:34:25 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/17 20:45:05 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/errno.h>

extern int	errno;

int	main(void)
{
	char	before_path[MAXPATHLEN];
	char	after_path[MAXPATHLEN];
	char	*err_str;

	getcwd(before_path, MAXPATHLEN);
	printf("%s\n", before_path);
	system("ls");
	if (chdir("/Users/yeongos") == -1)
	{
		err_str = strerror(errno);
		// perror();
		printf("Error: %d %s\n", errno, err_str);
		return (1);
	}
	getcwd(after_path, MAXPATHLEN);
	printf("%s\n", after_path);
	system("ls");
	return (0);
}
