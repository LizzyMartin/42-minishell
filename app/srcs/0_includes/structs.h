/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:06:41 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/27 15:28:27 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

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
}	t_p;

typedef struct s_minishell
{
	int						argc;
	char					**argv;
	char					**envp;
	char					*shell_line;
	char					*shell_line_tokenized;
	char					**slt_splited_by_connectors;
	char					*readline_var;
	int						p_amount;
	t_p						*p;
	int						exit_code;
	int						history_i;
	t_history				*history;
	t_env					*envs;
}	t_ms;


#endif