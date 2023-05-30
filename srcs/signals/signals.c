/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:27:35 by raghonya          #+#    #+#             */
/*   Updated: 2023/05/30 16:27:38 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	sig_catcher(t_shell *sh)
{
	rl_catch_signals = 0;
	sigemptyset(&sh->sig.sa_mask);
	sh->sig.sa_handler = &handle_signals;
	sh->sig.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sh->sig, NULL);
	sigaction(SIGQUIT, &sh->sig, NULL);
}
