/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 21:44:27 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/15 13:57:56 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPEN_FILE_H
# define OPEN_FILE_H

# include "structure.h"

void	open_infile(t_cmd_node *cmd);
void	open_outfile(t_cmd_node *cmd, int pipe_fd[2]);
void	close_unused_fd(t_cmd_node *cmd, int pipe_fd[2]);

#endif
