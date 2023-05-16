/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbae <wbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 21:42:06 by yeongo            #+#    #+#             */
/*   Updated: 2023/05/16 22:58:28 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structure.h"
#include "error.h"
#include <sys/fcntl.h>

void	remove_redir(t_redir **redir)
{
	t_redir	*cur;

	cur = *redir;
	while (cur != NULL)
	{
		if (cur->next != NULL && cur->fd != -1)
			close(cur->fd);
		ft_free_str(&cur->file);
		*redir = cur->next;
		free(cur);
		cur = *redir;
	}
}

void	open_infile(t_cmd_node *cmd)
{
	t_redir	*cur;

	cur = cmd->redir_in;
	if (cur == NULL)
		return ;
	while (cur != NULL)
	{
		if (cur->type == T_IO_L)
		{
			cur->fd = open(cur->file, O_RDONLY);
			if (cur->fd == -1)
				exit_with_errno(NULL, cur->file, EXIT_FAILURE);
		}
		if (cur->next == NULL)
			break ;
		cur = cur->next;
	}
	cmd->fds[INPUT] = cur->fd;
	remove_redir(&cmd->redir_in);
}

void	open_outfile(t_cmd_node *node, int pipe_fd[2])
{
	t_redir	*cur;

	if (pipe_fd != NULL && node->next != NULL)
		node->fds[OUTPUT] = pipe_fd[WR];
	cur = node->redir_out;
	if (cur == NULL)
		return ;
	while (cur != NULL)
	{
		if (cur->type == T_IO_R)
			cur->fd = open(cur->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (cur->type == T_IO_RR)
			cur->fd = open(cur->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (cur->fd == -1)
			exit_with_errno(NULL, cur->file, EXIT_FAILURE);
		if (cur->next == NULL)
			break ;
		cur = cur->next;
	}
	node->fds[OUTPUT] = cur->fd;
	remove_redir(&node->redir_out);
}

void	close_unused_fd(t_cmd_node *cmd, int pipe_fd[2])
{
	close(pipe_fd[RD]);
	if (!(cmd->prev == NULL && cmd->fds[INPUT] == STDIN_FILENO))
	{
		dup2(cmd->fds[INPUT], STDIN_FILENO);
		close(cmd->fds[INPUT]);
	}
	if (!(cmd->next == NULL && cmd->fds[OUTPUT] == STDOUT_FILENO))
	{
		dup2(cmd->fds[OUTPUT], STDOUT_FILENO);
		close(cmd->fds[OUTPUT]);
	}
	if (cmd->fds[OUTPUT] != pipe_fd[WR])
		close(pipe_fd[WR]);
}
