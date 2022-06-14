/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 22:13:24 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/13 21:24:57 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* includes */
# include           "../../libs/libft/srcs/libft.h"
# include           "macros.h"
# include           "../1_design/design.h"
# include           "errors.h"
# include           "structs.h"
# include           <stdbool.h>

/*
** GLOBAL VARIABLE: pointer to ms struct, so we can
** easily free ms when signal is called.
*/

extern t_ms	*g_ms;

/* design */
void		print_banner(void);
char		*ms_print_sh_name(void);

/* init */
void		ms_init(t_ms **ms, int argc, char **argv, char **envp);

// env
void		ms_init_env(t_ms *ms);
void		ms_add_env(t_env **env, char *key, char *value);
void		ms_delete_env(t_ms *ms, char *key);
char		*ms_find_env_value(t_ms *ms, char *key);
void		ms_free_env(t_env *envs);
int			ms_is_in_env(t_ms *ms, const char *key);
void		update_env_value(t_ms *ms, char *key, char *value);
t_env		*ms_last_env(t_env *env);

// history
t_history	*ms_last_history(t_history *history);
void		ms_free_history(t_ms *ms);

/* read_input */
int			ms_read_input(t_ms *ms);
int			ms_here_doc(t_ms *ms, t_p *p);

// signals
void		ms_read_input_signals(void);
void		ms_while_executing_commands_signals(void);
void		ctrl_c_redisplay_prompt(int signal);
void		ctrl_c_interrupt_process(int signal);
void		ctrl_d_exit_shell(int signal);
void		ctrl_d_quit_process(int signal);

/* history */
void		ms_init_history(t_ms *ms);
void		ms_add_history(t_ms *ms, char *line, t_cmd *cmds);
void		ms_print_history(t_ms *ms, t_cmd *current_cmd, t_p *prompt);

/* tokenizer */
int			ms_sintax(t_ms *ms);
int			ms_tokenizer(t_ms *ms);
void		ms_wildcard(t_ms *ms);
void		ms_check_quotes(t_ms *ms);
int			ms_get_index(t_ms *ms, int size, char **cmd);
int			ms_check_if_have_quotes(t_ms *ms, char *line);
int			get_index_before_space(t_ms *ms, int size, char **cmd);
bool		get_boolean(const char *wildcard, const struct dirent *de, int all);
void		update_tmp(char **replace, DIR *dr, struct dirent **de, char **tmp);
void		ms_expand_dolar(t_ms *ms);
int			ms_count_char(char *str, char c);
int			valid_chr(char chr);
void		ms_quotes_vs_connectors(t_ms *ms, char *line);
void		ms_check_quotes_aux(t_ms *ms, char **cmd, char *tmp, char *aux);
void		ms_replace_connectors_by_token(t_ms *ms, char *tmp);

/* parse */
int			ms_parse(t_ms *ms);

t_p			*parse_prompts(t_ms *ms);
t_p			*ms_get_prompt(t_ms *ms, t_p *curr_prompt, int i);

char		**ms_parse_input(t_p *curr_prompt);
char		**ms_parse_output(t_p *curr_prompt);

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
int			is_input_command_alone(char *cmd_line);

// prompt
void		ms_free_prompt(t_ms *ms, t_p *curr_prompt);

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
void		cat_ls_sc(t_p *curr_prompt);
int			ms_which_command_type(t_p *curr_prompt, \
t_cmd *current_cmd, t_ms *ms);

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

/* utils */
void		ms_reinit(t_ms *ms);
void		ms_finish(t_ms *ms);

/* ms */
void		minishell(t_ms *ms);

#endif
