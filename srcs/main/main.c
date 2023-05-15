/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:33:23 by wbae              #+#    #+#             */
/*   Updated: 2023/05/15 16:37:31 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_list.h"
#include "ft_signal.h"
#include "envp.h"
#include "builtin.h"
#include "parsing.h"
#include "execute_process.h"
#include "error.h"
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>

extern char	**environ;

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

static void	main_init(int ac, char **av, t_cmd *cmd)
{
	t_env_node	*head;
	t_termios	term;
	char		*tmp;

	(void)av;
	if (ac != 1)
		exit_with_message(NULL, NULL, "Argument input error", STDERR_FILENO);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDOUT_FILENO, TCSANOW, &term);
	get_env_lst(environ);
	head = g_env.head;
	while (head)
	{
		if (!ft_strncmp(head->key, "SHLVL", 6))
		{
			tmp = head->value;
			head->value = ft_itoa(ft_atoi(tmp) + 1);
			free(tmp);
		}
		head = head->next;
	}
	memset(cmd, 0, sizeof(t_cmd));
}

static void	run_prompt(t_cmd *cmd)
{
	char	*line;

	while (1)
	{
		set_sig(CUSTOM, IGNORE);
		line = readline(MINISHELL);
		if (!line)
		{
			ft_putstr_fd("\033[1A\033[11C", STDOUT_FILENO);
			ft_exit(NULL);
		}
		if (*line != '\0' && !is_space(line))
		{
			add_history(line);
			if (parse(cmd, line))
			{
				if (is_single_builtin(cmd->head))
					execute_single_process(cmd);
				else
					execute_multi_process(cmd);
				cmd_clear(cmd);
			}
		}
		free(line);
	}
}

int	main(int ac, char **av)
{
	struct termios	term;
	t_cmd			cmd;

	tcgetattr(STDIN_FILENO, &term);
	main_init(ac, av, &cmd);
	run_prompt(&cmd);
	tcsetattr(STDOUT_FILENO, TCSANOW, &term);
	return (g_env.status);
}
