/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:45:47 by wbae              #+#    #+#             */
/*   Updated: 2023/04/24 15:40:51 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

# include <sys/types.h>

# define EXIT_SIGNAL 128

typedef struct s_token		t_token;
typedef struct s_cmd		t_cmd;
typedef struct s_cmdlist	t_cmdlist;
typedef struct s_env		t_env;
typedef struct s_process	t_process;
typedef struct s_file_fd	t_file_fd;

struct s_token
{
	char	*str;
	int		type;
	t_token	*next;
};

struct s_cmd
{
	t_token		*token;
	char		*str;
	int			size;
	int			type;
	char		syntax;
	pid_t		pid;
	int			redir[2];
	t_file_fd	*file_fd;
	t_cmd		*next;
	t_cmd		*prev;
};

struct s_cmdlist
{
	t_cmd	*cmd_list;
	t_cmd	*cmd_list_tail;
};

struct s_env
{
	char	*key;
	char	*value;
	int		status;
	t_env	*next;
};

struct s_process
{
};

struct s_file_fd
{
	int		pipe[2];
	int		infile_fd;
	int		outfile_fd;
	char	*infile;
	char	*outfile;
};

enum e_token_type
{
	T_CHUNK = 11,
	T_ECHUNK = 22,
	T_ARGV = 33,
	T_PIPE = 44,
	T_SPACE = 55,
	T_REDIR = 60
};

enum e_io_type
{
	T_IO_R = 61,
	T_IO_RR,
	T_IO_L,
	T_IO_LL
};

enum e_pipe
{
	RD,
	WR
};

enum e_redir
{
	INPUT,
	OUTPUT
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
