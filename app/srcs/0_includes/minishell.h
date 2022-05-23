/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 22:13:24 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/18 17:31:56 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* includes */
# include			"../../libs/libft/srcs/libft.h"
# include			"../1_design/design.h"
# include			"structs.h"
# include			"macros.h"

/* design */
void		print_banner(void);
void	    ms_print_sh_name(void);

/* init */
t_ms		*ms_init(int argc, char **argv, char **envp);
void		init_env(t_ms *ms);

// env
void		add_env(t_ms *ms, char *key, char *value);
void		delete_env(t_ms *ms, char *key);
char		*find_env_value(t_ms *ms, char *key);
void		free_env(t_ms *ms);
int			is_in_env(t_ms *ms, const char *key);
void		parse_env(t_ms *ms);

/* read_input */
int	        ms_read_input(t_ms *ms);

/* signals */
void	    ms_read_input_signals(void);
void	    ms_execute_command_signals(void);
void        ctrl_d_exit_shell(int signal);

/* save history */
void	    ms_init_history(t_ms *ms);
void        ms_add_history(t_ms *ms, char *line);
void	    ms_print_history(t_ms *ms);

/* tokenizer */
void		ms_tokenizer(t_ms *ms);

/* parse */
int			ms_parse(t_ms *ms);
void		ms_prepare_command (t_ms *ms);
char	    *append_path(t_cmd *current_cmd, t_ms *ms);

/* execute */
int			is_builtin(char *cmd);
void	    execute_builtin(t_ms *ms, t_cmd *current_cmd);
void		ms_execute(t_ms *ms);
void	    last_cmd_exit_status(t_ms *ms);
void	    ms_reinit(t_ms *ms);

// builtins
int			ms_cd(t_ms *ms);
int	        ms_echo(t_ms *ms, t_cmd *current_cmd);
int			ms_env(t_ms *ms);
void		ms_exit(t_ms *ms);
int			ms_export(t_ms *ms);
int			ms_pwd(t_ms *ms);
int			ms_unset(t_ms *ms);

/* utils */
void		ms_clear(t_ms *ms);
void		ms_free(t_ms *ms);
void	    ms_finish(t_ms *ms);

// dll_cmd
t_cmd		*ft_dll_cmd_last(t_cmd *cmds);
void	    ft_dll_cmd_add_back(t_ms *ms, char **cmd_splited);
void	    ft_dll_cmd_free(t_ms *ms);

/* ms */
void		minishell(t_ms *ms);

#endif
