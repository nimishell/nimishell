/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:23:25 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/15 16:27:12 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_PROCESS_H
# define EXECUTE_PROCESS_H

# include "structure.h"

int		is_single_builtin(t_cmd_node *cmd);
void	execute_single_process(t_cmd *cmd);
int		wait_child_process(int count, pid_t last_pid);
void	execute_multi_process(t_cmd *cmd);

#endif
