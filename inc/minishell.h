/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:56:15 by wbae              #+#    #+#             */
/*   Updated: 2023/04/12 18:10:25 by wbae             ###   ########.fr       */
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
# include "../libft/libft.h"
# include "structure.h"

# include "debug.h" //DO NOT SUBMIT!!!

# define STDIN		0
# define STDOUT		1
# define STDERR		2
# define SYNTAX		4
# define T_CHUNK	11
# define T_ARGV		22
# define T_SPACE	33
# define T_PIPE		44
# define T_IO_R		51
# define T_IO_RR	52
# define T_IO_L		53
# define T_IO_LL	54

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

int			check_quote(char *line);
char		**split_quote(char *str);
char		**seperate_array_quote(char *str, int start, int end);
void		tokenize_quote(t_token *ret);

void		tokenize_space(t_token *tokens);
void		split_space(t_token *token);

void		tokenize_pipe(t_token *token);
void		sep_pipeline(t_token *token);
void		sub_pipeline(t_token *token);

void		tokenize_special(t_token *token);
void		split_str_io(t_token *token, char *str);
void		tokenize_io(t_token *token, char *s, int idx, int flag);

int			parse(t_cmd *cmd, char *rd_line);
t_token		*tokenize(char *rd_line);

t_token		*make_new_token(void);
t_token		*add_token(t_token **tokens, int idx, int type, char *str);
t_token		*add_back_token(t_token **tokens, int idx, t_token *new);

void		*ft_free(void *p1, void *p2, void *p3, void *p4);
void		*ft_free_char_arr(char **p);
void		ft_free_token(t_token *token);

#endif
