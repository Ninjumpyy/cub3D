/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plusaux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:24:45 by rpandipe          #+#    #+#             */
/*   Updated: 2024/03/08 15:51:43 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_zeros(char *ans)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (ans[i] != 0)
	{
		if (ans[i] != '0')
			flag = 1;
		i++;
	}
	return (flag);
}

char	*deal_plus_c(char *ans, int width, char *flags, char c)
{
	char	chk;
	char	spchk;
	char	hschk;
	int		len;
	char	*base;

	chk = flags[0];
	spchk = flags[1];
	hschk = flags[2];
	len = ft_strlen(ans);
	base = "0123456789abcdef";
	if (c == 'X')
		base = "0123456789ABCDEF";
	if (hschk == '#' && (check_zeros(ans) == 1))
		ans = add_x(ans, len, 0, base);
	if (chk == '+' && !check_negative(ans) && hschk != '#')
		ans = add_plus(ans, len, width);
	if (spchk == ' ' && (c == 'd' || c == 'i') && !check_negative(ans))
		ans = add_space(ans, len, width);
	return (ans);
}

char	*deal_plus(char *ans, int width, const char *dup)
{
	char	chk;
	char	spchk;
	char	hschk;

	chk = *dup;
	spchk = *dup;
	hschk = *dup;
	while (*dup != '%')
		dup--;
	while (*dup != '.')
	{
		if (*dup == '+')
			chk = '+';
		else if (*dup == ' ')
			spchk = ' ';
		else if (*dup == '#')
			hschk = '#';
		dup++;
	}
	while (ft_isdigit(*dup) || *dup == '.')
		dup++;
	ans = deal_plus_c(ans, width, (char []){chk, spchk, hschk}, *dup);
	return (ans);
}

char	get_prev(char prev, const char *dup)
{
	while (*dup != '%')
		dup--;
	while (*dup != '.')
	{
		if (*dup == '-')
			prev = '-';
		dup++;
	}
	return (prev);
}

char	*add_space(char *ans, int len, int width)
{
	char	*new;
	int		size;

	size = width;
	if (len > width)
		size = len;
	new = (char *)ft_calloc(size + 2, sizeof(char));
	new[0] = ' ';
	ft_strlcpy(new + 1, ans, len + 1);
	free(ans);
	return (new);
}
