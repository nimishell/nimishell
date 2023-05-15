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

void	debug_print_cmd(t_cmd *cmd)
{
	t_cmd_node	*cur;
	t_redir		*in;
	t_redir		*out;
	int cnt = 0;
	int idx;

	cur = cmd->head;
	while (cur)
	{
		printf("--------cmd[%d]---------\n", cnt++);
		idx = 0;
		while (cur->argv[idx])
		{
			printf("%s\n", cur->argv[idx]);
			idx++;
		}
		in = cur->redir_in;
		out = cur->redir_out;
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
		cur = cur->next;
	}
	printf("\n\n======================output=======================\n");
}
