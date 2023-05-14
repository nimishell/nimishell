/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:45:47 by wbae              #+#    #+#             */
/*   Updated: 2023/05/14 20:59:17 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

# include <sys/types.h>

# define MINISHELL "\033[0;32mMINISHELL$\033[0m "
# define EXIT_SIGNAL 128

typedef struct termios		t_termios;
typedef struct s_token		t_token;
typedef struct s_cmd		t_cmd;
typedef struct s_cmd_node	t_cmd_node;
typedef struct s_env		t_env;
typedef struct s_env_node	t_env_node;
typedef struct s_redir		t_redir;

t_env						g_env;

struct s_token
{
	char	*str;
	int		type;
	t_token	*next;
};

struct s_cmd
{
	int			size;
	t_cmd_node	*head;
	t_cmd_node	*tail;
};

struct s_cmd_node
{
	char		**argv;
	int			fds[2];
	pid_t		pid;
	t_redir		*redir_in;
	t_redir		*redir_out;
	t_cmd_node	*next;
	t_cmd_node	*prev;
};

struct s_env
{
	int			key_count;
	int			value_count;
	int			status;
	t_env_node	*head;
	t_env_node	*tail;
};

struct s_env_node
{
	char		*key;
	char		*value;
	int			is_value;
	t_env_node	*next;
};

struct s_redir
{
	pid_t	pid;
	int		type;
	int		fd;
	char	*file;
	t_redir	*next;
};

enum e_token_type
{
	T_CHUNK = 11,
	T_ARGV = 22,
	T_SPACE = 33,
	T_PIPE = 44,
	T_REDIR = 50
};

enum e_io_type
{
	T_IO_R = 51,
	T_IO_RR,
	T_IO_L,
	T_IO_LL
};

enum e_file_io
{
	INPUT,
	OUTPUT
};

enum e_pipe
{
	RD,
	WR
};

enum e_bool
{
	FALSE,
	TRUE
};

enum e_result
{
	FAIL,
	SUCCESS
};

enum e_signal
{
	DEFAULT,
	IGNORE,
	CUSTOM,
	HEREDOC
};

#endif
