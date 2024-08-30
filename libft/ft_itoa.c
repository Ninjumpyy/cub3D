/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:31:43 by rpandipe          #+#    #+#             */
/*   Updated: 2024/02/23 11:24:02 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	int_count(int n)
{
	size_t	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		count++;
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

int	ft_abs(int n)
{
	if (n < 0)
		n *= -1;
	return (n);
}

char	*ft_itoa(int n)
{
	char	*ans;
	size_t	count;

	count = int_count(n);
	ans = (char *)malloc(sizeof(char) * (count + 1));
	if (!ans)
		return (NULL);
	ans[count] = '\0';
	count--;
	if (n == 0)
		ans[0] = '0';
	if (n < 0)
		ans[0] = '-';
	while (n != 0)
	{
		ans[count] = ft_abs(n % 10) + '0';
		n = n / 10;
		count--;
	}
	return (ans);
}
