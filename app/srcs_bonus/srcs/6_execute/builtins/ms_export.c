/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:42 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/09 17:15:31 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<_minishell.h>

char	**env_to_array(t_ms *ms)
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

static void	add_env_by_key_2(t_ms *ms, char *key, char *value, char *tmp)
{
	if (ms_is_in_env(ms, key))
		update_env_value(ms, key, value);
	else
		ms_add_env(&ms->envs, key, value);
	ft_free_ptr((void *) &tmp);
	ms->p->cmds->exit_code = 0;
}

static void	add_env_by_key(t_ms *ms, const t_cmd *current_cmd)
{
	char	*key;
	char	*value;
	int		equal_index;
	int		i;
	char	*tmp;

	equal_index = ft_str_indexof(current_cmd->cmd_splited_by_space[1], \
	"=", ft_strlen(current_cmd->cmd_splited_by_space[1]));
	if (equal_index == -1)
		return ;
	tmp = ft_substr(current_cmd->cmd_splited_by_space[1], 0, equal_index);
	key = tmp;
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
	add_env_by_key_2(ms, key, value, tmp);
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
		return ;
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
