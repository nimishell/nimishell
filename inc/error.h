/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 21:25:59 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/20 22:00:34 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

void	ft_perror(char *cmd, char *arg);
void	exit_with_perror(char *cmd, char *arg, int status);
void	exit_with_message(char *cmd, char *arg, char *messsage, int status);
void	syntax_error(char *message, int status, int flag);

#endif
