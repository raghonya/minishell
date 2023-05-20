#include <minishell.h>


void	handle_signals(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		printf ("\n");
		rl_on_new_line();
		if (wait(NULL) == -1)
			rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		return ;
	}
}

void	sig_catcher(t_shell *sh)
{
	sh->sig.sa_handler = &handle_signals;
	sigaction(SIGINT, &sh->sig, NULL);
	sigaction(SIGQUIT, &sh->sig, NULL);
}