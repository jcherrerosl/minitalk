/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printerror.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanherr <juanherr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 11:41:31 by juanherr          #+#    #+#             */
/*   Updated: 2024/10/27 14:56:15 by juanherr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printerror(char *error_msg)
{
	ft_putstr_fd("\033[31mError: ", 2);
	ft_putendl_fd(error_msg, 2);
	ft_putstr_fd("\033[0m", 2);
	exit(1);
}
