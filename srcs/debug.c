#include <stdio.h>
#include "debug.h"

void	debug_print_tokens(t_token *token)
{
	printf("\n================tokens================\n[ ");
	while (token)
	{
		printf("{%s} (%d)", token->str, token->type);
		token = token->next;
		if (!token)
			break ;
		printf(", ");
	}
	printf(" ]\n\n");
}

void	debug_print_cmd(t_cmd *cmd)
{
	t_redir	*cur;
	int cnt = 0;
	int idx;

	while (cmd)
	{
		printf("--------cmd[%d]---------\n", cnt++);
		idx = 0;
		while (cmd->argv[idx])
		{
			printf("%s\n", cmd->argv[idx]);
			idx++;
		}
		cur = cmd->redir;
		while (cur)
		{
			printf("redir_type : %d\nredir_file : %s\n", cur->type, cur->file);
			cur = cur->next;
		}
		// printf("input: %s, input_fd: %d\n", cmd->file->infile, cmd->file->infile_fd);
		// printf("output: %s, output_fd %d\n\n", cmd->file->outfile, cmd->file->outfile_fd);
		// printf("redir_in: %d\n", cmd->redir[INPUT]);
		// printf("redir_out: %d\n\n", cmd->redir[OUTPUT]);
		cmd = cmd->next;
	}
}
