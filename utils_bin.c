/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:22:33 by juanherr          #+#    #+#             */
/*   Updated: 2024/10/27 18:44:17 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*ft_itoa_bin(unsigned int n)
{
	char	*binary;
	int		i;

	binary = (char *)malloc(8 + 1);
	check_memory(binary);
	binary[8] = '\0';
	i = 7;
	while (i >= 0)
	{
		if (n % 2 == 1)
			binary[i] = '1';
		else
			binary[i] = '0';
		n = n / 2;
		i--;
	}
	return (binary);
}

char	*str_to_bin(const char *str)
{
	char	*binary;
	char	*char_bin;
	size_t	i;

	if (!str)
		return (NULL);
	binary = (char *)calloc(8 * ft_strlen(str) + 1, sizeof(char));
	check_memory(binary);
	i = 0;
	while (str[i])
	{
		char_bin = ft_itoa_bin(str[i]);
		if (!char_bin)
			return (ft_free(binary));
		ft_strlcat(binary, char_bin, 8 * ft_strlen(str) + 1);
		free(char_bin);
		i++;
	}
	return (binary);
}

void accumulate_bit(int signal, char *current_byte, int *bit_index)
{
    static char bit_position[8] = {128, 64, 32, 16, 8, 4, 2, 1};

    if (signal == SIGUSR1)
        *current_byte += bit_position[*bit_index];
    (*bit_index)++;
}

int	is_byte_complete(int *bit_index)
{
	if (*bit_index == 8)
	{
		*bit_index = 0;
		return (1);
	}
	return (0);
}
	
void	process_length_byte(char current_byte, size_t *length)
{
	if (current_byte >= '0' && current_byte <= '9')
		*length = (*length) * 10 + (current_byte - '0');
}
