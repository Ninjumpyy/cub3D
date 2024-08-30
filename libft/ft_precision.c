/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:03:14 by rpandipe          #+#    #+#             */
/*   Updated: 2024/03/08 15:41:37 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_prev_width(const char *format)
{
	int	width;

	width = 0;
	format++;
	while (ft_isdigit(*format))
	{
		width = (width * 10) + (*format - '0');
		format++;
	}
	return (width);
}

char	*check_prev(char *ans, int width, char prev, const char *dup)
{
	char	*new;
	int		len;

	len = ft_strlen(ans);
	prev = get_prev(prev, dup);
	new = (char *)ft_calloc(width + 1, sizeof(char));
	ft_strlcpy(new, ans, len + 1);
	free(ans);
	ans = new;
	if (prev == ' ' || prev == '0' || prev == '+' || prev == '#')
	{
		ft_memmove(ans + (width - len), ans, len);
		ft_memset(ans, ' ', (size_t)(width - len));
	}
	else
	{
		ft_memset(ans + len, ' ', (size_t)(width - len));
	}
	return (ans);
}

void	deal_precision(char *ans, char prev, const char *dup, int *count)
{
	int		len;
	int		width;

	len = ft_strlen(ans);
	while (*dup != '.')
		dup--;
	while (*dup != prev && *dup != '%')
		dup--;
	if (prev == '0' && (*(dup -1) > '0' && *(dup - 1) <= '9'))
	{
		dup--;
		while (*dup != prev)
			dup--;
	}
	width = get_prev_width(dup);
	ans = deal_plus(ans, width, dup);
	len = ft_strlen(ans);
	if (len < width)
	{
		ans = check_prev(ans, width, prev, dup);
	}
	ft_putstr_count(ans, count);
	free (ans);
}

void	special_case(char *ans, int width, char c)
{
	if ((c == 'd' || c == 'i' || c == 'u' || c == 'x' || c == 'X') \
		&& width == 0 && ans[0] == '0')
		ans[0] = 0;
}

void	ft_precision(va_list *ap, int *count, const char **format, char prev)
{
	int		width;
	char	c;
	char	*p_ans;
	char	*ans;
	int		len;

	width = get_width(format);
	c = **format;
	p_ans = b_format_sorter((char []){c, '.'}, ap, \
							(int *[]){&width, count}, format);
	len = ft_strlen(p_ans);
	if (c != **format)
		return ;
	if (c == 's' && len > width)
	{
		ans = p_str_special(p_ans, width);
	}
	else
		ans = p_ans;
	if (c == 'd' || c == 'i' || c == 'u' || c == 'x' || c == 'X')
		ans = padzeros(ans, width, len, '.');
	special_case(ans, width, c);
	deal_precision(ans, prev, *format, count);
}
