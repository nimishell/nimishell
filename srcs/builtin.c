/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:42:07 by wbae              #+#    #+#             */
/*   Updated: 2023/04/12 22:49:12 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <sys/param.h>
#include <unistd.h>

int	ft_cd(t_token *token)
{
	char	*dir;

	if (token->next == NULL)
		dir = "/Users/yeongo";
	else
		dir = token->next->str;
	chdir(dir);
	return (0);
}

int	ft_echo(t_token *token)
{
	int	followd_new_line;

	followd_new_line = 1;
	token = token->next;
	if (token != NULL
		&& ft_strncmp(token->str, "-n", 3) == 0)
	{
		followd_new_line = 0;
		token = token->next;
	}
	while (token != NULL)
	{
		ft_putstr_fd(token->str, 1);
		token = token->next;
	}
	if (followd_new_line == 1)
		ft_putchar_fd('\n', 1);
	return (0);
}

int	ft_env(t_token *token);
int	ft_unset(t_token *token);

int	ft_pwd(t_token *token)
{
	t_token	*next_token;
	char	working_path[MAXPATHLEN];

	next_token = token->next;
	if (next_token != NULL)
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		return (1);
	}
	getcwd(working_path, MAXPATHLEN);
	ft_putstr_fd(working_path, 1);
	return (0);
}

int	ft_export(t_token *token);
int	ft_exit(t_token *token);

int	is_builtin(t_token *token)
{
	char	*str;
	int		result;

	str = token->str;
	if (ft_strncmp(str, "cd", 3) == 0)
		result = ft_cd(token);
	else if (ft_strncmp(str, "echo", 5) == 0)
		result = ft_echo(token);
	else if (ft_strncmp(str, "env", 4) == 0)
		result = ft_env(token);
	else if (ft_strncmp(str, "unset", 6) == 0)
		result = ft_unset(token);
	else if (ft_strncmp(str, "pwd", 4) == 0)
		result = ft_pwd(token);
	else if (ft_strncmp(str, "export", 7) == 0)
		result = ft_export(token);
	else if (ft_strncmp(str, "exit", 5) == 0)
		result = ft_exit(token);
	else
		result = 1;
	return (result);
}
