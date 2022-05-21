#include <minishell.h>

int	ms_export(t_ms *ms)
{
	char *key;
	char *value;
	char **cmd_env_splitted;

	cmd_env_splitted = ft_split(ms->p.line_splited[1], '=');
	key = cmd_env_splitted[0];
	value = cmd_env_splitted[1];
	add_env(ms, key, value);
	ms->p.cmds->exit_status = 0;
	return (ms->p.cmds->exit_status);
}
