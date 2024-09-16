/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:14:53 by rpandipe          #+#    #+#             */
/*   Updated: 2024/09/10 11:05:55 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*read_line(int fd, char *line)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && ft_strchr_num(line, '\n'))
	{
		ft_setzero(buffer, BUFFER_SIZE);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free (buffer);
			if (line)
				return (line);
			return (NULL);
		}
		buffer[bytes_read] = 0;
		line = ft_strjoin_r((char *)line, (char *)buffer);
	}
	free(buffer);
	return (line);
}

char	*save_newline(char *line)
{
	int		i;
	char	*ans;

	i = 0;
	while (line[i] != '\n' && line[i])
		i++;
	if (line[i] == '\n')
		i++;
	ans = (char *)malloc(sizeof(char) * (i + 1));
	if (!ans)
		return (NULL);
	i = 0;
	while (line[i] != '\n' && line[i])
	{
		ans[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
		ans[i++] = '\n';
	ans[i] = 0;
	return (ans);
}

char	*save_oldline(char *line)
{
	int		i;
	int		j;
	int		len;
	char	*oldline;

	i = 0;
	j = 0;
	len = ft_strlen(line);
	while (line[i] != '\n' && line[i])
		i++;
	if (line[i] == '\n')
		i++;
	if (!line[i])
	{
		free (line);
		return (NULL);
	}
	oldline = (char *)malloc(sizeof(char) * (len - i) + 1);
	if (!oldline)
		return (NULL);
	while (line[i])
		oldline[j++] = line[i++];
	oldline[j] = 0;
	free (line);
	return (oldline);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*ans;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_line(fd, line);
	if (!line)
		return (NULL);
	ans = save_newline(line);
	line = save_oldline(line);
	return (ans);
}
