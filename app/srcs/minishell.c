#include <minishell.h>

void	minishell(t_ms *ms)
{
	if (ms_read_input(ms) == 1)
	    return ;
	ms_add_history(ms, NULL);
	ms_tokenizer(ms);
	ms_parse(ms);
	ms_execute(ms);
}
