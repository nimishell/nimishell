/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:58:07 by wbae              #+#    #+#             */
/*   Updated: 2023/05/10 21:42:38 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "structure.h"

int		check_syntax(t_token *token);
void	remove_empty_space(t_token **lst);

int		parse(t_cmd **cmd, char *rd_line);
int		tokenize(t_token *token);
int		token_into_cmd(t_cmd **cmd, t_token *token);
void	treat_redir(t_cmd *cmd);

t_token	*token_add_back(t_token **lst, t_token *new);
void	cmd_add_back(t_cmd **lst, t_cmd *new);
void	redir_add_back(t_redir **lst, t_redir *new);
t_token	*remove_single_token(t_token **lst, t_token *target);

t_cmd	*new_cmd(void);

t_token	*new_token(char *str, int type);
void	make_split_to_token(t_token *lst, char **arr);
char	**split_quote(char *str);
void	split_by_parameter(t_token *token, char *param);
void	chunk_to_argv(t_token **lst);
void	join_argv_tokens(t_token **lst);
void	treat_heredoc(t_token *token, char *s);
void	treat_dollar(t_token *token);


#endif
