/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:31:58 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/12 21:31:09 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "structure.h"

int		has_heredoc(t_cmd *cmd);
void	execute_heredoc(t_cmd *cmd);

#endif
