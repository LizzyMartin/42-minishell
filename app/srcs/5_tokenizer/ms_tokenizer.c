#include <minishell.h>

char	*ms_get_home_value(t_ms *ms)
{
	if (is_in_env(ms, "HOME"))
		return find_env_value(ms, "HOME");
	else if (is_in_env(ms, "USER"))
		return ft_printf_to_var("/home/%s", find_env_value(ms, "USER"));
	else
		return ft_strdup("/home");
}

// void	ms_check_and_insert_spaces(t_ms *ms)
// {
// 	char *beggin;
// 	char *end;
// 	char *line;
// 	int i;
// 	int j;

// 	i = 0;
// 	line = ms->p.line;
// 	beggin = (char *)malloc(500 * sizeof(char *));
// 	end = (char *)malloc(500 * sizeof(char *));
// 	while (line[i])
// 	{
// 		if (line[i] == '>' && line[i + 1] == '>')
// 		{
// 			j = 0;
// 			end[j++] = ' ';
// 			end[j++] = '>';
// 			end[j++] = '>';
// 			end[j++] = ' ';
// 			while (line[i])
// 				end[j++] = line[i++];
// 			ms->p.line = ft_printf_to_var("%s%s", beggin, end);
// 			free(beggin);
// 			free(end);
// 			return ;
// 		}
// 		else if (line[i] == '>')
// 		{
// 			j = 0;
// 			end[j++] = ' ';
// 			end[j++] = '>';
// 			end[j++] = ' ';
// 			while (line[i])
// 				end[j++] = line[i++];
// 			ms->p.line = ft_printf_to_var("%s%s", beggin, end);
// 			free(beggin);
// 			free(end);
// 			return ;
// 		}
// 		beggin[i] = line[i];
// 		i++;
// 	}
// 	free(beggin);
// 	free(end);
// }

/*
void	ms_check_quotes(t_ms *ms)
{
	char	*line;
	int		i;

	i = 0;
	line = ms->shell_line;
	if (ft_strchr(line, '\'') == NULL)
	{
		while (line[i])
		{
			if (line[i] == '"')
				line[i] = ' ';
			i++;
		}
	}
}
*/

void	ms_tokenizer(t_ms *ms)
{
	ms->shell_line_tokenized = ft_str_replace_all(ms->shell_line, " && ", T_CONNECTOR);
	ms->shell_line_tokenized = ft_str_replace_all(ms->shell_line_tokenized, " | ", T_PIPE);
	ms->shell_line_tokenized = ft_str_replace_all(ms->shell_line_tokenized, ft_chr_to_str('~', 1), ms_get_home_value(ms));
}
