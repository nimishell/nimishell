/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:33:23 by wbae              #+#    #+#             */
/*   Updated: 2023/05/07 18:19:55 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "execute_process.h"

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
	t_termios	term;

	(void)av;
	if (ac != 1)
		exit_with_message(NULL, NULL, "Argument input error", STDERR_FILENO);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDOUT_FILENO, TCSANOW, &term);
	copy_env(envp);
}

void	f(void)
{
	system("leaks minishell");
}

int	main(int ac, char *av[], char *envp[])
{
	char	*line;
	t_cmd	*cmd;

	main_init(ac, av, envp);
	while (1)
	{
		set_sig(CUSTOM, CUSTOM);
		line = readline(MINISHELL);
		if (!line)
			break ;
		if (*line != '\0' && !is_space(line))
		{
			cmd = NULL;
			add_history(line);
			if (parse(&cmd, line))
			{
				if (is_single_builtin(cmd))
					execute_single_process(cmd);
				else
					execute_multi_process(cmd);
				ft_free_cmd(&cmd);
			}
		}
		free(line);
	}
	// atexit(f);
	return (0);
}
