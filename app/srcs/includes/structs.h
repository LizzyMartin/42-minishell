/* structs */

typedef struct s_minishell
{
	int		argc;
	char	**argv;
	char	**envp;
	char	*prompt;
	int		exit_status;
	char	*line;
	char	**line_splited;
	int		args_size;
} t_ms;
