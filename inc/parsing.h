/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:58:07 by wbae              #+#    #+#             */
/*   Updated: 2023/04/16 21:46:16 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "structure.h"

int			ft_issep(char c, char const *sep);
int			split_squote(t_token **token, char **rd_line, t_token *new);
int			split_dquote(t_token **token, char **rd_line, t_token *new);
int			split_pipe(t_token **token, char **rd_line, t_token *new);
int			split_redir(t_token **token, char **rd_line, t_token *new, char redir_char);
int			split_space(t_token **token, char **rd_line, t_token *new);
int			split_str(t_token **token, char **rd_line, t_token *new);
int			ft_split_token(t_token **token_head, char *rd_line);

void		remove_empty_token(t_token **lst);
void		translate_dollar(t_token *token, t_env *g_env);

int			parse(t_cmd *cmd, char *rd_line);
int			tokenize(t_token *token, char *rd_line);

void		token_clear(t_token **token);
void		token_add_back(t_token **lst, t_token *new);
#endif
