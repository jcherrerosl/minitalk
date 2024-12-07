/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaherre <juaherre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:39:45 by juanherr          #+#    #+#             */
/*   Updated: 2024/12/07 21:24:18 by juaherre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include "libft/libft.h"
# include <signal.h>

# ifndef USAGE
#  define USAGE "Usage: ./client [server_pid] [message]\n"
# endif // USAGE

void		send_message(int server_pid, char *message);
char		*ft_itoa_bin(unsigned int n);
char		*str_to_bin(const char *str);
void		*ft_free(void *ptr);
void		check_memory(void *ptr);
int			is_byte_complete(int *bit_index);
void		process_length_byte(char current_byte, size_t *length);
void		accumulate_bit(int signal, char *current_byte, int *bit_index);

// Server.c

size_t		receive_length(int signal);
void		receive_message(int signal, char **buffer, size_t message_len, int *state);
void		signal_handler(int signal, siginfo_t *info, void *context);

#endif // MINITALK_H
