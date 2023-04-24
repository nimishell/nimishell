/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 20:34:25 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/24 22:40:04 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/inc/libft.h"
#include <stdlib.h>
#include <stdio.h>

extern char	**environ;

int	main(void)
{
	int	index;

	index = 0;
	while (environ[index])
	{
		printf("%s\n", environ[index]);
		index++;
	}
	return (0);
}
