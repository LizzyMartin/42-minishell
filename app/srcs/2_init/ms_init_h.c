#include <minishell.h>

void	ms_init_h(t_ms *ms)
{
	int		fd;
	char	*line;
	char	*path;
	t_h   	*h;

	path = ft_printf_to_var("/home/%s/.bash_history", find_env_value(ms, "USER"));
	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
    h = ms->p.h;
	while (line)
	{
		if (h == NULL)
		{
			h = (t_h *) malloc(sizeof(t_h));
			h->index = 1;
			h->line = line;
			h->next = NULL;
			h->prev = NULL;
		}
		else
		{
			while (h->next) {
				h = h->next;
			}
			h->next = (t_h *) malloc(sizeof(t_h));
			//h->next->index = h->index + 1;
			h->next->line = "asdf";
			h->next->next = NULL;
			//h->next->prev = h;
		}
		line = get_next_line(fd);
	}
}
