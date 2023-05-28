#include <minishell.h>



void	handle_signals(int signum)
{
	//printf ("wait = %d\n", waitpid(-1, NULL, WNOHANG));
	if (signum == SIGINT && waitpid(-1, NULL, WNOHANG) == -1)
	{
		//printf ("ste el hasanq\n");
		rl_replace_line("", 0);
		rl_done = 1;
		//printf ("\n");
		//rl_on_new_line();
		//if (wait(NULL) == -1)
		//rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		return ;
	}
	rl_done = 0;
	//printf ("funckicayi verj\n");
}

void	sig_catcher(t_shell *sh)
{
	sh->sig.sa_handler = &handle_signals;
	sigaction(SIGINT, &sh->sig, NULL);
	sigaction(SIGQUIT, &sh->sig, NULL);
}