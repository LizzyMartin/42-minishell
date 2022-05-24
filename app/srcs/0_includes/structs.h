/* structs */


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

// cmds
typedef struct s_cmd
{
	int					index;
	struct s_cmd		*prev;
	struct s_cmd		*next;

	char                *cmd_line;
	char				**cmd_splited_by_space;
	int					args_amount;

	char				*just_name;
	char				*path_and_name;
	char				**flags; 
	
	int					bridge_pipe[2];
	
	int					exit_code;
	char				*error_msg;
}	t_cmd;



/* prompt */
typedef struct s_prompt
{
	struct s_prompt			*prev;       // connectors &&,||
	struct s_prompt			*next;

	int                     has_here_doc;
	int 					only_here_doc;
	int						pipe_here_doc[2]; //input file or here_doc
	char					*hd_limiter;

	int						input_fd;
	char					*input_path;
	int						input_redirected_to_file;
	int						only_input_redirected_to_file;

	int						output_fd;   // output
	char					*output_path;
	int                     redirect;

	int						pipe_amount; // commands
	t_cmd					*cmds;

	int						aux_fd;
	
	char					*this_p_line;
	char					**this_p_line_splited_by_pipe;
	int                     args_amount;

}	t_p;

// ms
typedef struct s_minishell
{
	int					argc;
	char				**argv;
	char				**envp;

	int					history_i;
	t_history			*history;
	t_env				*envs;
	
	char				*shell_line;
	char				*shell_line_tokenized;
	char				**slt_splited_by_connectors;
	char				*readline_var;
	
	t_p					p;
	int					p_amount;

	int					exit_code;

}	t_ms;
