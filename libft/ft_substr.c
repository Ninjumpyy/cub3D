/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandie@student.42luxembourg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 09:43:19 by rpandipe          #+#    #+#             */
/*   Updated: 2024/02/23 12:41:31 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		slen;
	size_t		dlen;
	char		*ans;

	if (!s)
		return (NULL);
	slen = ft_strlen((char *)s);
	if (start > slen)
	{
		ans = (char *)malloc(sizeof(char));
		if (!ans)
			return (NULL);
		ans[0] = 0;
		return (ans);
	}
	dlen = ft_strlen(((char *)s + start));
	if (len > dlen)
		len = dlen;
	ans = (char *)malloc(sizeof(char) * len + 1);
	if (!ans)
		return (NULL);
	ft_strlcpy(ans, s + start, len + 1);
	return (ans);
}
