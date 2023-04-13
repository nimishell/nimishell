/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:45:47 by wbae              #+#    #+#             */
/*   Updated: 2023/04/13 21:57:25 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef struct s_token		t_token;
typedef struct s_cmd		t_cmd;
typedef struct s_cmdlist	t_cmdlist;
typedef struct s_env		t_env;

struct s_token
{
	char	*str;
	char	*rd_line;
	int		type;
	t_token	*next;
};

struct s_cmd
{
	t_token	*token;
	int		size;
	int		type;
	int		infile_fd;
	char	*infile;
	int		outfile_fd;
	char	*outfile;
	char	syntax;
	t_cmd	*next;
	t_cmd	*prev;
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

enum e_token_type
{
	T_CHUNK = 11,
	T_ARGV = 22,
	T_PIPE = 33,
	T_SPACE = 44,
	T_RED = 50
};

enum e_io_type
{
	T_IO_R = 51,
	T_IO_RR,
	T_IO_L,
	T_IO_LL
};

#endif
