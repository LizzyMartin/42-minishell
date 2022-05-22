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
	int					std_in;
	int					std_out;
	int					exit_status;
	char				*error_msg;
}	t_cmd;

// env
typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
	struct s_env		*prev;
}	t_env;

// h
typedef struct s_h
{
	int						index;
	char					*line;
	struct s_h				*next;
	struct s_h				*prev;
}	t_h;

// prompt
typedef struct s_prompt
{
	char				*rl_p;
	int					cmds_size;
	char				*line;
	char				**line_splited;
	t_cmd				*cmds;
	t_env				*envs;
	t_h					*h;
}	t_p;

// ms
typedef struct s_minishell
{
	int					exit_code;
	int					argc;
	char				**argv;
	char				**envp;
	t_p					p;
}	t_ms;
