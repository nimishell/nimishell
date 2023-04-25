#include <stdio.h>
#include "debug.h"

void	debug_print_tokens(t_token *token)
{
	printf("================tokens================\n[ ");
	while (token)
	{
		printf("{%s} (%d)", token->str, token->type);
		token = token->next;
		if (!token)
			break ;
		printf(", ");
	}
	printf(" ]\n");
}

void	debug_print_cmd(t_cmd *cmd)
{
	int cnt = 0;
	t_token *cur;

	while (cmd)
	{
		printf("--------cmd[%d]---------\n", cnt++);
		printf("size : %d\n", cmd->size);
		cur = cmd->token;
		while (cur)
		{
			printf("%s\n", cur->str);
			cur = cur->next;
		}
		cmd = cmd->next;
	}
}
