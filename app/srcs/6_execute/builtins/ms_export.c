/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:42 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/03 19:56:26 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<minishell.h>

static char	**env_to_array(t_env *env)
{
	char	**arr;
	int		i;

	arr = malloc(sizeof(char *) * 500);
	i = 0;
	while (env)
	{
		arr[i] = ft_printf_to_var("%s=%s", env->key, env->value);
		i++;
		env = env->next;
	}
	return (arr);
}

static void	add_env_by_key(t_ms *ms, const t_cmd *current_cmd)
{
	char	*key;
	char	*value;
	int		equal_index;

	equal_index = ft_str_indexof(current_cmd->cmd_splited_by_space[1], \
	"=", ft_strlen(current_cmd->cmd_splited_by_space[1]));
	key = ft_substr(current_cmd->cmd_splited_by_space[1], 0, equal_index);
	value = current_cmd->cmd_splited_by_space[1] + equal_index + 1;
	int i = 0;
	while (key[i])
	{
		if (!ft_isalpha(key[i])) {
			ft_printf_to_fd(1, "bash: export: `%s': not a valid identifier", key);
			ms->p->cmds->exit_code = 1;
			return ;
		}
	}
	if (ms_is_in_env(ms, key))
		update_env_value(ms, key, value);
	else
		ms_add_env(&ms->envs, key, value);
	ms->p->cmds->exit_code = 0;
}

static void	print_sorted_env(t_ms *ms, int aux)
{
	t_env	*env;
	char	**str;
	char 	*line;
	int		i;
	t_qs	*qs;

	i = 0;
	env = ms->envs;
	str = env_to_array(env);
	qs = ft_calloc (1, sizeof(t_qs));
	qs->v = str;
	qs->size = sizeof(char *);
	quicksort(qs, 0, ft_mtx_size((void **) str) - 1, \
			(int (*)(void *, void *))(cmpstr));
	i = 0;
	while (str[i])
	{
		if (str[i])
		{
			line = ft_printf_to_var("declare -x %s\n", str[i]);
			ft_putstr_fd(line, aux);
		}
		i++;
	}
}

void	ms_export(t_ms *ms, t_cmd *current_cmd, t_p *prompt)
{
	char	*line;
	int		aux;
	int		tmp_fd[2];

	pipe(tmp_fd);
	prompt->input_fd = tmp_fd[0];
	aux = tmp_fd[1];
	if (current_cmd->index == prompt->args_amount - 1)
		aux = 1;
	if (!current_cmd->cmd_splited_by_space[1]
		|| *current_cmd->cmd_splited_by_space[1] == '\0'
		|| *current_cmd->cmd_splited_by_space[1] == ' ')
		print_sorted_env(ms, aux);
	if (ft_strnstr(current_cmd->cmd_splited_by_space[1], "=",
			ft_strlen(current_cmd->cmd_splited_by_space[1])) == NULL)
	{
		ms->p->cmds->exit_code = 0;
		return ;
	}
	if (ft_isdigit(current_cmd->cmd_splited_by_space[1][0]))
	{
		line = ft_printf_to_var("export: `%s` : not a valid identifier\n", current_cmd->cmd_splited_by_space[1]);
		ft_putstr_fd(line, aux);
		ms->p->cmds->exit_code = 1;
		return ;
	}
	add_env_by_key(ms, current_cmd);
	if (aux != 1)
		close(aux);
}
