#include <minishell.h>

int	ms_export(t_ms *ms)
{
	char *key;
	char *value;

	key = ms->p.line_splited[1]; //pegar pelo valor do tokenizer depois
	value = ms->p.line_splited[2];
	add_env(ms, key, value);
	ms->p.cmds->exit_status = 0;
	return (ms->p.cmds->exit_status);
}
