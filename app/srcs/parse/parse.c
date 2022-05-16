#include <minishell.h>

int	check_if_is_builtin(t_ms *ms)
{
	return (ms->exit_status);
}


int	parse(t_ms *ms)
{
	ms->line_splited = ft_split(ms->line, ' ');
	//check_if_is_builtin();
	return (0);
}
