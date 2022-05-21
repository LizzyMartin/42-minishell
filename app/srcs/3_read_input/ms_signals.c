#include <minishell.h>

/*  
	 SIGINT: CTRL + C 
    SIGQUIT: CTRL + D
	SIG_IGN: ignore signal
*/
static void ctrl_c_redisplay_prompt(int signal)
{
	(void)signal;
	ft_printf("\n");
	ms_print_sh_name();
}

static void ctrl_c_interrupt_process(int signal)
{
	(void)signal;
}

void ctrl_d_exit_shell(int signal)
{
	(void)signal;
	ft_printf("exit\n");
}

void ctrl_d_quit_process(int signal)
{
	(void)signal;
	ft_printf("Quit (Core Dumped)\n");
}

/* Signals while ms is reading input */
void	ms_read_input_signals(void)
{
	signal(SIGINT, ctrl_c_redisplay_prompt);
}

/* Signals while some process is being executed  */
void	ms_execute_command_signals(void)
{
	signal(SIGINT, ctrl_c_interrupt_process);
	signal(SIGQUIT, ctrl_d_quit_process);
}
