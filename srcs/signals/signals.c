#include <minishell.h>

void	handle_signals(int signum)
{
	//printf ("wait = %d\n", waitpid(-1, NULL, WNOHANG));
	if (signum == SIGINT)
	{
		//printf ("ste el hasanq\n");
		rl_replace_line("", 0);
		rl_done = 1;
	}
	else if (signum == SIGQUIT)
	{
		printf ("dcgfvthj");
		return ;
	}
	//printf ("funckicayi verj\n");
}

void	sig_catcher(t_shell *sh)
{
	sigemptyset(&sh->sig.sa_mask);
	sh->sig.sa_handler = &handle_signals;
	sh->sig.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sh->sig, NULL);
	sigaction(SIGQUIT, &sh->sig, NULL);
}