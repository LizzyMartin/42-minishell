#ifndef MINISHELL_H
# define MINISHELL_H

/* includes */
# include			<stdio.h>
# include			<readline/readline.h>
# include			<readline/history.h>
# include			<stdlib.h>
# include			<unistd.h>
# include			"../libs/libft/srcs/libft.h"

/* macros */


/* structs */
typedef struct s_minishell
{
	int		argc;
	char	**argv;
	char	**envp;
	int		exit_status;
	char	*line;
	char	**line_splited;
} t_ms;

/* builtins */
int			ms_cd(t_ms *ms);
int			ms_echo(t_ms *ms);
int			ms_env(t_ms *ms);
void		ms_exit(t_ms *ms);
int			ms_export(t_ms *ms);
int			ms_pwd(t_ms *ms);
int			ms_unset(t_ms *ms);

/* design */
void		ms_banner();


/* execute */
void		execute(t_ms *ms);

/* init */
int		init(t_ms *ms);

/* parse */
int			parse(t_ms *ms);

/* ms */
int			minishell(int argc, char **argv, char **envp);

#endif
