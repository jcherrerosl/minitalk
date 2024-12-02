/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:46:17 by juanherr          #+#    #+#             */
/*   Updated: 2024/12/02 15:30:39 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int signal, siginfo_t *info, void *context)
{
	static int				bit = 0;
	static unsigned char	byte = 0;

	(void)context;
	if (signal == SIGUSR1)
		byte = byte << 1 | 1;
	else if (signal == SIGUSR2)
		byte = byte << 1;
	bit++;
	if (bit == 8)
	{
		ft_printf("%c", byte);
		byte = 0;
		bit = 0;
		if (kill(info->si_pid, SIGUSR1) == -1)
			ft_printerror("Failed to send signal to client");
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server PID: %d\n", getpid());
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
