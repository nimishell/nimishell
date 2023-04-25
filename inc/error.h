/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 21:25:59 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/25 20:45:34 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

void	ft_perror(char *cmd, char *arg);
void	exit_with_errno(char *cmd, char *arg, int status);
void	exit_with_message(char *cmd, char *arg, char *messsage, int status);
void	ft_error_message(char *cmd, char *arg, char *message);
void	ft_syntax_error(char *message, int status, int flag);

#endif
