/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:59:18 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/14 21:45:18 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

int	ft_echo(char **argv);
int	ft_cd(char **argv);
int	ft_pwd(void);
int	ft_env(char **argv);
int	export_variable(char **key, char *value);
int	ft_export(char **argv);
int	ft_unset(char **argv);
int	ft_exit(char **argv);

#endif
