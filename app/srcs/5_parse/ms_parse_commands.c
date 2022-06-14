/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:44:12 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/14 17:43:20 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	treat_input_command(t_p *curr_prompt, t_cmd *curr_command)
{
	if (is_input_command(curr_command->just_name) == 1)
	{
		if (curr_command->args_amount >= 2 && curr_command->index == 0)
		{
			curr_prompt->input_path = curr_command->cmd_splited_by_space[1];
			curr_prompt->input_fd = \
				open(curr_command->cmd_splited_by_space[1], O_RDONLY);
		}
	}
}

static void	prepare_path_and_fd(t_ms *ms, t_p *curr_prompt, t_cmd *curr_command)
{
	char	*tmp;

	curr_command->cmd_splited_by_space = \
		ft_split(curr_command->cmd_line, ' ');
	curr_command->args_amount = \
		ft_mtx_size((void **) curr_command->cmd_splited_by_space);
	if (ms->tmp)
		ft_free_ptr((void *) &ms->tmp);
	ms->tmp = ft_strdup(curr_command->cmd_splited_by_space[0]);
	curr_command->just_name = ft_strdup(ms->tmp);
	tmp = curr_command->just_name;
	if (ft_strnstr(tmp, "/", ft_strlen(tmp)) != NULL)
	{
		curr_command->just_name = get_just_name(tmp);
		curr_command->path_and_name = ft_strdup(tmp);
		if (access(tmp, X_OK) == 0)
			curr_command->cmd_is_path_but_invalid = 0;
		else
			curr_command->cmd_is_path_but_invalid = 1;
		ft_free_ptr((void *) &tmp);
	}
	else
		curr_command->path_and_name = ms_append_path_in_front(curr_command, ms);
	treat_input_command(curr_prompt, curr_command);
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
	ft_free_ptr((void *) &curr_command->cmd_line);
	curr_command->cmd_line = ft_substr(tmp, 0, ft_strlen(tmp) - aux - 1);
	if (ft_strnstr(curr_command->cmd_line, ">>", \
		ft_strlen(curr_command->cmd_line)) \
		|| ft_strnstr(curr_command->cmd_line, ">", \
		ft_strlen(curr_command->cmd_line)))
		curr_prompt->no_cmd_just_redirect = 1;
	ft_free_ptr((void *) &tmp);
}

void	ms_parse_commands2(t_ms *ms, \
	t_p *curr_prompt, t_cmd *curr_command, int c)
{
	ms->tmp2 = ft_strdup(curr_prompt->this_p_line_splited_by_pipe[c]);
	ft_free_ptr((void *) &curr_command->cmd_line);
	curr_command->cmd_line = ft_strdup(ms->tmp2);
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
		ft_free_ptr((void *) &ms->tmp2);
		ms_parse_commands2(ms, curr_prompt, curr_command, c);
		prepare_cmd_line(curr_prompt, input_s_by_space, c, curr_command);
		if (c == (curr_prompt->pipe_amount - 1) && curr_prompt->redirect > 0)
			prepare_something(curr_command, curr_prompt, output_s_by_space);
		if (*curr_command->cmd_line != '\0')
			prepare_path_and_fd(ms, curr_prompt, curr_command);
		if (is_input_command_alone(ms, curr_command->cmd_line) && \
		curr_prompt->args_amount == 1)
			curr_command->can_execute = 1;
		c++;
	}
}
