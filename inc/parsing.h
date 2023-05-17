/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:58:07 by wbae              #+#    #+#             */
/*   Updated: 2023/05/15 15:21:56 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "structure.h"

int			parse(t_cmd *cmd, char *rd_line);

int			tokenize(t_token *token);
int			treat_heredoc(t_token *token);
int			split_by_quote(t_token *token);
void		make_split_to_token(t_token *lst, char **arr);
void		translate_dollar(char **str);
void		treat_dollar_in_chunk(t_token *token);

void		split_by_parameter(t_token *token, char *param);

void		chunk_to_argv(t_token **lst);
void		join_argv_tokens(t_token **lst);
void		remove_empty_space(t_token **lst);
int			check_syntax(t_token *token);

int			token_to_cmd(t_cmd *cmd, t_token *token);
void		treat_redir(t_cmd_node *node);

#endif
