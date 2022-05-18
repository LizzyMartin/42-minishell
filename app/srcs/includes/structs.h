/* structs */

// cmds
typedef struct s_cmd
{
	int					index;
	char				*name;
	char				*name_and_path;
	char				**cmd_splited;
	struct s_cmd		*prev;
	struct s_cmd		*next;
	int					exit_status;
	int					std_in;
	int					std_out;
}	t_cmd;

// env
typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}	t_env;

// prompt
typedef struct s_prompt
{
	char				*rl_p;
	int					cmds_size;
	char				*line;
	char				**line_splited;
	t_cmd				*cmds;
	t_env				*envs;
}	t_p;

// ms
typedef struct s_minishell
{
	int					argc;
	char				**argv;
	char				**envp;
	t_p					p;
}	t_ms;
