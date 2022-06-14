/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:42 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/14 18:00:39 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<minishell.h>

static char	**env_to_array(t_ms *ms)
{
	char	**arr;
	int		i;
	int		count;
	t_env	*tmp_env;

	tmp_env = ms->envs;
	count = 0;
	while (tmp_env)
	{
		count++;
		tmp_env = tmp_env->next;
	}
	arr = ft_calloc(count + 1, sizeof(char *));
	i = 0;
	tmp_env = ms->envs;
	while (tmp_env)
	{
		if (tmp_env->key != NULL && tmp_env->value != NULL)
		{
			arr[i] = ft_printf_to_var("%s=%s", tmp_env->key, tmp_env->value);
			i++;
		}
		tmp_env = tmp_env->next;
	}
	return (arr);
}

static void	add_env_by_key(t_ms *ms, const t_cmd *current_cmd)
{
	char	*key;
	char	*value;
	int		equal_index;
	int		i;

	equal_index = ft_str_indexof(current_cmd->cmd_splited_by_space[1], \
	"=", ft_strlen(current_cmd->cmd_splited_by_space[1]));
	key = ft_substr(current_cmd->cmd_splited_by_space[1], 0, equal_index);
	value = current_cmd->cmd_splited_by_space[1] + equal_index + 1;
	i = 0;
	while (key[i])
	{
		if (!ft_isalpha(key[i]))
		{
			ft_printf_to_fd(2, "miniheaven: export: `%s': \
not a valid identifier\n", key);
			ms->p->cmds->exit_code = 1;
			return ;
		}
		i++;
	}
	if (ms_is_in_env(ms, key))
		update_env_value(ms, key, value);
	else
		ms_add_env(&ms->envs, key, value);
	ms->p->cmds->exit_code = 0;
}

static void	print_sorted_env(t_ms *ms, int aux)
{
	char	*line;
	int		i;
	t_free	*curr_qs;

	i = 0;
	ms->str_export = env_to_array(ms);
	ms->qs = ft_calloc (1, sizeof(t_qs));
	ms->qs->free_qs = NULL;
	ms->qs->v = ms->str_export;
	ms->qs->size = sizeof(char *);
	quicksort(ms->qs, 0, ft_mtx_size((void **) ms->str_export) - 1, \
			(int (*)(void *, void *))(cmpstr));
	curr_qs = ms->qs->free_qs;
	ms_free_qs(ms, aux, &line, &curr_qs);
}

static void	check_first_char(t_ms *ms, t_cmd *current_cmd, int aux)
{
	char	*line;

	if (ft_isdigit(current_cmd->cmd_splited_by_space[1][0]))
	{
		line = ft_printf_to_var("miniheaven: export: `%s` \
not a valid identifier\n", current_cmd->cmd_splited_by_space[1]);
		ft_putstr_fd(line, aux);
		free(line);
		ms->p->cmds->exit_code = 1;
	}
	add_env_by_key(ms, current_cmd);
	ms->p->cmds->exit_code = 0;
}

void	ms_export(t_ms *ms, t_cmd *current_cmd, t_p *prompt)
{
	int		aux;
	int		clo;

	clo = 0;
	aux = bridge_builtion_other_cmds(current_cmd, prompt, &clo);
	if (!current_cmd->cmd_splited_by_space[1]
		|| *current_cmd->cmd_splited_by_space[1] == '\0'
		|| *current_cmd->cmd_splited_by_space[1] == ' ')
		print_sorted_env(ms, aux);
	else
		check_first_char(ms, current_cmd, aux);
	ft_mtx_free((void **) ms->str_export);
	if (clo)
		close(aux);
}
