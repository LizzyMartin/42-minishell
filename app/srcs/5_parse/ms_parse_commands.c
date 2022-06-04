/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:44:12 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/03 20:36:43 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_input_command(char *name)
{
	if (ft_strnstr(name, "cat", ft_strlen(name)) || \
		ft_strnstr(name, "more", ft_strlen(name)) || \
		ft_strnstr(name, "less", ft_strlen(name)) || \
		ft_strnstr(name, "tail", ft_strlen(name)) || \
		ft_strnstr(name, "wc", ft_strlen(name)) || \
		ft_strnstr(name, "touch", ft_strlen(name))
	)
		return (1);
	return (0);
}

int	is_input_command_alone(char *cmd_line)
{
	char **split;

	split = ft_split(cmd_line, ' ');
	if (is_input_command(split[0])
		&& ft_mtx_size((void **) split) == 1)
		return (1);
	return (0);
}

static void	prepare_cmd_line(const t_p *curr_prompt, \
	char **input_s_by_space, int c, t_cmd *curr_command)
{
	char	*tmp;
	int		aux;

	if (curr_prompt->has_here_doc == 1)
	{
		aux = ft_strlen(input_s_by_space[0]) \
			+ ft_strlen(input_s_by_space[1]) + 2;
		tmp = curr_prompt->this_p_line_splited_by_pipe[c] + aux;
		curr_command->cmd_line = ft_substr(tmp, 0, ft_strlen(tmp));
	}
	if (c == 0 && curr_prompt->input_redirected_to_file == 1)
	{
		aux = ft_strlen(input_s_by_space[0]) \
			+ ft_strlen(input_s_by_space[1]) + 2;
		tmp = curr_prompt->this_p_line_splited_by_pipe[c] + aux;
		curr_command->cmd_line = ft_substr(tmp, 0, ft_strlen(tmp));
	}
}

char	*get_just_name(char *path)
{
	int	i;

	i = ft_strlen(path);
	while (i > 0)
	{
		if (path[i] == '/')
			break ;
		i--;
	}
	return (ft_substr(path, i + 1, ft_strlen(path)));
}

static void	prepare_path_and_fd(t_ms *ms, t_p *curr_prompt, t_cmd *curr_command)
{
	char	*tmp;

	curr_command->cmd_splited_by_space = \
		ft_split(curr_command->cmd_line, ' ');
	curr_command->args_amount = \
		ft_mtx_size((void **) curr_command->cmd_splited_by_space);
	curr_command->just_name = curr_command->cmd_splited_by_space[0];
	tmp = ft_strdup(curr_command->just_name);
	if (ft_strnstr(tmp, "/", ft_strlen(tmp)) != NULL)
	{
		curr_command->just_name = get_just_name(tmp);
		curr_command->path_and_name = tmp;
		if (access(tmp, X_OK) == 0)
			curr_command->cmd_is_path_but_invalid = 0;
		else
			curr_command->cmd_is_path_but_invalid = 1;
	}
	else
	{
		curr_command->path_and_name = ms_append_path_in_front(curr_command, ms);
	}
	if (is_input_command(curr_command->just_name) == 1)
	{
		if (curr_command->args_amount >= 2 && curr_command->index == 0)
		{
			curr_prompt->input_path = \
				ft_strdup(curr_command->cmd_splited_by_space[1]);
			curr_prompt->input_fd = \
				open(curr_command->cmd_splited_by_space[1], O_RDONLY);
		}
	}
}

static void	prepare_something(t_cmd *curr_command, \
	t_p *curr_prompt, char **output_s_by_space)
{
	char	*tmp;
	int		length;
	int		aux;

	length = ft_mtx_size((void **) output_s_by_space);
	aux = ft_strlen(output_s_by_space[length - 2])
		+ ft_strlen(output_s_by_space[length - 1]) + 1;
	tmp = ft_strdup(curr_command->cmd_line);
	curr_command->cmd_line = ft_substr(tmp, 0, ft_strlen(tmp) - aux - 1);
	if (ft_strnstr(curr_command->cmd_line, ">>", \
		ft_strlen(curr_command->cmd_line)) \
		|| ft_strnstr(curr_command->cmd_line, ">", \
		ft_strlen(curr_command->cmd_line)))
		curr_prompt->no_cmd_just_redirect = 1;
}

void	ms_parse_commands(t_ms *ms, \
	t_p *curr_prompt, char **output_s_by_space, char **input_s_by_space)
{
	int		c;
	t_cmd	*curr_command;

	c = 0;
	curr_prompt->cmds = (t_cmd *) malloc (sizeof(struct s_cmd));
	curr_command = curr_prompt->cmds;
	reset_cmd(&curr_command);
	while (c < curr_prompt->pipe_amount)
	{
		if (c > 0)
			curr_command = update_cmd(curr_command);
		curr_command->exit_code = 0;
		curr_command->index = c;
		curr_command->cmd_line = \
		ft_strdup(curr_prompt->this_p_line_splited_by_pipe[c]);
		prepare_cmd_line(curr_prompt, input_s_by_space, c, curr_command);
		if (c == (curr_prompt->pipe_amount - 1) && curr_prompt->redirect > 0)
			prepare_something(curr_command, curr_prompt, output_s_by_space);
		prepare_path_and_fd(ms, curr_prompt, curr_command);
		if(is_input_command_alone(curr_command->cmd_line) && \
		curr_prompt->args_amount == 1)
			curr_command->can_execute = 0;
		// ft_printf("%d", curr_prompt->args_amount);
		c++;
	}
}
