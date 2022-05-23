#include <minishell.h>

void	minishell(t_ms *ms)
{
	if (ms_read_input(ms) == 1)
	    return ;
	ms_add_history(ms, NULL);
	ms_tokenizer(ms);
	if (ms_parse(ms) == 0)
		ms_execute(ms);
}
