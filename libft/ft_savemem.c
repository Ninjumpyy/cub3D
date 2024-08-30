/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_savemem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:48:37 by rpandipe          #+#    #+#             */
/*   Updated: 2024/03/06 12:32:09 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*add_nil(int width)
{
	char	*ans;
	int		len;

	len = ft_strlen("(nil)");
	if (width == 0 || width < len)
		width = len;
	ans = (char *)ft_calloc(width + 1, sizeof(char));
	ft_strlcpy(ans, "(nil)", width + 1);
	return (ans);
}

static char	*ft_mltoa(char *ans, void *ptr)
{
	unsigned long long int	address;
	int						i;
	int						size;

	size = 0;
	address = (unsigned long long int)ptr;
	while (address != 0)
	{
		size++;
		address /= 16;
	}
	ans = (char *)ft_calloc((size + 3), sizeof(char));
	ans[0] = '0';
	ans[1] = 'x';
	ans[size + 2] = 0;
	i = size + 1;
	address = (unsigned long long int)ptr;
	while (address != 0)
	{
		ans[i] = "0123456789abcdef"[address % 16];
		address /= 16;
		i--;
	}
	return (ans);
}

char	*ft_putmem_str(void *ptr, int width)
{
	unsigned long long int	address;
	char					*ans;
	char					*temp;
	int						size;

	size = 0;
	address = (unsigned long long int)ptr;
	if (address == 0)
		return (add_nil(width));
	while (address != 0)
	{
		size++;
		address /= 16;
	}
	if (width == 0 || width < (size + 2))
		width = size + 2;
	ans = (char *)ft_calloc((width + 1), sizeof(char));
	if (!ans)
		return (NULL);
	temp = ft_mltoa(ans, ptr);
	ft_strlcpy(ans, temp, width + 1);
	free (temp);
	return (ans);
}
