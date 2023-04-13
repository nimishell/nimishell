/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:56:15 by wbae              #+#    #+#             */
/*   Updated: 2023/04/13 15:35:06 by yeongo           ###   ########.fr       */
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
# include "structure.h"
# include "debug.h" //DO NOT SUBMIT!!!

t_env		*g_env;

void		main_init(int ac, char *av[], char *envp[]);

void		set_sig(void);
void		sig_handler(int signal);

void		standard_error(int code);
void		print_error(char *str, int code);
void		cmd_error(char *str, int code);
void		syntax_error(char *str, int exit_code, int flag);

void		copy_env(char *env[]);
char		*copy_key(char *env);
char		*copy_value(char *envp);
void		making_env(char *envp);

void		*ft_free(void *p1, void *p2, void *p3, void *p4);
void		*ft_free_char_arr(char **p);
void		ft_free_token(t_token *token);

#endif
