#include <minishell.h>

void	ms_init_history(t_ms *ms)
{
	int		fd;
	char	*line;
	char	*path;

	ms->p.history_i = 1;
	path = ft_printf_to_var("/home/%s/.bash_history", find_env_value(ms, "USER"));
	fd = open(path, O_RDONLY);
	//ms->p.history = malloc(sizeof(struct s_history));
	ms->p.history = malloc(sizeof(struct s_history));
	ms->p.history->next = NULL;
	ms->p.history->prev = NULL;
	line = get_next_line(fd);
	ms->p.history->line = line;
	ms->p.history->index = ms->p.history_i;
	while (line)
	{
		line = get_next_line(fd);
		if (line)
			ms_add_history(ms, line);
		//ft_printf(" *%s* ", line);
		//envp_splitted = ft_split(envp[i], '='); //alterar para o parse_env
		//if (envp_splitted[0] != NULL && envp_splitted[1] != NULL)
		//ft_free_ptr((void *) &line);
	}
}
