/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:58:07 by wbae              #+#    #+#             */
/*   Updated: 2023/05/14 18:47:35 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "structure.h"

int			parse(t_cmd *cmd, char *rd_line);
int			tokenize(t_token *token);
void		treat_heredoc(t_token *token, char *s);
char		**split_quote(char *str);
void		treat_dollar(t_token *token);
void		split_by_parameter(t_token *token, char *param);
void		chunk_to_argv(t_token **lst);
void		join_argv_tokens(t_token **lst);
void		remove_empty_space(t_token **lst);
int			check_syntax(t_token *token);
int			token_into_cmd(t_cmd *cmd, t_token *token);
void		treat_redir(t_cmd_node *node);

t_token		*new_token(char *str, int type);
// t_token		*token_add_back(t_token **lst, t_token *new);
t_token		*remove_single_token(t_token **lst, t_token *target);
void		make_split_to_token(t_token *lst, char **arr);
// void		cmd_add_back(t_cmd_node **lst, t_cmd_node *new);
void		redir_add_back(t_redir **lst, t_redir *new);
#endif
