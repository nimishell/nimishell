/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:59:18 by yeongo            #+#    #+#             */
/*   Updated: 2023/04/21 16:07:09 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

int	ft_echo(char *path, char **argv);
int	ft_cd(char *path, char **argv);
int	ft_pwd(char *path, char **argv);
int	ft_env(char *path, char **argv);
int	ft_export(char *path, char **argv);
int	ft_unset(char *path, char **argv);
int	ft_exit(char *path, char **argv);

#endif
