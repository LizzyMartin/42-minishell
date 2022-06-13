/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:06:41 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/13 15:45:05 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

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
	void	*vt;
	void	*v3;
	void	*vr;
	void	*vl;
	int		last;
	int		mid;
	void	*v;
	int		size;
	int		left;
	int		right;
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
	int						bridge_pipe[2];
	int						exit_code;
	char					*error_msg;
	int						cmd_is_path_but_invalid;
	int						can_execute;
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
	int						no_cmd_just_redirect;
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
	char					*aux;
	char					**str_export;
	t_qs					*qs;
	int						here_doc_open;
}	t_ms;

#endif
