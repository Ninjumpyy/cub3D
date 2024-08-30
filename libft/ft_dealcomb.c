/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dealcomb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 12:08:50 by rpandipe          #+#    #+#             */
/*   Updated: 2024/03/09 12:22:00 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*deal_spcomb(char *ans, const char *dup, char c)
{
	int		width;
	char	*new;
	int		len;

	if (check_negative(ans) == 1)
		return (ans);
	while (*dup != '%')
		dup--;
	while (*dup != c)
		dup++;
	width = get_prev_width(dup);
	len = ft_strlen(ans);
	if (len + 1 > width)
		width = len + 1;
	new = (char *)ft_calloc((width + 1), sizeof(char));
	new[0] = ' ';
	ft_strlcpy(new + 1, ans, width + 1);
	free(ans);
	ans = new;
	return (ans);
}

char	*deal_hscomb(char *ans, const char *dup, char c)
{
	int		width;
	char	*new;
	int		len;
	char	x;

	x = 'X';
	if (check_negative(ans) == 1 || *ans == '0')
		return (ans);
	while (*dup != '%')
		dup--;
	while (*dup != c)
		dup++;
	width = get_prev_width(dup);
	if (*dup == 'x')
		x = 'x';
	len = ft_strlen(ans);
	if (len + 2 > width)
		width = len + 2;
	new = (char *)ft_calloc((width + 1), sizeof(char));
	new[0] = '0';
	new[1] = x;
	ft_strlcpy(new + 2, ans, width + 1);
	free(ans);
	ans = new;
	return (ans);
}

char	*deal_bonuscomb(char flag, char *ans, const char *dup, char prev)
{
	if (flag == ' ')
		ans = deal_spcomb(ans, dup, prev);
	else if (flag == '#')
		ans = deal_hscomb(ans, dup, prev);
	return (ans);
}
