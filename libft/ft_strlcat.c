/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe@student.42luxembourg.lu>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 20:40:23 by rpandipe          #+#    #+#             */
/*   Updated: 2024/02/21 16:54:29 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	j;
	size_t	i;
	size_t	rt;
	size_t	srclen;

	i = 0;
	j = 0;
	srclen = ft_strlen(src);
	i = ft_strlen((const char *)dest);
	if (size <= i)
		rt = srclen + size;
	else
		rt = srclen + i;
	if (size == 0)
		return (rt);
	while (i < size - 1 && src[j] != 0)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = 0;
	return (rt);
}
