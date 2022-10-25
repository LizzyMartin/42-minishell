/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   32_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:34 by acapela-          #+#    #+#             */
/*   Updated: 2022/10/12 02:52:57 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

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
			ft_free_ptr((void *) &line);
		}
		env = env->next;
	}
}

void	ms_env(t_ms *ms, t_cmd *current_cmd, t_p *prompt)
{
	int		aux;
	int		clo;

	if (ms_find_env_value(ms, "PATH") == NULL)
	{
		ft_pf_error("miniheaven: %s %s", \
		current_cmd->just_name, E_NOTDIR);
		ms->no_path = 1;
		current_cmd->exit_code = 127;
		return ;
	}
	clo = 0;
	aux = bridge_builtion_other_cmds(current_cmd, prompt, &clo);
	ms_print_env(ms, aux);
	ms->p->cmds->exit_code = EXIT_SUCCESS;
	if (clo)
		close(aux);
}
