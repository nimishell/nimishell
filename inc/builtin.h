/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:59:18 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/26 02:19:20 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

int	ft_echo(char **argv);
int	ft_cd(char **argv);
int	ft_pwd(char **argv);
int	ft_env(char **argv);
int	ft_export(char **argv);
int	ft_unset(char **argv);
int	ft_exit(char **argv);

#endif
