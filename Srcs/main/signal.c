/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eydupray <eydupray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:58:59 by user42            #+#    #+#             */
/*   Updated: 2022/03/15 18:09:30 by eydupray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_is_running;

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		//rl_on_new_line();
		//rl_replace_line("", 0);
		if (!g_is_running)
			rl_redisplay();
	}
	else if (signo == SIGQUIT)
		write(1, "\b\b  \b\b", 6);
}

int	sig_init(void)
{
	if (signal(SIGINT, signal_handler))
		return (1);
	if (signal(SIGQUIT, signal_handler))
		return (1);
	return (0);
}
