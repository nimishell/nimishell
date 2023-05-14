#include <stdio.h>
#include "debug.h"

void	debug_print_tokens(t_token *token)
{
	printf("\n================tokens================\n[ ");
	while (token)
	{
		printf("{%s} (%d)<%p>", token->str, token->type, token);
		token = token->next;
		if (!token)
			break ;
		printf(", ");
	}
	printf(" ]\n\n");
}

void	debug_print_cmd(t_cmd_node *cmd)
{
	t_redir	*in;
	t_redir	*out;
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
		in = cmd->redir_in;
		out = cmd->redir_out;
		while (in || out)
		{
			if (in)
			{
				printf("in_type : %d\nfile : %s\n", in->type, in->file);
				in = in->next;
			}
			if (out)
			{
				printf("out_type : %d\nfile : %s\n", out->type, out->file);
				out = out->next;
			}
		}
		cmd = cmd->next;
	}
	printf("\n\n======================output=======================\n");
}
