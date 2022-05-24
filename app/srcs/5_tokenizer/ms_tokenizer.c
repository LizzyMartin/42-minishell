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

/*
 * procura por aspas duplas, se tiver terminada, troca os espaços por algo
 * e ignora as aspas duplas
 *
 * ex:
 * "oi" -> oi
 * "       oi" -> "AAAAAAAAoi"
 * "$PWD" -> /home/user
 * '$PWD' -> $PWD
 */
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


void	ms_tokenizer(t_ms *ms)
{
	ms_check_quotes(ms);
	ms->shell_line_tokenized = ft_str_replace_all(ms->shell_line, " && ", T_CONNECTOR);
	ms->shell_line_tokenized = ft_str_replace_all(ms->shell_line_tokenized, " | ", T_PIPE);
	ms->shell_line_tokenized = ft_str_replace_all(ms->shell_line_tokenized, ft_chr_to_str('~', 1), ms_get_home_value(ms));
}
