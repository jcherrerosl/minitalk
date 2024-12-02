/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:28:20 by juanherr          #+#    #+#             */
/*   Updated: 2024/12/02 15:29:58 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_message(int server_pid, char *message)
{
	int	bit;
	int	byte;
	int	i;

	bit = 0;
	i = 0;
	while (message[i])
	{
		byte = message[i];
		while (bit < 8)
		{
			if (byte << bit & 0b10000000)
			{
				if (kill(server_pid, SIGUSR1) == -1)
					ft_printerror("Failed to send signal to server");
			}
			else if (kill(server_pid, SIGUSR2) == -1)
				ft_printerror("Failed to send signal to server");
			bit++;
			usleep(100);
		}
		i++;
		bit = 0;
	}
}

// void	send_len(int server_pid, size_t len)
// {
// 	char *len_char;

// 	len_char = ft_itoa(len);
// 	if (!len_char)
// 		ft_printerror("Failed to convert message length to string");
// 	send_message(server_pid, len_char);
// 	send_message(server_pid, "\n");
// 	free(len_char);
// }

void	sig_handler(int sig)
{
	static int	message_printed = 0;

	if (!message_printed)
	{
		if (sig == SIGUSR1)
		{
			ft_printf("The signal was received successfully.\n");
			message_printed = 1;
		}
	}
}

int	main(int argc, char *argv[])
{
	int					server_pid;
	struct sigaction	sa;

	if (argc != 3)
		ft_printerror(USAGE);
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
		ft_printerror("Invalid server PID");
	sa.sa_handler = &sig_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	send_message(server_pid, argv[2]);
	return (0);
}
