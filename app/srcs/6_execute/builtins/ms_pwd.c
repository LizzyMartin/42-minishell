/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:45 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/11 20:38:07 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_pwd(t_ms *ms, t_cmd *current_cmd, t_p *prompt)
{
	char	cwd[PATH_MAX];
	int		aux;
	int		clo;

	clo = 0;
	aux = bridge_builtion_other_cmds(current_cmd, prompt, &clo);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ms->p->cmds->exit_code = 0;
		ft_putstr_fd(cwd, aux);
		ft_putstr_fd("\n", aux);
	}
	else
		ms->p->cmds->exit_code = 1;
	if (clo)
		close(aux);
}
