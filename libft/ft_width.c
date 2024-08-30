/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_width.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:21:31 by rpandipe          #+#    #+#             */
/*   Updated: 2024/03/09 12:19:59 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*deal_d(char *ans, int len, int width)
{
	char	*new;

	if (len >= width)
	{
		width = len + 1;
		new = (char *)ft_calloc((width + 1), sizeof(char));
		ft_strlcpy(new, ans, len + 1);
		free(ans);
		ans = new;
	}
	ft_memmove((ans + (width - len)), ans, len);
	ft_memset(ans, ' ', (size_t)(width - len));
	return (ans);
}

int	check_null(char *ans)
{
	int	flag;

	flag = 0;
	if (ans[0] == 0)
		flag = 1;
	return (flag);
}

void	deal_c(char *ans, char c, int *count, int width)
{
	int		len;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	len = ft_strlen(ans);
	if (c == 'c')
		flag = check_null(ans);
	if (len < width)
	{
		ft_memmove(ans + (width - len), ans, len);
		ft_memset(ans, ' ', (size_t)(width - len));
	}
	if (c == 'c' && flag == 1)
	{
		while ((size_t)i < (ft_strlen(ans) - 1))
		{
			*count += write(1, &ans[i], 1);
			i++;
		}
		*count += write(1, "\0", 1);
	}
	else
		ft_putstr_count(ans, count);
}

void	ft_printspaces(va_list *ap, int *count, const char **format)
{
	int		width;
	char	c;
	char	*ans;
	int		len;
	char	flag;

	flag = **format;
	if (flag != ' ')
		(*format)--;
	if (*(*format + 1) != '0')
		width = get_width(format);
	else
		(*format)++;
	c = **format;
	ans = b_format_sorter((char []){c, ' '}, ap, \
							(int *[]){&width, count}, format);
	if (c != **format)
		return ;
	len = ft_strlen(ans);
	if ((width == 0 || flag == ' ') && \
		(c == 'd' || c == 'i') && !(check_negative(ans)))
		ans = deal_d(ans, len, width);
	deal_c(ans, c, count, width);
	free (ans);
}
