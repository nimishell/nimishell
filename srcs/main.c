/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:33:23 by wbae              #+#    #+#             */
/*   Updated: 2023/04/26 19:49:10 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipe.h"
#include "parsing.h"

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
		exit_with_message(NULL, NULL, "Argument input error", 2);
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
	t_cmd			*cmd;
	struct termios	terminal;

	tcgetattr(STDIN_FILENO, &terminal);
	main_init(ac, av, envp);
	while (1)
	{
		line = readline(MINISHELL);
		if (!line)
			break ;
		if (*line != '\0' && !is_space(line))
		{
			cmd = NULL;
			add_history(line);
			parse(&cmd, line);
		}
		// execute_multi_process(cmd);
		free (line);
	}
	tcsetattr(STDOUT_FILENO, TCSANOW, &terminal);
	ft_putstr_fd("\033[1A", STDOUT_FILENO);
	ft_putstr_fd("\033[11C", STDOUT_FILENO);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	// atexit(f);
	return (0);
}
