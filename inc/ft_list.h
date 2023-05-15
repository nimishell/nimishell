/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 14:41:39 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/15 16:49:53 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIST_H
# define FT_LIST_H

# include "structure.h"

t_cmd_node	*cmd_new(void);
t_env_node	*env_new(void);
t_redir		*redir_new(void);
t_token		*token_new(char *str, int type);

t_env_node	*env_last(void);
t_redir		*redir_last(t_redir *redir);
t_token		*token_last(t_token *token);

void		cmd_add_back(t_cmd *cmd, t_cmd_node *new);
void		env_add_back(t_env_node *new);
void		redir_add_back(t_redir **redir, t_redir *new);
void		token_add_back(t_token **token, t_token *new);

void		cmd_remove_back(t_cmd *cmd);
void		env_remove_if(t_env_node *target);
void		token_remove_if(t_token **token, t_token *target);

void		cmd_clear(t_cmd *cmd);
void		env_clear(void);
void		redir_clear(t_redir **redir);
void		token_clear(t_token **token);

#endif
