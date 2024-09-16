/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:03:56 by rpandipe          #+#    #+#             */
/*   Updated: 2024/03/09 11:04:17 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	format_sorter(char c, va_list *ap, int *count, const char **format)
{
	if (c == 'c')
		ft_putchar_count(va_arg(*ap, int), count);
	else if (c == 's')
		ft_putstr_count(va_arg(*ap, char *), count);
	else if (c == 'p')
		ft_putmem_count(va_arg(*ap, void *), count);
	else if (c == 'd' || c == 'i')
		ft_putnbr_count(va_arg(*ap, int), count);
	else if (c == 'u')
		ft_putnbr_u_count(va_arg(*ap, unsigned int), count);
	else if (c == 'X')
		ft_putnbr_base(va_arg(*ap, unsigned int), "0123456789ABCDEF", count);
	else if (c == 'x')
		ft_putnbr_base(va_arg(*ap, unsigned int), "0123456789abcdef", count);
	else if (c == '%')
		ft_putchar_count('%', count);
	else
		*count += flag_sorter((char []){c, 'N'}, ap, format);
}

int	flag_sorter(char c[2], va_list *ap, const char **format)
{
	int	tempcount;

	tempcount = 0;
	if (c[0] == '-')
		ft_leftjust(ap, &tempcount, format, c[1]);
	else if (c[0] == '0')
		ft_zeropad(ap, &tempcount, format, c[1]);
	else if (c[0] == '.')
		ft_precision(ap, &tempcount, format, c[1]);
	else if (ft_isdigit(c[0]) || c[0] == ' ')
		ft_printspaces(ap, &tempcount, format);
	else if (c[0] == '+')
		ft_plussign(ap, &tempcount, format, c[1]);
	else if (c[0] == '#')
		ft_hashsign(ap, &tempcount, format, c[1]);
	else
		(*format)--;
	return (tempcount);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	count = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
			format_sorter(*(++format), &ap, &count, &format);
		else
			count += write(1, format, 1);
		format++;
	}
	va_end(ap);
	return (count);
}
