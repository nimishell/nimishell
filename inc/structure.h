/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:45:47 by wbae              #+#    #+#             */
/*   Updated: 2023/05/02 21:27:50 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

# include <sys/types.h>

# define MINISHELL "\033[0;32mMINISHELL$\033[0m "
# define EXIT_SIGNAL 128

typedef struct s_token		t_token;
typedef struct s_cmd		t_cmd;
typedef struct s_env		t_env;
typedef struct s_process	t_process;
typedef struct s_file		t_file;
typedef struct s_redir		t_redir;

struct s_token
{
	char	*str;
	int		type;
	t_token	*next;
};

struct s_cmd
{
	char	**argv;
	int		fd[2];
	pid_t	pid;
	t_redir	*redir;
	t_cmd	*next;
	t_cmd	*prev;
};

struct s_env
{
	char	*key;
	char	*value;
	int		is_value;
	int		status;
	t_env	*next;
};

struct s_redir
{
	int		type;
	char	*file;
	t_redir	*next;
};

enum e_token_type
{
	T_CHUNK = 11,
	T_ECHUNK = 22,
	T_ARGV = 33,
	T_SPACE = 44,
	T_PIPE = 55,
	T_REDIR = 60
};

enum e_io_type
{
	T_IO_R = 61,
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

#endif
