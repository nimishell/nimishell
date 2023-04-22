/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 21:44:27 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/22 21:45:11 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPEN_FILE_H
# define OPEN_FILE_H

# include "structure.h"

void	open_infile(t_file_fd *file_fd, int redir[2]);
void	open_outfile(t_file_fd *file_fd, int redir[2]);

#endif
