
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
