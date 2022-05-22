#include <minishell.h>

int	ms_parse(t_ms *ms)
{
	ms->p.line_splited = ft_split(ms->p.line, ' ');
	ms->p.cmds = (t_cmd *) malloc(sizeof(t_cmd));
	ms->p.cmds->name = ms->p.line_splited[0];
	ms->p.cmds->index = 0;
	ms->p.cmds->next = NULL;
	ms->p.cmds->prev = NULL;
	ms->p.cmds_size = ft_mtx_size((void **) ms->p.line_splited);
	ms->p.cmds->cmd_splited = NULL;
	ms->p.cmds->std_in = open(ms->p.line_splited[1], O_RDONLY);
	ms->p.cmds_size = 1;
	
	ms->p.cmds->name_and_path = append_path(ms->p.cmds, ms);
	// if (is_builtin(ms) == 0 && ms->p.cmds->name_and_path == NULL)
	// {
	// 	ft_printf("%s: %s\n", ms->p.cmds->name, ms->p.cmds->error_msg);
	// 	return (ms->p.cmds->exit_status);
	// }
	return (0);
}
