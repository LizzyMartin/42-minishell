/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 22:13:24 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/17 22:03:28 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* includes */
# include			"../../libs/libft/app/srcs/libft.h"
# include			"design.h"
# include			"structs.h"

/* builtins */
int			ms_cd(t_ms *ms);
int			ms_echo(t_ms *ms);
int			ms_env(t_ms *ms);
void		ms_exit(t_ms *ms);
int			ms_export(t_ms *ms);
int			ms_pwd(t_ms *ms);
int			ms_unset(t_ms *ms);

/* design */
void		print_banner(void);

/* execute */
int			is_builtin(char *cmd);
void		execute_builtin(t_ms *ms);
void		ms_execute(t_ms *ms);

/* init */
t_ms		*ms_init(int argc, char **argv, char **envp);
void		init_env(t_ms *ms);

/* parse */
int			ms_parse(t_ms *ms);
void		ms_prepare_command (t_ms *ms);

/* signals */
int			ms_signals(t_ms *ms);

/* tmp */
t_cmd		*ft_cmd_last(t_cmd *cmds);
void		ft_cmd_add_back(t_cmd *cmd, char *name);

/* ms */
int			minishell(int argc, char **argv, char **envp);

#endif
