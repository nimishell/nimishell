/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:33:23 by wbae              #+#    #+#             */
/*   Updated: 2023/04/11 20:57:15 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_space(char *line)
{
	while (*line)
	{
		if (*line != 32 && !(*line >= 9 && *line <= 13))
			return (0);
		line++;
	}
	return (1);
}

void	main_init(int ac, char *av[], char *envp[])
{
	struct termios	term;

	(void)av;
	if (ac != 1)
		print_error("Argument input error\n", 2);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDOUT_FILENO, TCSANOW, &term);
	set_sig();
	copy_env(envp);
}

void	f(void)
{
	system("leaks minishell");
}

int	main(int ac, char *av[], char *envp[])
{
	char			*line;
	t_cmd			cmd;
	struct termios	terminal;

	tcgetattr(STDIN_FILENO, &terminal);
	main_init(ac, av, envp);
	while (1)
	{
		line = readline("\033[0;32mMINISHELL$\033[0m ");
		if (!line)
			break ;
		if (*line != '\0' && !is_space(line))
		{
			add_history(line);
			parse(&cmd, line);
		}
	}
	tcsetattr(STDOUT_FILENO, TCSANOW, &terminal);
	ft_putstr_fd("\033[1A", STDOUT);
	ft_putstr_fd("\033[11C", STDOUT);
	ft_putstr_fd("exit\n", STDOUT);
	// atexit(f);
	return (0);
}
