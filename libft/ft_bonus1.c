/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonus1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:38:05 by rpandipe          #+#    #+#             */
/*   Updated: 2024/03/09 12:38:10 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_width(const char **format)
{
	int	width;

	width = 0;
	(*format)++;
	while (ft_isdigit(**format))
	{
		width = (width * 10) + (**format - '0');
		(*format)++;
	}
	return (width);
}

char	*padzeros(char *ans, int width, int len, char flag)
{
	int		offset;
	char	*new;

	offset = check_negative(ans);
	if (flag == ' ')
		offset = 1;
	if (offset == 1 && flag == '.')
	{
		width = width + 1;
		if (len < width)
		{
			new = (char *)ft_calloc(width + 1, sizeof(char));
			ft_strlcpy(new, ans, width + 1);
			free(ans);
			ans = new;
		}
	}
	if (len < width)
	{
		ft_memmove(ans + offset + (width - len), ans + offset, len - offset);
		ft_memset(ans + offset, '0', (size_t)(width - len));
	}
	return (ans);
}

void	ft_leftjust(va_list *ap, int *count, const char **format, char prev)
{
	int		width;
	char	c;
	char	*ans;
	int		len;

	width = get_width(format);
	c = **format;
	ans = b_format_sorter((char []){c, '-'}, ap, \
							(int *[]){&width, count}, format);
	if (c != **format)
		return ;
	if (ans[0] == 0 && c == 'c')
	{
		write(1, "\0", 1);
		*count += 1;
		width -= 1;
	}
	if (c == 'd' || c == 'i' || c == 'x' || c == 'X')
		ans = deal_bonuscomb(prev, ans, *format, '-');
	len = ft_strlen(ans);
	if (len < width)
		ft_memset(ans + len, ' ', (size_t)(width - len));
	ft_putstr_count(ans, count);
	free (ans);
}

int	deal_char(va_list *ap, int *count, const char **format, char c)
{
	if (c == 'c' || c == 's' || c == 'p')
	{
		while (**format != '0' || ft_isdigit(*(*format -1)))
			(*format)--;
		ft_printspaces(ap, count, format);
		return (1);
	}
	return (0);
}

void	ft_zeropad(va_list *ap, int *count, const char **format, char flag)
{
	int		width;
	char	c;
	char	*ans;
	int		len;

	width = get_width(format);
	c = **format;
	if (deal_char(ap, count, format, c) == 1)
		return ;
	ans = b_format_sorter((char []){c, '0'}, ap, \
							(int *[]){&width, count}, format);
	if (c != **format)
		return ;
	if (c == 'd' || c == 'i' || c == 'x' || c == 'X')
		ans = deal_bonuscomb(flag, ans, *format, '0');
	len = ft_strlen(ans);
	if (len < width)
	{
		if (flag == '-')
			ft_memset(ans + len, '0', (size_t)(width - len));
		else
			ans = padzeros(ans, width, len, flag);
	}
	ft_putstr_count(ans, count);
	free (ans);
}
