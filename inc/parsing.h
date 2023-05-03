/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:58:07 by wbae              #+#    #+#             */
/*   Updated: 2023/05/03 19:16:22 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "structure.h"

int		ft_issep(char c, char const *sep);
int		split_squote(t_token **token, char **rd_line, t_token *new);
int		split_dquote(t_token **token, char **rd_line, t_token *new);
int		split_pipe(t_token **token, char **rd_line, t_token *new);
int		split_redir(t_token **token, char **rd_line, t_token *new, char rd);
int		split_space(t_token **token, char **rd_line, t_token *new);
int		split_str(t_token **token, char **rd_line, t_token *new);
int		ft_split_token(t_token **token_head, char *rd_line);

int		check_syntax(t_token *token);
void	remove_empty_space(t_token **lst);
void	check_heredoc_delimiter(t_token *token);
void	treat_dollar(t_token *token);

int		parse(t_cmd **cmd, char *rd_line);
t_token	*tokenize(t_token *token, char *rd_line);
char	**token_to_command(t_token *token);
int		token_into_cmd(t_cmd **cmd, t_token *token);
void	treat_redir(t_cmd *cmd);

void	token_add_back(t_token **lst, t_token *new);
void	cmd_add_back(t_cmd **lst, t_cmd *new);
void	redir_add_back(t_redir **lst, t_redir *new);
void	remove_single_token(t_token **lst, t_token *target);

t_cmd	*new_cmd(void);

#endif
