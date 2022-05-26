#include <minishell.h>

static char	*ms_get_home_value(t_ms *ms)
{
	if (is_in_env(ms, "HOME"))
		return find_env_value(ms, "HOME");
	else if (is_in_env(ms, "USER"))
		return ft_printf_to_var("/home/%s", find_env_value(ms, "USER"));
	else
		return ft_strdup("/home");
}

void	ms_check_quotes(t_ms *ms)
{
	char	*line;
	int		i;
	int 	j;
	int 	quote_terminated;

	i = 0;
	line = ms->shell_line;
	quote_terminated = 0;
	if (ft_strchr(line, '\'') == NULL)
	{
		while (line[i])
		{
			if (line[i] == '"') {
				j = i + 1;
				while (line[j])
				{
					if (line[j] == '"')
					{
						quote_terminated = 1;
						break ;
					}
					j++;
				}
				j = i;
				while (line[j])
				{
					if (quote_terminated && line[j] == '"')
					{
						line[j] = ' ';
						j++;
					}
					if (line[j] ==  ' ')
					{
						line[j] = '-';
					}
					j++;
				}
				break ;
			}
			i++;
		}
	}
}

char	*ms_wildcards(t_ms *ms, char *wildcard)
{
	if (ms)
	{
	}
	char 			*replace;
	struct dirent	*de;
	int				all;

	all = 0;
	replace = ft_strdup("");
	DIR *dr = opendir(".");
	if (ft_strncmp(wildcard, "*", ft_strlen(wildcard)) == 0)
		all = 1;
	while ((de = readdir(dr)) != NULL)
	{
		if (all == 0 && (ft_strnstr(de->d_name, wildcard + 1, ft_strlen(de->d_name)) == NULL))
			continue ;
		if (all == 1 && \
		((ft_strncmp(de->d_name, ".", ft_strlen(de->d_name)) == 0) || \
		(ft_strncmp(de->d_name, "..", ft_strlen(de->d_name)) == 0)))
			continue;
		replace = ft_strjoin(ft_strjoin(replace, " "), de->d_name);
		replace = ft_strjoin(replace, " \0");
	}
	closedir(dr);
	return (replace);
}

int	ms_exist_some_file_with_this_wildcard(char *wildcard)
{
	if (ft_strncmp(wildcard, "*", ft_strlen(wildcard)) == 0)
		return (1);
	DIR 			*dr;
	struct dirent	*de;
	int				wd_f_o;
	int				exist;

	exist = 0;
	dr = opendir(".");
	while ((de = readdir(dr)) != NULL)
	{
		wd_f_o = ft_str_indexof(de->d_name, wildcard + 1, ft_strlen(de->d_name));
		if (wd_f_o > 0)
			exist = 1;
	}
	closedir(dr);
	return (exist);
}



int	next_space_index(t_ms *ms, int after_asteristic_posi)
{
	char	*tmp;

	tmp = ms->shell_line;
	while (tmp[after_asteristic_posi] != ' ' && tmp[after_asteristic_posi] != '\0')
		after_asteristic_posi++;
	return (after_asteristic_posi);
}

void	ms_tokenizer(t_ms *ms)
{
	ms_check_quotes(ms);
	ms->shell_line_tokenized = ft_str_replace_all(ms->shell_line, " && ", T_CONNECTOR);
	ms->shell_line_tokenized = ft_str_replace_all(ms->shell_line_tokenized, " | ", T_PIPE);
	ms->shell_line_tokenized = ft_str_replace_all(ms->shell_line_tokenized, ft_chr_to_str('~', 1), ms_get_home_value(ms));

	// wildcards
	char *iterate_shell_line;
	int start;
	int end;
	char *replace;
	char *wildcard;

	iterate_shell_line = ms->shell_line_tokenized;
	while (ft_strrchr(iterate_shell_line, '*'))
	{

		replace = ft_strdup("");
		start = ft_indexof(ms->shell_line, '*') + 1;
		end = next_space_index(ms, start) - 1;
		wildcard = ft_substr(ms->shell_line, start, end);
		if (ms_exist_some_file_with_this_wildcard(wildcard) == 1)
		{
			replace = ms_wildcards(ms, wildcard);
			ms->shell_line_tokenized = ft_str_replace(ms->shell_line_tokenized, wildcard, replace);
		}
		else
			iterate_shell_line += start;
	}
}
