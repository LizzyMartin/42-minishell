/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   29_execute_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:42:02 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/09 20:06:23 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

int	ms_execv(t_ms *ms, t_p *curr_prompt, t_cmd *current_cmd)
{
	if (ms->is_cat_sequence == 1
		&& ft_strnstr(current_cmd->just_name, \
		"cat", ft_strlen(current_cmd->just_name)) != NULL)
	{
		current_cmd = current_cmd->next;
		return (1);
	}
	if (ms_which_command_type(curr_prompt, \
	current_cmd, ms) == 1)
		return (0);
	return (-1);
}

int	ms_execute_commands(t_ms *ms, t_p *curr_prompt)
{
	t_cmd	*current_cmd;
	int		res;

	current_cmd = NULL;
	current_cmd = curr_prompt->cmds;
	pre_cat_ls_sc(ms, curr_prompt);
	res = -1;
	while (current_cmd)
	{
		res = ms_execv(ms, curr_prompt, current_cmd);
		if (res == 0)
			return (0);
		else if (res == 1)
			continue ;
		current_cmd = current_cmd->next;
	}
	exec_cat_ls_sc(ms);
	ms_add_history(ms, NULL, curr_prompt->cmds);
	ms_close_fds(curr_prompt);
	current_cmd = ms_dll_cmd_last(curr_prompt->cmds);
	return (current_cmd->exit_code);
}

static void	print_fd_or_execute_cmd_loop(t_ms *ms, t_p *curr_prompt)
{
	int		exit_code;
	char	*tmp;
	int		i;

	i = 0;
	while (curr_prompt)
	{
		tmp = ft_strtrim(curr_prompt->this_p_line, " ");
		if (ft_strncmp(tmp, T_SUBSHELL,
				ft_strlen(curr_prompt->this_p_line)) == 0)
			ms_execute_prompt_in_subshell(ms, curr_prompt, &exit_code);
		else
			exit_code = ms_execute_commands(ms, curr_prompt);
		ft_free_ptr((void *) &tmp);
		if (ms->connectors_order != NULL)
			if ((ms->connectors_order[i] == 1 && exit_code != 0)
				|| (ms->connectors_order[i] == 2 && exit_code == 0))
				break ;
		ft_free_ptr((void *) &tmp);
		i++;
		curr_prompt = curr_prompt->next;
	}
}

void	print_fd_or_execute_cmd(t_ms *ms, t_p *curr_prompt)
{
	if (curr_prompt->only_input_redirected_to_file == 1 || \
curr_prompt->only_redirect_to_file == 1)
		return ;
	else if (curr_prompt->no_cmd_just_redirect == 1)
		ft_fd_dup2(curr_prompt->pipe_here_doc[0], curr_prompt->output_fd);
	else
		print_fd_or_execute_cmd_loop(ms, curr_prompt);
}

void	ms_execute(t_ms *ms)
{
	t_p	*curr_prompt;
	int	o_here_doc;

	curr_prompt = ms->p;
	if (curr_prompt->has_here_doc == 1)
	{
		o_here_doc = curr_prompt->only_here_doc;
		curr_prompt->input_fd = ms_here_doc(ms, curr_prompt);
		if (o_here_doc == 1)
		{
			close(curr_prompt->input_fd);
			return ;
		}
	}
	print_fd_or_execute_cmd(ms, curr_prompt);
}
