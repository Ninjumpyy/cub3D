/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonus2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:50:29 by rpandipe          #+#    #+#             */
/*   Updated: 2024/03/09 12:06:42 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*add_plus(char *ans, int len, int width)
{
	char	*new;
	int		size;

	size = width;
	if (len > width)
		size = len;
	new = (char *)ft_calloc(size + 2, sizeof(char));
	new[0] = '+';
	ft_strlcpy(new + 1, ans, len + 1);
	free(ans);
	return (new);
}

void	plus_operations(char *ans, int len, int width, char flag)
{
	if (flag == '0')
	{
		ft_memmove(ans + 1 + (width - len), ans + 1, len - 1);
		ft_memset(ans + 1, '0', (size_t)(width - len));
	}
	else
	{
		ft_memmove(ans + (width - len), ans, len);
		ft_memset(ans, ' ', (size_t)(width - len));
	}
}

void	ft_plussign(va_list *ap, int *count, const char **format, char prev)
{
	int		width;
	char	c;
	char	*ans;
	int		len;

	if ((*format)[1] == '0' || prev == '0')
		prev = '0';
	width = get_width(format);
	c = **format;
	ans = b_format_sorter((char []){c, '+'}, ap, \
							(int *[]){&width, count}, format);
	if (c != **format)
		return ;
	len = ft_strlen(ans);
	if (check_negative(ans) == 0)
		ans = add_plus(ans, len, width);
	len = ft_strlen(ans);
	if (len < width)
	{
		plus_operations(ans, len, width, prev);
	}
	ft_putstr_count(ans, count);
	free (ans);
}

void	deal_minus(char *ans, int width, int len, char flag)
{
	if (flag != '-')
	{
		ft_memmove(ans + (width - len), ans, len);
		ft_memset(ans, ' ', (size_t)(width - len));
	}
	else
		ft_memset(ans + len, ' ', (size_t)(width - len));
}

void	ft_hashsign(va_list *ap, int *count, const char **format, char prev)
{
	int		width;
	char	c;
	char	*ans;
	int		len;

	if ((*format)[1] == '-' || prev == '-')
		prev = '-';
	if (*(*format + 1) != '0')
		width = get_width(format);
	else
		(*format)++;
	c = **format;
	ans = b_format_sorter((char []){c, '#'}, ap, \
							(int *[]){&width, count}, format);
	if (c != **format)
		return ;
	len = ft_strlen(ans);
	if (len < width)
		deal_minus(ans, width, len, prev);
	ft_putstr_count(ans, count);
	free (ans);
}
