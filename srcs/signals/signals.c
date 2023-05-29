#include <minishell.h>

void	handle_signals(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		rl_done = 1;
	}
}

void	sig_catcher(t_shell *sh)
{
	rl_catch_signals = 0;
	sigemptyset(&sh->sig.sa_mask);
	sh->sig.sa_handler = &handle_signals;
	sh->sig.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sh->sig, NULL);
	sigaction(SIGQUIT, &sh->sig, NULL);
}