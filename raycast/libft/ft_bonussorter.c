/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonussorter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:06:58 by rpandipe          #+#    #+#             */
/*   Updated: 2024/03/09 11:04:29 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*b_format_sorter(char c[2], va_list *ap, int *wc[2], \
							const char **format)
{
	char	*ans;
	int		w;

	ans = NULL;
	w = *wc[0];
	if (c[0] == 'c')
		ans = ft_putchar_str(va_arg(*ap, int), w);
	else if (c[0] == 's')
		ans = ft_putstr_str(va_arg(*ap, char *), w);
	else if (c[0] == 'p')
		ans = ft_putmem_str(va_arg(*ap, void *), w);
	else if (c[0] == 'd' || c[0] == 'i')
		ans = ft_putnbr_str(va_arg(*ap, int), w);
	else if (c[0] == 'u')
		ans = ft_putnbr_u_str(va_arg(*ap, unsigned int), w);
	else if (c[0] == 'X')
		ans = ft_pb_str(va_arg(*ap, unsigned int), "0123456789ABCDEF", w, c[1]);
	else if (c[0] == 'x')
		ans = ft_pb_str(va_arg(*ap, unsigned int), "0123456789abcdef", w, c[1]);
	else if (c[0] == '%')
		ans = ft_putchar_str('%', w);
	else
		*wc[1] += flag_sorter(c, ap, format);
	return (ans);
}
