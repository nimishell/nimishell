/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:58:07 by wbae              #+#    #+#             */
/*   Updated: 2023/04/24 15:44:30 by yeongo           ###   ########.fr       */
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

void	remove_empty_token(t_token **lst);
void	check_special(t_token *token);

void	treat_dollar(t_token *token);
char	*translate_dollar(t_env *head, char **str);
char	**split_dollar(char *str);

int		parse(t_cmd *cmd, char *rd_line);
t_token	*tokenize(t_token *token, char *rd_line);
void	token_to_command(t_token *token, t_cmd *cmd);
int		classify_token(t_token *token);

void	token_clear(t_token **token);
void	token_add_back(t_token **lst, t_token *new);
#endif
