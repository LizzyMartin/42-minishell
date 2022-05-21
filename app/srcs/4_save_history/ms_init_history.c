#include <minishell.h>

void	ms_init_history(t_ms *ms)
{
	ms->h = (t_cmd *) malloc(sizeof(t_cmd));
	
}
