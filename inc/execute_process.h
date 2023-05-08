/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:23:25 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/08 20:30:47 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_PROCESS_H
# define EXECUTE_PROCESS_H

# include "minishell.h"

int		is_single_builtin(t_cmd *cmd);
void	execute_single_process(t_cmd *cmd);
int		wait_child_process(int count, pid_t last_pid);
void	execute_multi_process(t_cmd *cmd);

#endif
