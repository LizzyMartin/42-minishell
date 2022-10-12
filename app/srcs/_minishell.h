/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _minishell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 22:13:24 by acapela-          #+#    #+#             */
/*   Updated: 2022/10/11 22:08:13 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MINISHELL_H
# define _MINISHELL_H

/**************************************************************************** #
#                               INCLUDES                                      #
# ****************************************************************************/

// libft
# include           "1_libft/srcs/libft.h"

/**************************************************************************** #
#                                DESIGN                                       #
# ****************************************************************************/

# define YELLOW "\001\033[0;33m\002"
# define BOLD_YELLOW "\001\033[1;33m\002"
# define BLUE "\001\033[0;34m\002"
# define BOLD_BLUE "\001\033[1;34m\002"
# define BOLD_CYAN "\001\033[1;36m\002"
# define WHITE "\001\033[0;37m\002"
# define BOLD_WHITE "\001\033[1;37m\002"
# define END_COLOR "\001\033[0m\002"

# define SHELL_NAME "miniheaven ▸ "
# define SHELL SHELL_NAME

/**************************************************************************** #
#                              CONSTANTS                                      #
# ****************************************************************************/

// tokens
# define T_CONNECTOR    "__[BANANA0]__"
# define T_CONNECTOR_AND    "__[BANANA1]__"
# define T_CONNECTOR_OR     "__[BANANA12]__"
# define T_PIPE             "__[BANANA2]__"
# define T_SPACE            "__[BANANA3]__"
# define T_WILDCARD         "__[BANANA4]__"
# define T_SUBSHELL         "__[BANANA5]__"

// all errors
# define E_CMDNOTFOUND ": command not found"
# define E_BADSINTAX " syntax error near unexpected token "
# define E_NOTDIR ": No such file or directory\n"

// cd errors
# define EACCES "cd: permission denied\n"
# define ELOOP "cd: %s: too many levels of symbolic links\n"
# define ENAMETOOLONG "cd: file name too long\n"
# define ENOENT "cd: no such file or directory\n"
# define ENOTDIR "cd: not a directory\n"
# define EHNOTSET "miniheaven: cd: HOME not set\n"

// unset errors
# define EINVAL "unset: %s: invalid parameter name"

// export errors
# define EXINVAL "export: %s: not a valid identifier"

// exit errors
# define NUMERIC_ARG ": numeric argument required\n"
# define MANY_ARG "exit: too many arguments\n"

// here_doc errors
# define CTRL_D_HD "bash: warning: here-document \
at line 5 delimited by end-of-file (wanted `FIM')\n"

/**************************************************************************** #
#                                STRUCTS                                      #
# ****************************************************************************/

typedef struct s_file
{
	char			*name;
	int				cursor;
	struct s_file	*next;
	struct s_file	*prev;
}	t_file;

typedef struct s_free
{
	int				index;
	char			*buffer;
	struct s_free	*prev;
	struct s_free	*next;
}	t_free;

typedef struct s_sc
{
	int	cat_ls;
	int	reset_fd;
	int	cat;
	int	ls;
}	t_sc;

typedef struct s_qs
{
	struct s_free	*free_qs;
	void			*vt;
	void			*v3;
	void			*vr;
	void			*vl;
	int				last;
	int				mid;
	void			*v;
	int				size;
	int				left;
	int				right;
}	t_qs;

typedef struct s_env
{
	char					*key;
	char					*value;
	struct s_env			*next;
	struct s_env			*prev;
}	t_env;

typedef struct s_history
{
	int						index;
	char					*line;
	struct s_history		*next;
	struct s_history		*prev;
	int						l_c_exit_code;
}	t_history;

typedef struct s_cmd
{
	int						index;
	struct s_cmd			*prev;
	struct s_cmd			*next;
	char					*cmd_line;
	char					**cmd_splited_by_space;
	int						args_amount;
	char					*just_name;
	char					*path_and_name;
	char					**flags;
	int						exit_code;
	char					*error_msg;
	int						cmd_is_path_but_invalid;
	int						can_execute;
	int						subshell;
	int						input;
	int						output;
	int						pipe[2];
}	t_cmd;

typedef struct s_prompt
{
	struct s_prompt			*prev;
	struct s_prompt			*next;
	int						has_here_doc;
	int						only_here_doc;
	int						pipe_here_doc[2];
	char					*hd_limiter;
	int						input_fd;
	char					*input_path;
	int						input_redirected_to_file;
	int						only_input_redirected_to_file;
	int						only_redirect_to_file;
	int						no_cmd_just_redirect;
	int						dont_execute_first;
	int						pipe[2];
	int						output_fd;
	char					*output_path;
	int						redirect;
	int						pipe_amount;
	t_cmd					*cmds;
	int						aux_fd;
	char					*this_p_line;
	char					**this_p_line_splited_by_pipe;
	int						args_amount;
	int						mtx_free;
	t_sc					*sc;
}	t_p;

typedef struct s_minishell
{
	int						argc;
	char					**argv;
	char					**envp;
	int						*connectors_order;
	int						connectors_index;
	int						connectors_amount;
	char					*shell_line;
	char					*shell_line_tokenized;
	char					**slt_splited_by_connectors;
	char					*sh_name;
	char					*readline_var;
	int						p_amount;
	int						has_double_quotes;
	int						has_single_quotes;
	t_p						*p;
	int						exit_code;
	int						history_i;
	t_history				*history;
	t_env					*envs;
	t_env					*aux_envs;
	int						is_aux_env;
	char					*tmp;
	char					*tmp2;
	char					*tmp3;
	char					**tmp4;
	int						*tmp5;
	char					*aux;
	int						i;
	char					**str_export;
	t_qs					*qs;
	int						here_doc_open;
	int						here_document;
	int						input_command_open;
	int						is_cat_sequence;
	int						fake_cat_input;
	int						no_path;
	struct s_minishell		*subs;
	int						n_subs;
	int						i_subs;
}	t_ms;

/**************************************************************************** #
#                             PROTOTYPES                                      #
# ****************************************************************************/

// Global points to ms struct, so we can easily free ms when signal is called
extern t_ms	*g_ms;

/* design */
void		print_banner(void);
char		*ms_print_sh_name(void);

/* init */
void		ms_init(t_ms *ms, int argc, char **argv, char **envp);

// env
void		ms_init_env(t_ms *ms);
void		ms_add_env(t_env **env, char *key, char *value);
void		ms_delete_env(t_ms *ms, char *key);
char		*ms_find_env_value(t_ms *ms, char *key);
void		ms_free_env(t_env *envs);
int			ms_is_in_env(t_ms *ms, const char *key);
int			update_env_value(t_env *env, char *key, char *value);
t_env		*ms_last_env(t_env *env);

// history
t_history	*ms_last_history(t_history *history);
void		ms_free_history(t_ms *ms);

/* read_input */
int			ms_read_input(t_ms *ms);
int			ms_here_doc(t_ms *ms, t_p *p, int *hdoc);

// signals
void		ms_init_signal_detection(void);
void		ctrl_c_redisplay_prompt(int sig, siginfo_t *siginfo, void *context);
void		ctrl_d_exit_shell(int sig, siginfo_t *siginfo, void *context);

/* history */
void		ms_init_history(t_ms *ms);
void		ms_add_history(t_ms *ms, char *line);
void		ms_print_history(t_ms *ms, t_cmd *current_cmd, t_p *prompt);

/* tokenizer */
void		ms_switch_subshell_output(t_ms *ms);
int			ms_execute_prompt_in_subshell(t_ms *ms, t_p *curr_prompt,
				int *exit_code);
void		ms_parse_subshells(t_ms *ms);
int			execv_in_sub_shell(t_cmd **current_cmd, \
t_p *curr_prompt, t_ms *ms);
int			ms_sintax(t_ms *ms);
int			ms_tokenizer(t_ms *ms);
void		ms_wildcard(t_ms *ms);
void		ms_check_quotes(t_ms *ms);
int			ms_get_index(t_ms *ms, int size, char **cmd);
int			ms_check_if_have_quotes(t_ms *ms, char *line);
int			get_index_before_space(t_ms *ms, int size, char **cmd);
int			get_boolean(const char *wildcard, const struct dirent *de, int all);
void		update_tmp(char **replace, DIR *dr, struct dirent **de, char **tmp);
void		ms_expand_dolar(t_ms *ms);
void		threat_dolar(t_ms *ms,
				char **line_splited, int i, char *dolar_cmd);
void		ms_has_single_quotes(t_ms *ms, \
char *dolar_cmd, char *line, int threated);
int			ms_jump_to_end_quote(t_ms *ms, char *line, int *i, int size);
void		subs_replace_join_free(char *find, char *replace, \
t_ms *ms, char *line);
int			ms_count_char(char *str, char c);
int			valid_chr(char chr);
void		ms_quotes_vs_connectors(t_ms *ms, char *line);
void		ms_check_quotes_aux(t_ms *ms, char **cmd, char *tmp, char *aux);
void		ms_replace_connectors_by_token(t_ms *ms, char *tmp);
void		print_lst(t_file *head);
void		ms_free_files(t_file **files);
t_file		*ms_get_current_directory(void);
void		ms_file_delete(t_file **head);
void		ms_go_start(t_file **files);
void		update_exit_code_last_cmd(t_ms *ms, t_cmd *cmds, int code);

/* parse */
int			ms_parse(t_ms *ms);

t_p			*parse_prompts(t_ms *ms);
t_p			*ms_get_prompt(t_ms *ms, t_p *curr_prompt, int i);

char		**ms_parse_input(t_p *curr_prompt);
char		**ms_parse_output(t_p *curr_prompt);

char		**get_string(t_p *curr_prompt, char **split_by_space, \
				char *arg, char **str_op);
void		ms_parse_commands(t_ms *ms,
				t_p *curr_prompt, char **output_s_by_space,
				char **input_s_by_space);
void		prepare_cmd_line(const t_p *curr_prompt, \
	char **input_s_by_space, int c, t_cmd *curr_command);
char		*ms_append_path_in_front(t_cmd *current_cmd, t_ms *ms);
char		*check_path(int i, t_cmd *current_cmd, char **path);
void		reset_cmd(t_cmd **curr_command);
t_cmd		*update_cmd(t_cmd *curr_command);
char		*get_just_name(char *path);
int			is_input_command(char *name);
int			is_input_command_alone(t_ms *ms, char *cmd_line);

// prompt
void		ms_free_prompt(t_ms *ms);

// cmd
t_cmd		*ms_dll_cmd_last(t_cmd *cmds);
void		ms_dll_cmd_free(t_cmd *cmds);

/* execute */
void		ms_execute(t_ms *ms);
int			ms_execute_commands(t_ms *ms, t_p *curr_prompt);
void		ms_execute_command(t_p *prompt, \
t_cmd *current_cmd, char **envp, int *aux_fd);
int			bridge_builtion_other_cmds(t_cmd *current_cmd, \
t_p *prompt, int *clo);

int			is_builtin(char *cmd);
void		execute_builtin(t_ms *ms, t_cmd *current_cmd, t_p *prompt);
void		ms_close_fds(t_p *curr_prompt);
void		last_cmd_exit_code(t_ms *ms);
void		pre_cat_ls_sc(t_ms *ms, t_p *curr_prompt);
void		exec_cat_ls_sc(t_ms *ms);
int			ms_which_command_type(t_p *curr_prompt, \
t_cmd *current_cmd, t_ms *ms);
void		print_fd_or_execute_cmd(t_ms *ms, t_p *curr_prompt);
int			get_child_process_id(const t_p *prompt, \
				t_cmd *current_cmd, char **envp, const int *aux_fd);
int			is_input_command2(char *name, t_cmd **current_cmd, \
t_p *curr_prompt);
int			ms_execute_in_redi(t_p *curr_prompt);

// builtins
void		ms_cd(t_ms *ms, t_cmd *current_cmd, t_p *prompt);
void		ms_echo(t_ms *ms, t_cmd *current_cmd, t_p *prompt);
void		ms_env(t_ms *ms, t_cmd *current_cmd, t_p *prompt);
void		ms_exit(t_ms *ms, t_cmd *current_cmd, t_p *prompt);
void		ms_export(t_ms *ms, t_cmd *current_cmd, t_p *prompt);
void		ms_free_qs(const t_ms *ms, int aux, char **line, t_free **curr_qs);
void		quicksort(t_qs *qs, int left, int right, int (*comp)(void*, void*));
int			cmpstr(void *v1, void *v2);
void		ms_pwd(t_ms *ms, t_cmd *current_cmd, t_p *prompt);
void		ms_unset(t_ms *ms, t_cmd *current_cmd);
void		print_sorted_env(t_ms *ms, int aux);
char		**env_to_array(t_ms *ms);

/* utils */
void		ms_reinit(t_ms *ms);
void		ms_finish(t_ms *ms);

/* ms */
void		ms_subshell(t_ms *ms);
void		minishell(t_ms *ms);

#endif
