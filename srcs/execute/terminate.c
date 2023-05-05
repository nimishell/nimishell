/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 20:35:53 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/05 20:22:04 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_terminate_code(int terminate_code)
{
	ft_putstr_fd("Terminate: ", STDERR_FILENO);
	ft_putnbr_fd(terminate_code, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}
