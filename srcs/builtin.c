/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:42:07 by wbae              #+#    #+#             */
/*   Updated: 2023/04/12 20:21:54 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	ft_cd(t_token *token);

int	ft_echo(t_token *token)
{
	int	is_option;

	is_option = 0;
	token = token->next;
	if (token != NULL
		&& ft_strncmp(token->str, "-n", 3) == 0)
	{
		is_option = 1;
		token = token->next;
	}
	while (token != NULL)
	{
		ft_putstr_fd(token->str, 1);
		token = token->next;
	}
	if (is_option == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}

int	ft_env(t_token *token);
int	ft_unset(t_token *token);
int	ft_pwd(t_token *token);
int	ft_export(t_token *token);
int	ft_exit(t_token *token);

void	is_builtin(t_token *token)
{
	char	*str;

	str = token->str;
	if (ft_strncmp(str, "cd", 3) == 0)
		ft_cd(token);
	else if (ft_strncmp(str, "echo", 5) == 0)
		ft_echo(token);
	else if (ft_strncmp(str, "env", 4) == 0)
		ft_env(token);
	else if (ft_strncmp(str, "unset", 6) == 0)
		ft_unset(token);
	else if (ft_strncmp(str, "pwd", 4) == 0)
		ft_pwd(token);
	else if (ft_strncmp(str, "export", 7) == 0)
		ft_export(token);
	else if (ft_strncmp(str, "exit", 5) == 0)
		ft_exit(token);
}
