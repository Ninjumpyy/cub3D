/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:40:06 by rpandipe          #+#    #+#             */
/*   Updated: 2024/03/06 15:25:28 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_count(char c, int *count)
{
	ft_putchar_fd(c, 1);
	(*count)++;
}

void	ft_putstr_count(char *str, int *count)
{
	if (!str)
	{
		(*count) += write(1, "(null)", 6);
		return ;
	}
	ft_putstr_fd(str, 1);
	(*count) += ft_strlen(str);
}
