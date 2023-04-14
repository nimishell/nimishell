/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 20:28:23 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/14 20:53:10 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TOKEN_H
# define FT_TOKEN_H

typedef struct s_token	t_token;

struct s_token
{
	char	*str;
	int		type;
	t_token	*next;
};

enum e_token_type
{
	T_CHUNK = 11,
	T_ECHUNK = 22,
	T_PIPE = 33,
	T_SPACE = 44,
	T_REDIR = 55
};

enum e_result
{
	FAIL,
	SUCCESS
};

#endif
