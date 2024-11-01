/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:20:17 by gemartin          #+#    #+#             */
/*   Updated: 2024/10/27 19:59:05 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

size_t	receive_length(int signal)
{
	static int		bit_index = 0;
	static size_t	length = 0;
	static char		current_byte = 0;
	size_t			result;

	result = 0;
	accumulate_bit(signal, &current_byte, &bit_index);
	if (is_byte_complete(&bit_index))
	{
		if (current_byte == '\n')
		{
			result = length;
			ft_printf("Longitud recibida: %u\n", result);
			length = 0;
			current_byte = 0;
			return (result);
		}
		else
		{
			process_length_byte(current_byte, &length);
			current_byte = 0;
		}
	}
	return (0);
}

void	receive_message(int signal, char **buffer, size_t message_len)
{
	static int		bit_index = 0;
	static size_t	bytes_received = 0;
	static char		current_byte = 0;
	static char		bit_position[8] = {128, 64, 32, 16, 8, 4, 2, 1};

	if (signal == SIGUSR1)
		current_byte += bit_position[bit_index];
	bit_index++;
	if (bit_index == 8)
	{
		(*buffer)[bytes_received] = current_byte;
		bytes_received++;
		bit_index = 0;
		current_byte = 0;
	}
	if (bytes_received == message_len)
	{
		ft_printf("%s\n", *buffer);
		ft_free(*buffer);
		bytes_received = 0;
	}
}

void	signal_handler(int signal, siginfo_t *info, void *context)
{
	static size_t	length = 0;
	static int		state = 0;
	static char		*buffer = NULL;
	

	(void)info;
	(void)context;
	if (state == 0)
	{
		length = receive_length(signal);
		if (length != 0)
		{
			buffer = (char *)malloc(length + 1);
			check_memory(buffer);
			buffer[length] = '\0';
			state = 1;
		}
	}
	else if (state == 1)
	{
		receive_message(signal, &buffer, length);
		if (buffer == NULL)
			state = 0;
	}
}

int	main(void)
{
	struct sigaction sa;

	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	ft_printf("Server PID: %d\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}