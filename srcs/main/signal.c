/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:36:18 by wbae              #+#    #+#             */
/*   Updated: 2023/05/11 18:47:31 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	custom_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	heredoc_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		ft_putendl_fd("", STDERR_FILENO);
		exit(1);
	}
}

void	set_sig(int sig_int, int sig_quit)
{
	if (sig_int == DEFAULT)
		signal(SIGINT, SIG_DFL);
	else if (sig_int == IGNORE)
		signal(SIGINT, SIG_IGN);
	else if (sig_int == CUSTOM)
		signal(SIGINT, custom_handler);
	else if (sig_int == HEREDOC)
		signal(SIGINT, heredoc_handler);
	if (sig_quit == DEFAULT)
		signal(SIGQUIT, SIG_DFL);
	else if (sig_quit == IGNORE)
		signal(SIGQUIT, SIG_IGN);
}
