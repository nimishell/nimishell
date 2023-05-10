/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:33:23 by wbae              #+#    #+#             */
/*   Updated: 2023/05/10 20:37:18 by wbae             ###   ########.fr       */
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
	t_env		*head;
	t_termios	term;

	(void)av;
	if (ac != 1)
		exit_with_message(NULL, NULL, "Argument input error", STDERR_FILENO);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDOUT_FILENO, TCSANOW, &term);
	copy_env(envp);
	head = g_env;
	while (head)
	{
		if (!ft_strncmp(head->key, "SHLVL", 6))
			head->value = ft_strdup(ft_itoa(ft_atoi(head->value) + 1));
		head = head->next;
	}

}

int	main(int ac, char *av[], char *envp[])
{
	char			*line;
	struct termios	term;
	t_cmd			*cmd;

	tcgetattr(STDIN_FILENO, &term);
	main_init(ac, av, envp);
	while (1)
	{
		set_sig(CUSTOM, IGNORE);
		line = readline(MINISHELL);
		if (!line)
			break ;
		if (*line != '\0' && !is_space(line))
		{
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
	tcsetattr(STDOUT_FILENO, TCSANOW, &term);
	return (g_env->status);
}
