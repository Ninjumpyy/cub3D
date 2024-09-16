/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbraux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:01:05 by rpandipe          #+#    #+#             */
/*   Updated: 2024/03/09 11:22:54 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	int_u_count(unsigned int n)
{
	size_t	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*ft_u_itoa(unsigned int n)
{
	char	*ans;
	size_t	count;

	count = int_u_count(n);
	ans = (char *)malloc(sizeof(char) * (count + 1));
	if (!ans)
		return (NULL);
	ans[count] = '\0';
	count--;
	if (n == 0)
		ans[0] = '0';
	while (n != 0)
	{
		ans[count] = (n % 10) + '0';
		n = n / 10;
		count--;
	}
	return (ans);
}

int	check_negative(char *ans)
{
	int	i;

	i = 0;
	while (ans[i])
	{
		if (ans[i] == '-' || ans[i] == '+')
			return (1);
		i++;
	}
	return (0);
}

char	*add_x(char *ans, int len, int width, char *base)
{
	char	x;
	char	*temp;

	x = 'x';
	if (base[15] == 'F')
		x = 'X';
	if (width <= len + 2)
	{
		temp = ft_calloc(len + 3, sizeof(char));
		ft_strlcpy(temp, ans, len + 1);
		free(ans);
		ans = temp;
	}
	ft_memmove(ans + 2, ans, len);
	ans[0] = '0';
	ans[1] = x;
	return (ans);
}

char	*p_str_special(char *p_ans, int width)
{
	char	*ans;

	if (!(ft_strncmp(p_ans, "(null)", 8)))
	{
		ans = (char *)ft_calloc((1), sizeof(char));
		ans[0] = 0;
		free(p_ans);
	}
	else
	{
		ans = (char *)ft_calloc((width + 1), sizeof(char));
		ft_strlcpy(ans, p_ans, (width + 1));
		free(p_ans);
	}
	return (ans);
}
