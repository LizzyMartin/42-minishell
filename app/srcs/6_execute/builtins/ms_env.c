/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:34 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/03 19:18:31 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_env(t_ms *ms, t_cmd *current_cmd, t_p *prompt)
{
	t_env	*env;
	char	*line;
	int		aux;
	int		tmp_fd[2];

	env = ms->envs;
	pipe(tmp_fd);
	prompt->input_fd = tmp_fd[0];
	aux = tmp_fd[1];
	if (current_cmd->index == prompt->args_amount - 1)
		aux = 1;
	while (env)
	{
		if (env->key != NULL && env->value != NULL)
		{
			line = ft_printf_to_var("%s=%s\n", env->key, env->value);
			ft_putstr_fd(line, aux);
		}
		env = env->next;
	}
	ms->p->cmds->exit_code = EXIT_SUCCESS;
	if (aux != 1)
		close(aux);
}
