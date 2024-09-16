/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_savenbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:23:40 by rpandipe          #+#    #+#             */
/*   Updated: 2024/03/05 19:56:49 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_putnbr_str(int nbr, int width)
{
	char	*ans;
	char	*str;
	int		len;

	str = ft_itoa(nbr);
	len = ft_strlen(str);
	if (width == 0 || width < len)
		width = len;
	ans = (char *)ft_calloc((width + 1), sizeof(char));
	if (!ans)
		return (NULL);
	ft_strlcpy(ans, str, width + 1);
	free(str);
	return (ans);
}

char	*ft_putnbr_u_str(unsigned int nbr, int width)
{
	char	*ans;
	char	*str;
	int		len;

	str = ft_u_itoa(nbr);
	len = ft_strlen(str);
	if (width == 0 || width < len)
		width = len;
	ans = (char *)ft_calloc((width + 1), sizeof(char));
	if (!ans)
		return (NULL);
	ft_strlcpy(ans, str, width + 1);
	free(str);
	return (ans);
}

static void	base_count(unsigned long nbr, int *width)
{
	if (nbr >= 16)
	{
		base_count(nbr / 16, width);
	}
	(*width)++;
}

void	ft_savebase(unsigned int size, char *base, unsigned long nbr, char *ans)
{
	int		i;
	int		start;
	int		end;
	char	temp;

	i = 0;
	start = 0;
	while (nbr >= size)
	{
		ans[i++] = base[nbr % size];
		nbr /= size;
	}
	ans[i++] = base[nbr % size];
	end = i - 1;
	while (start < end)
	{
		temp = ans[start];
		ans[start] = ans[end];
		ans[end] = temp;
		start++;
		end--;
	}
	ans[i] = 0;
}

char	*ft_pb_str(unsigned int nbr, char *base, int width, char x)
{
	char				*ans;
	unsigned long		n;
	unsigned int		size;
	int					len;

	len = 0;
	n = (unsigned long)nbr;
	base_count(n, &len);
	if (width == 0 || width < len)
		width = len;
	ans = (char *)ft_calloc((width + 1), sizeof(char));
	if (!ans)
		return (NULL);
	size = 16;
	ft_savebase(size, base, n, ans);
	if (x == '#' && ft_strncmp(ans, "0", len))
		ans = add_x(ans, len, width, base);
	return (ans);
}
