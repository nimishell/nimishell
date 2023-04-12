/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:45:47 by wbae              #+#    #+#             */
/*   Updated: 2023/04/12 20:34:17 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

enum e_token_type
{
	T_CHUNK = 11,
	T_ARGV = 22,
	T_SPACE = 33,
	T_PIPE = 44,
	T_RED = 50
};

enum e_io_type
{
	T_IO_R = 51,
	T_IO_RR,
	T_IO_L,
	T_IO_LL
};

typedef struct s_token
{
	char			*str;
	char			*rd_line;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	t_token			*token;
	int				size;
	int				type;
	int				input;
	int				output;
	char			syntax;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_cmdlist
{
	struct s_cmd	*cmd_list;
	struct s_cmd	*cmd_list_tail;
}	t_cmdlist;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				status;
	struct s_env	*next;
}	t_env;

#endif
