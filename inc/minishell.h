/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:56:15 by wbae              #+#    #+#             */
/*   Updated: 2023/05/12 16:15:27 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <unistd.h>
# include <termios.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "error.h"
# include "structure.h"
# include "debug.h" //DO NOT SUBMIT!!!

t_env	*g_env;

void	set_sig(int sig_int, int sig_quit);
void	custom_handler(int signal);
void	heredoc_handler(int signal);

void	copy_env(char *env[]);
char	*get_value(char *key);

void	*ms_free(char *p1, char *p2, char *p3, char *p4);
void	ft_free_char_arr(char **p);
void	ft_free_token(t_token **token);
void	ft_free_cmd(t_cmd **cmd);
void	ft_free_redir(t_redir **redir);

#endif
