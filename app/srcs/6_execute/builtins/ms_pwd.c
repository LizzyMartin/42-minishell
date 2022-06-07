/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:45 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/07 18:07:20 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_pwd(t_ms *ms, t_cmd *current_cmd, t_p *prompt)
{
	char	cwd[PATH_MAX];
	int		aux;
	int		tmp_fd[2];

	pipe(tmp_fd);
	prompt->input_fd = tmp_fd[0];
	aux = tmp_fd[1];
	if ((current_cmd->index == \
			(prompt->args_amount - 1)) && prompt->redirect <= 0)
		aux = 1;
	else
		aux = prompt->output_fd;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ms->p->cmds->exit_code = 0;
		ft_putstr_fd(cwd, aux);
		ft_putstr_fd("\n", aux);
	}
	else
		ms->p->cmds->exit_code = 1;
	if (aux != 1)
		close(aux);
}
