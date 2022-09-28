/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:44:15 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/28 02:06:25 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

char	**nothing_before(int op, t_p *curr_prompt,
char **split_by_space, char *arg)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	if (split_by_space[1] == NULL) // << EOF
	{
		// ft_printf("A\n");
		if (op == 1)
			curr_prompt->only_here_doc = 1;
		else if (op == 2)
			curr_prompt->only_input_redirected_to_file = 1;
		return (split_by_space);
	}
	else // << EOF tr a b
	{
		// ft_printf("B\n");
		tmp = ft_strdup(curr_prompt->this_p_line_splited_by_pipe[0]);
		i += ft_str_indexof(tmp, arg, ft_strlen(tmp)) + ft_strlen(arg);
		tmp = ft_substr(tmp, i, ft_strlen(tmp));
		curr_prompt->this_p_line_splited_by_pipe[0] = tmp;
		split_by_space = ft_split(tmp, ' ');
		return (split_by_space);
	}
}

char	**something_before(t_p *curr_prompt,
char **split_by_space, char *arg, char *str_op)
{
	int		n;
	char	*tmp;

	if (split_by_space[1] != NULL) // cat << EOF tr a b
	{
		// ft_printf("C\n");
		tmp = ft_printf_to_var("%s %s", str_op, arg);
		curr_prompt->this_p_line_splited_by_pipe[0] = \
ft_str_replace(curr_prompt->this_p_line_splited_by_pipe[0], tmp, " ");
		split_by_space = \
ft_split(curr_prompt->this_p_line_splited_by_pipe[0], ' ');
		return (split_by_space);
	}
	else // cat << EOF
	{
		n = ft_mtx_size((void **) curr_prompt->this_p_line_splited_by_pipe);
		// ft_printf("D (%d)\n", n);
		if (n <= 1)
		{
			if (ft_strncmp(str_op, "<<", ft_strlen(str_op)) == 0)
				curr_prompt->only_here_doc = 2;
			else if (ft_strncmp(str_op, "<", ft_strlen(str_op)) == 0)
				curr_prompt->only_input_redirected_to_file = 2;
			return (split_by_space);
		}
		else
		{
			curr_prompt->dont_execute_first = 1;
			return (split_by_space);
		}
	}
}

static char	**here_doc_input_file(int op, t_p *curr_prompt)
{
	char	*str_op;
	char	**splited_by_chr;
	char	**split_by_space;
	char	*tmp;
	int		len;
	char	*arg;

	len = 0;
	tmp = NULL;
	splited_by_chr = NULL;
	split_by_space = NULL;
	if (op == 1)
		str_op = ft_strdup("<<");
	else
		str_op = ft_strdup("<");
	len = ft_strlen(curr_prompt->this_p_line_splited_by_pipe[0]);
	splited_by_chr = \
		ft_split_by_str(curr_prompt->this_p_line_splited_by_pipe[0], str_op);
	split_by_space = ft_split(splited_by_chr[1], ' ');
	tmp = ft_strdup(split_by_space[0]);
	if (op == 1)
	{
		curr_prompt->has_here_doc = 1;
		curr_prompt->hd_limiter = ft_strdup(tmp);
		arg = curr_prompt->hd_limiter;
	}
	else
	{
		curr_prompt->input_redirected_to_file = 1;
		curr_prompt->input_path = ft_strdup(tmp);
		arg = curr_prompt->input_path;
		curr_prompt->input_fd = open(curr_prompt->input_path, O_RDONLY);
		if (curr_prompt->input_fd == -1)
		{
			ft_pf_error("miniheaven: %s %s", curr_prompt->input_path, E_NOTDIR);
			ft_free_ptr((void *) &tmp);
			return (NULL);
		}
	}
	if (ft_strncmp(splited_by_chr[0], \
" ", ft_strlen(splited_by_chr[0])) == 0)
		return (nothing_before(op, curr_prompt, split_by_space, arg));
	else
		return (something_before(curr_prompt, split_by_space, arg, str_op));
	ft_free_ptr((void *) &tmp);
}

char	**ms_parse_input(t_p *curr_prompt)
{
	int		len;

	len = 0;
	len = ft_strlen(curr_prompt->this_p_line_splited_by_pipe[0]);
	curr_prompt->input_fd = 0;
	curr_prompt->input_path = NULL;
	curr_prompt->has_here_doc = 0;
	curr_prompt->only_here_doc = 0;
	curr_prompt->no_cmd_just_redirect = 0;
	curr_prompt->input_redirected_to_file = 0;
	curr_prompt->only_input_redirected_to_file = 0;
	if (ft_strnstr(curr_prompt->this_p_line_splited_by_pipe[0], "<<", len))
		return (here_doc_input_file(1, curr_prompt));
	else if (ft_strnstr(curr_prompt->this_p_line_splited_by_pipe[0], "<", len))
		return (here_doc_input_file(2, curr_prompt));
	else
		return (ft_split(curr_prompt->this_p_line_splited_by_pipe[0], ' '));
}
