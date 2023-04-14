/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:58:07 by wbae              #+#    #+#             */
/*   Updated: 2023/04/14 17:26:35 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "structure.h"

int			check_quote(char *line);
char		**split_quote(char *str);
char		**seperate_array_quote(char *str, int start, int end);
void		tokenize_quote(t_token *ret);

void		tokenize_space(t_token *tokens);
void		split_space(t_token *token, char *str);

void		tokenize_pipe(t_token *token);
void		split_pipe(t_token *token, char *str);

void		tokenize_redirection(t_token *token);
void		before_split_io(t_token *token, char *str);
void		split_io(t_token *token, char *s, int idx, int flag);
void		change_type_red(t_token *token);

void		remove_empty_token(t_token **lst);

int			parse(t_cmd *cmd, char *rd_line);
t_token		*tokenize(char *rd_line);

t_token		*make_new_token(void);
t_token		*add_token(t_token **tokens, int idx, int type, char *str);
t_token		*add_back_token(t_token **tokens, int idx, t_token *new);

char		*ft_strsep(char **str, const char *target);
#endif
