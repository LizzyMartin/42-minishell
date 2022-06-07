/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:34 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/07 18:54:27 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ms_print_env(t_ms *ms, int aux)
{
	char	*line;
	t_env	*env;

	env = ms->envs;
	while (env)
	{
		if (env->key != NULL && env->value != NULL)
		{
			line = ft_printf_to_var("%s=%s\n", env->key, env->value);
			ft_putstr_fd(line, aux);
		}
		env = env->next;
	}
}

void	ms_env(t_ms *ms, t_cmd *current_cmd, t_p *prompt)
{
	int		aux;
	int		tmp_fd[2];

	pipe(tmp_fd);
	prompt->input_fd = tmp_fd[0];
	aux = tmp_fd[1];
	if ((current_cmd->index == (prompt->args_amount - 1)) \
			&& prompt->redirect <= 0)
		aux = 1;
	else
		aux = prompt->output_fd;
	ms_print_env(ms, aux);
	ms->p->cmds->exit_code = EXIT_SUCCESS;
	if (aux != 1)
		close(aux);
}
