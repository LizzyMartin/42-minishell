/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 22:13:24 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/30 20:24:44 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* includes */
# include           "../../libs/libft/srcs/libft.h"
# include           "macros.h"
# include           "../1_design/design.h"
# include 			"errors.h"
# include           "structs.h"

/* design */
void		print_banner(void);
char		*ms_print_sh_name(void);

/* init */
void		ms_init(t_ms **ms, int argc, char **argv, char **envp);

// env
void		ms_init_env(t_ms *ms);
void		ms_add_env(t_ms *ms, char *key, char *value);
void		ms_delete_env(t_ms *ms, char *key);
char		*ms_find_env_value(t_ms *ms, char *key);
void		ms_free_env(t_ms *ms);
int			ms_is_in_env(t_ms *ms, const char *key);
void		ms_parse_env(t_ms *ms);

// history
t_history	*ms_last_history(t_history *history);
void		ms_free_history(t_ms *ms);

/* read_input */
int			ms_read_input(t_ms *ms);
int			ms_here_doc(t_p *p);

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
void		ms_print_history(t_ms *ms);

/* tokenizer */
void		ms_tokenizer(t_ms *ms);
void		ms_wildcard(t_ms *ms);
void		ms_check_quotes(t_ms *ms);
void		ms_remove_char(char *s, char c);

/* parse */
int			ms_parse(t_ms *ms);

char		**ms_parse_input(t_p *curr_prompt);
char		**ms_parse_output(t_p *curr_prompt);
char		*ms_append_path_in_front(t_cmd *current_cmd, t_ms *ms);
void		if_there_is_commands_prepare_them_to_be_executed(t_ms *ms,
				t_p *curr_prompt, char **output_s_by_space,
				char **input_s_by_space);

// prompt
void	     ms_free_prompt(t_p *curr_prompt);

// cmd
t_cmd		*ms_dll_cmd_last(t_cmd *cmds);
void		ms_dll_cmd_free(t_cmd *cmds);

/* execute */
void		ms_execute(t_ms *ms);
void		ms_execute_commands(t_ms *ms, t_p *prompt);

int			is_builtin(char *cmd);
void		execute_builtin(t_ms *ms, t_cmd *current_cmd, t_p *prompt);

void		last_cmd_exit_code(t_ms *ms);

// builtins
void		ms_cd(t_ms *ms, t_cmd *current_cmd);
void		ms_echo(t_ms *ms, t_cmd *current_cmd, t_p *prompt);
void		ms_env(t_ms *ms);
void		ms_exit(t_ms *ms, t_cmd *current_cmd);
void		ms_export(t_ms *ms, t_cmd *current_cmd);
void		ms_pwd(t_ms *ms);
void		ms_unset(t_ms *ms, t_cmd *current_cmd);

/* utils */
void		ms_reinit(t_ms *ms);
void		ms_finish(t_ms *ms);

/* ms */
void		minishell(t_ms *ms);

extern int g_ms_is_being_executed;

#endif
