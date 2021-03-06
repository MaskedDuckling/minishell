/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:58:59 by user42            #+#    #+#             */
/*   Updated: 2022/03/21 21:25:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
		if (!g_is_running)
		{
			rl_redisplay();
		}
	}
	else if (signo == SIGQUIT)
	{
		if (g_is_running)
			write(1, "\b\b  \b\b", 6);
	}
}

int	sig_init(void)
{
	if (signal(SIGINT, signal_handler))
		return (1);
	if (signal(SIGQUIT, signal_handler))
		return (1);
	return (0);
}
