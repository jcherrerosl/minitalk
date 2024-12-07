/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaherre <juaherre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:28:20 by juanherr          #+#    #+#             */
/*   Updated: 2024/12/07 22:09:50 by juaherre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_message(int server_pid, char *message)
{
	char	*binary;
	int		result;
	size_t	i;

	binary = str_to_bin(message);
	if (!binary)
		ft_printerror("Failed to convert message to binary");
	i = 0;
	while (binary[i])
	{
		if (binary[i] == '1')
			result = kill(server_pid, SIGUSR1);
		else if (binary[i] == '0')
			result = kill(server_pid, SIGUSR2);
		else
			ft_printerror("Invalid binary character");
		if (result == -1)
			ft_printerror("Proccess not found");
		usleep(100);
		i++;
	}
	free(binary);
}

void	send_len(int server_pid, size_t len)
{
	char	*len_char;

	len_char = ft_itoa(len);
	if (!len_char)
		ft_printerror("Failed to convert message length to string");
	send_message(server_pid, len_char);
	send_message(server_pid, "\n");
	free(len_char);
}

void	ack_handler(int signal)
{
	if (signal == SIGUSR1)
	{
		ft_printf("Message received by server\n");
		exit(0);
	}
}

int	main(int argc, char *argv[])
{
	struct sigaction	sa;
	int					server_pid;
	size_t				len;

	if (argc != 3)
		ft_printerror(USAGE);
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
		ft_printerror("Invalid PID");
	len = ft_strlen(argv[2]);
	sa.sa_handler = ack_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		ft_printerror("Failed to set up SIGUSR1 handler");
	send_len(server_pid, len);
	send_message(server_pid, argv[2]);
	while (1)
		pause();
	return (0);
}
