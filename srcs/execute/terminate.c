/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 20:35:53 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/08 13:37:37 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_terminate_code(int terminate_code)
{
	if (terminate_code == SIGINT)
		ft_putstr_fd("^C", STDERR_FILENO);
	else if (terminate_code == SIGQUIT)
	{
		ft_putstr_fd("^\\Quit: ", STDERR_FILENO);
		ft_putnbr_fd(terminate_code, STDERR_FILENO);
	}
	// ft_putstr_fd("Terminate: ", STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}
