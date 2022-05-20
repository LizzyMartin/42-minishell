#include    <minishell.h>

void    parse_env(t_ms *ms)
{
    // validar se tem mais de um =
	// pensar no caso: export FOO===BAR
	// a key deverá ser FOO e o value ==BAR (somente o primeiro = é válido)
    ms->p.envs = NULL;
}
