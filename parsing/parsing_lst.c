/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:32:30 by thomas            #+#    #+#             */
/*   Updated: 2024/09/19 16:28:08 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	add_node(char *line, t_lst **map_lst)
{
	t_lst	*new;
	t_lst	*ptr;

	new = malloc(sizeof(t_lst));
	if (new == NULL)
		return (0);
	new->next = NULL;
	new->line = ft_strdup(line);
	if (new->line == NULL)
	{
		free(new);
		return (0);
	}
	if (*map_lst == NULL)
		*map_lst = new;
	else
	{
		ptr = *map_lst;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
	return (1);
}

void	skip_empty_lines(char **line, int fd)
{
	while (*line && empty_line(*line))
	{
		free(*line);
		*line = get_next_line(fd);
	}
}

int	get_map_lst(char **line, int fd, t_lst **map_lst)
{
	skip_empty_lines(line, fd);
	if (*line == NULL)
		return (0);
	while (*line)
	{
		if (!valid_line(*line))
			return (0);
		if (empty_line(*line))
			break ;
		if (!add_node(*line, map_lst))
			return (0);
		free(*line);
		*line = get_next_line(fd);
	}
	skip_empty_lines(line, fd);
	if (*line != NULL)
		return (0);
	return (1);
}

