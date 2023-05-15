/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:49:46 by wbae              #+#    #+#             */
/*   Updated: 2023/05/15 14:50:25 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SIGNAL_H
# define FT_SIGNAL_H

void	set_sig(int sig_int, int sig_quit);
void	custom_handler(int signal);
void	heredoc_handler(int signal);

#endif
