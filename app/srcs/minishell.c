#include <minishell.h>

void	minishell(t_ms *ms)
{
	ms_read_input(ms);
//	ms_save_history(ms);
	ms_tokenizer(ms);
	if (ms_parse(ms))
		ms_execute(ms);
	ms_clear(ms);
}
