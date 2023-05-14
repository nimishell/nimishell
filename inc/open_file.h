/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 21:44:27 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/13 21:30:39 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPEN_FILE_H
# define OPEN_FILE_H

# include "structure.h"

int		get_heredoc(char *limiter);
void	open_infile(t_cmd_node *cmd);
void	open_outfile(t_cmd_node *cmd, int pipe_fd[2]);
void	close_unused_fd(t_cmd_node *cmd, int pipe_fd[2]);

#endif
