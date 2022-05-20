#include <minishell.h>

int	ms_parse(t_ms *ms)
{
	ms->p.line_splited = ft_split(ms->p.line, ' ');
	ms->p.cmds = (t_cmd *) malloc(sizeof(t_cmd));
	ms->p.cmds->name = ms->p.line_splited[0];
	ms->p.cmds->index = 0;
	ms->p.cmds_size = ft_mtx_size((void **) ms->p.line_splited);
	ms->p.cmds->name_and_path = NULL;
	ms->p.cmds->cmd_splited = NULL;
	ms->p.cmds->std_in = open(ms->p.line_splited[1], O_RDONLY);
	//ms->p.cmds->std_out = open("saida.txt", O_CREAT | O_WRONLY | O_APPEND, 0777);
	ms->p.cmds_size = 1;
	ms_prepare_command(ms);
	return (0);
}
