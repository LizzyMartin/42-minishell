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

// history
typedef struct s_history
{
	int					index;
	char				*line;
	struct s_history	*next;
	struct s_history	*prev;
}	t_history;


// prompt
typedef struct s_prompt
{
	char				*rl_p;
	int					cmds_size;
	char				*line;
	char				**line_splited;
	t_cmd				*cmds;
	t_env				*envs;
	int					history_i;
	t_history			*history;
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
