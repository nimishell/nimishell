/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:49:14 by wbae              #+#    #+#             */
/*   Updated: 2023/05/15 14:49:37 by wbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_H
# define ENVP_H

char	*split_key(char *envp);
char	*split_value(char *envp);
int		add_new_env(char *key, char *value);
void	get_env_lst(char **env);
char	*find_value(char *key);

#endif
