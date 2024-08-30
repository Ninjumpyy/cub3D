/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_savestr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 09:20:32 by rpandipe          #+#    #+#             */
/*   Updated: 2024/03/07 11:29:40 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_putchar_str(char c, int width)
{
	char	*ans;
	int		i;

	i = 1;
	if (width == 0)
		width = 1;
	ans = (char *)malloc(sizeof(char) * (width + 1));
	if (!ans)
		return (NULL);
	ans[0] = c;
	while (i <= width)
	{
		ans[i] = 0;
		i++;
	}
	return (ans);
}

char	*ft_putstr_str(char *str, int width)
{
	char	*ans;
	int		len;

	if (!str)
	{
		if (width < 6)
			width = 6;
		ans = (char *)ft_calloc(width + 1, sizeof(char));
		ft_strlcpy(ans, "(null)", 6 + 1);
		return (ans);
	}
	len = ft_strlen(str);
	if (width == 0 || width < len)
		width = len;
	ans = (char *)ft_calloc((width + 1), sizeof(char));
	if (!ans)
		return (NULL);
	ft_strlcpy(ans, str, width + 1);
	return (ans);
}
