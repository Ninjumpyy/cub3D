/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:02:41 by rpandipe          #+#    #+#             */
/*   Updated: 2024/02/21 11:28:29 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*ans;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen((char *)s1);
	s2len = ft_strlen((char *)s2);
	ans = (char *)malloc(sizeof(char) * (s1len + s2len + 1));
	if (!ans)
		return (NULL);
	ft_strlcpy(ans, s1, s1len + 1);
	ft_strlcat(ans, s2, s1len + s2len + 1);
	return (ans);
}
