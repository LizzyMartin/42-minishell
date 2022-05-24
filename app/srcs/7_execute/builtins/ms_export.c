#include <minishell.h>

/* function to swap data of two t_envs a and b*/
void swap(t_env *envs_1, t_env *envs_2)
{
	char* s_key;
 	char* s_value;

	s_key = envs_2->key;
	s_value = envs_2->value;
	envs_2->key = envs_1->key;
	envs_2->value = envs_1->value;
	envs_1->key = s_key;
	envs_1->value = s_value;
}

void bubbleSort(t_env *start)
{
    int swapped;
    t_env *ptr1;
    t_env *lptr = NULL;
  
    /* Checking for empty list */
    if (start == NULL)
        return;
    do
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
    while (swapped);
}

void ms_env_sort(t_ms *ms)
{
	bubbleSort(ms->envs);
}

void	ms_export(t_ms *ms, t_cmd *current_cmd)
{
	char *key;
	char *value;
	char **cmd_env_splitted;
	t_env *env;

	if (!current_cmd->cmd_splited_by_space[1] || *current_cmd->cmd_splited_by_space[1] == '\0' || *current_cmd->cmd_splited_by_space[1] == ' ')
	{
		ms_env_sort(ms);
		env = ms->envs;
		while (env)
		{
			if (env->key != NULL && env->value != NULL)
				ft_printf("declare -x %s=%s\n", env->key, env->value);
			env = env->next;
		}
	}
	if (ft_strnstr(current_cmd->cmd_splited_by_space[1], "=", ft_strlen(current_cmd->cmd_splited_by_space[1])) == NULL)
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
	cmd_env_splitted = ft_split(current_cmd->cmd_splited_by_space[1], '=');
	key = cmd_env_splitted[0];
	if (cmd_env_splitted[1] != NULL)
		value = cmd_env_splitted[1];
	else
		value = "";
	add_env(ms, key, value);
	ms->p.cmds->exit_code = 0;
}


// void ms_env_sort(t_ms *ms)
// {
// 	t_env *envs_1;
// 	t_env *envs_2;
// 	char* s_key;
// 	char* s_value;

// 	envs_1 = ms->p.envs;
// 	envs_2 = ms->p.envs->next;
// 	while (envs_1->next->next != NULL)
// 	{
// 		while (envs_2 != NULL)
// 		{
// 			if (envs_1->key != NULL && envs_1->value != NULL)
// 				if (*(envs_1->key) > *(envs_2->next->key))
// 				{
// 					s_key = envs_2->key;
// 					s_value = envs_2->value;
// 					envs_2->key = envs_1->key;
// 					envs_2->value = envs_1->value;
// 					envs_1->key = s_key;
// 					envs_1->value = s_value;
// 				}
// 			envs_2 = envs_2->next;	
// 		}
// 		envs_2 = ms->p.envs->next;				
// 		envs_1 = envs_1->next;
// 	}
// }