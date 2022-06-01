/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:42 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/31 21:30:03 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<minishell.h>

char	**env_to_array(t_env *env)
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

int	cmpstr(void *v1, void *v2)
{
	char	*a1;
	char	*a2;

	a1 = *(char **) v1;
	a2 = *(char **) v2;
	return (ft_strncmp(a1, a2, ft_strlen(a1)));
}

void	swap(void *v1, void *v2, int size)
{
	char	buffer[size];

	ft_memcpy(buffer, v1, size);
	ft_memcpy(v1, v2, size);
	ft_memcpy(v2, buffer, size);
}

void	_qsort(void *v, int size, int left, int right,
						int (*comp)(void*, void*))
{
	void	*vt;
	void	*v3;
	void	*vr;
	void	*vl;
	int		i;
	int		last;
	int		mid;

	mid = (left + right) / 2;
	if (left >= right)
		return ;
	vl = (char *)(v + (left * size));
	vr = (char *)(v + (mid * size));
	swap(vl, vr, size);
	last = left;
	i = left;
	while (i <= right)
	{
		vt = (char *)(v + (i * size));
		if ((*comp)(vl, vt) > 0)
		{
			++last;
			v3 = (char *)(v + (last * size));
			swap(vt, v3, size);
		}
		i++;
	}
	v3 = (char *)(v + (last * size));
	swap(vl, v3, size);
	_qsort(v, size, left, last - 1, comp);
	_qsort(v, size, last + 1, right, comp);
}

static void	print_sorted_env(t_ms *ms)
{
	t_env	*env;
	char	**str;
	int		i;

	i = 0;
	env = ms->envs;
	str = env_to_array(env);
	_qsort(str, sizeof(char *), 0, ft_mtx_size((void **) str) - 1, \
			(int (*)(void *, void *))(cmpstr));
	i = 0;
	while (str[i])
	{
		if (str[i])
			ft_printf("declare -x %s\n", str[i]);
		i++;
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
	ms->p->cmds->exit_code = 0;
}

void	ms_export(t_ms *ms, t_cmd *current_cmd)
{
	if (!current_cmd->cmd_splited_by_space[1]
		|| *current_cmd->cmd_splited_by_space[1] == '\0'
		|| *current_cmd->cmd_splited_by_space[1] == ' ')
		print_sorted_env(ms);
	if (ft_strnstr(current_cmd->cmd_splited_by_space[1], "=",
			ft_strlen(current_cmd->cmd_splited_by_space[1])) == NULL)
	{
		ms->p->cmds->exit_code = 0;
		return ;
	}
	if (ft_isdigit(current_cmd->cmd_splited_by_space[1][0]))
	{
		ft_putstr_fd("export: '", 2);
		ft_putstr_fd(current_cmd->cmd_splited_by_space[1], 2);
		ft_putstr_fd("' : not a valid identifier\n", 2);
		ms->p->cmds->exit_code = 1;
		return ;
	}
	add_env_by_key(ms, current_cmd);
}
