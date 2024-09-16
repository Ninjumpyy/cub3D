/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:52:07 by rpandipe          #+#    #+#             */
/*   Updated: 2024/02/23 10:42:05 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	start = 0;
	if (*little == 0 || little == NULL)
		return ((char *)big);
	while (i < len && big[i] != 0)
	{
		j = 0;
		if (big[i] == little[j])
		{
			start = i;
			while ((i + j) < len && little[j] != 0 && little[j] == big[i + j])
				j++;
			if (little[j] == 0)
				return ((char *)(big + start));
		}
		i++;
	}
	return (NULL);
}
