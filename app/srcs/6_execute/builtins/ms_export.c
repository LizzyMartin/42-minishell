/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:42 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/26 21:19:26 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	swap(t_env *envs_1, t_env *envs_2)
{
	char	*s_key;
	char	*s_value;

	s_key = envs_2->key;
	s_value = envs_2->value;
	envs_2->key = envs_1->key;
	envs_2->value = envs_1->value;
	envs_1->key = s_key;
	envs_1->value = s_value;
}

void	bubble_sort(t_env *start)
{
	int		swapped;
	t_env	*ptr1;
	t_env	*lptr;

	lptr = NULL;
	swapped = 0;
	if (start == NULL)
		return ;
	while (!swapped)
	{
		swapped = 0;
		ptr1 = start->next;
		while (ptr1->next != lptr)
		{
			if (*(ptr1->key) > *(ptr1->next->key))
			{
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

static void	print_sorted_env(t_ms *ms)
{
	t_env	*env;

	bubble_sort(ms->envs);
	env = ms->envs;
	while (env)
	{
		if (env->key != NULL && env->value != NULL)
			ft_printf("declare -x %s=%s\n", env->key, env->value);
		env = env->next;
	}
}

static void	add_env_by_key(t_ms *ms, const t_cmd *current_cmd)
{
	char	*key;
	char	*value;
	char	**cmd_env_splitted;

	cmd_env_splitted = ft_split(current_cmd->cmd_splited_by_space[1], '=');
	key = cmd_env_splitted[0];
	if (cmd_env_splitted[1] != NULL)
		value = cmd_env_splitted[1];
	else
		value = "";
	ms_add_env(ms, key, value);
	ms->p.cmds->exit_code = 0;
}

void	ms_export(t_ms *ms, t_cmd *current_cmd)
{
	if (!current_cmd->cmd_splited_by_space[1] || \
		*current_cmd->cmd_splited_by_space[1] == '\0' || \
		*current_cmd->cmd_splited_by_space[1] == ' ')
		print_sorted_env(ms);
	if (ft_strnstr(current_cmd->cmd_splited_by_space[1], "=", \
		ft_strlen(current_cmd->cmd_splited_by_space[1])) == NULL)
	{
		ms->p.cmds->exit_code = 0;
		return ;
	}
	if (ft_isdigit(current_cmd->cmd_splited_by_space[1][0]))
	{
		ft_putstr_fd("export: '", 2);
		ft_putstr_fd(current_cmd->cmd_splited_by_space[1], 2);
		ft_putstr_fd("' : not a valid identifier\n", 2);
		ms->p.cmds->exit_code = 1;
		return ;
	}
	add_env_by_key(ms, current_cmd);
}
