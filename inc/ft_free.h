/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:56:15 by wbae              #+#    #+#             */
/*   Updated: 2023/05/15 16:53:38 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FREE_H
# define FT_FREE_H

# include "structure.h"

void	ft_free_cmd(t_cmd *cmd, t_cmd_node *node);
void	ft_free_env(t_env_node *node);
void	ft_free_redir(t_redir *remove);
void	ft_free_token(t_token *remove);
void	*ft_free_ptrs(char *p1, char *p2, char *p3);

#endif
