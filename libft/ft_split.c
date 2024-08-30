/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:35:51 by rpandipe          #+#    #+#             */
/*   Updated: 2024/02/23 16:12:45 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	word_count(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

char	*word_split(char const *s, char c)
{
	size_t	count;
	int		i;
	char	*word;

	count = 0;
	i = 0;
	while (s[i] && s[i] != c)
	{
		count++;
		i++;
	}
	word = (char *)malloc(sizeof(char) * count + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, s, count + 1);
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;

	i = 0;
	arr = (char **)malloc((word_count(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			arr[i] = word_split(s, c);
			if (!arr[i])
				return (NULL);
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	arr[i] = 0;
	return (arr);
}
