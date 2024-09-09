/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:36:47 by tle-moel          #+#    #+#             */
/*   Updated: 2024/09/09 11:35:01 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parsing(char *filename, t_data *data)
{
	int		fd;
	char	*line;
	t_lst	*raw_map;

	fd = open(filename, O_RDONLY);
	check_fd(fd);
	init_data(data);
	parse_info(&line, fd, data);
	raw_map = NULL;
	if (get_raw_map(&line, fd, &raw_map))
	{
		free_lst(raw_map);
		err_parsing(&line, fd, data);
	}
	close(fd);
	parse_map(raw_map, data);
	return (0);
}

void	parse_info(char **line, int fd, t_data *data)
{
	int		info;
	int		i;

	info = 0;
	*line = get_next_line(fd);
	while (info < 6 && *line != NULL)
	{
		i = check_info(*line, data);
		if (i == -1)
			err_parsing(line, fd, data);
		else
			info += i;
		free(*line);
		*line = get_next_line(fd);
	}
	if (info != 6)
		err_parsing(line, fd, data);
}

void	init_player(t_player *player)
{
	player->flag = 0;
	player->x = -1;
	player->y = -1;
}

void	parse_map(t_lst *raw_map, t_data *data)
{
	int			width;
	int			height;
	t_player	player;
	t_lst		*ptr;

	width = 0;
	height = 0;
	init_player(&player);
	ptr = raw_map;
	while (ptr)
	{
		if (check_player_and_width(ptr->line, &width, &player, height))
			err_map(raw_map, data);
		height++;
		ptr = ptr->next;
	}
	if (player.flag == 0)
		err_map(raw_map, data);
	data->map = ft_calloc(height, sizeof(char *));
	if (data->map == NULL)
		err_map(raw_map, data);
	create_map(raw_map, data);
	free_lst(raw_map);
	if (!map_closed(data->map, width, height, player))
	{
		free_data(data);
		if (write(2, "Error: .cub file\n", 18) == -1)
			exit(1);
		exit(1);
	}
}

int	check_player_and_width(char *line, int *width, t_player *player, int curr_height)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		{
			if (player->flag == 1)
				return (1);
			player->flag = 1;
			player->x = i;
			player->y = curr_height;
		}
		i++;
	}
	if (i > *width)
		*width = i;
	return (0);
}

void	create_map(t_lst *raw_map, t_data *data)
{
	t_lst	*ptr;
	int		i;
	int		len;

	i = 0;
	ptr = raw_map;
	while (ptr)
	{
		len = ft_strlen(ptr->line);
		data->map[i] = malloc(len * sizeof(char));
		if (data->map[i] == NULL)
			err_map(raw_map, data);
		ft_strlcpy(data->map[i], ptr->line, len);
		ptr = ptr->next;
		i++;
	}
}

int	map_closed(char **map, int width, int height, t_player player)
{
	int	x;
	int	y;
	int	new_x;
	int	new_y;
	int	i;
	t_stack	*stack;
	int	visited[height][width];
	int	directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

	stack = NULL;
	ft_memset(visited, 0, sizeof(visited));
	push(&stack, player.x, player.y);
	while (stack)
	{
		pop(&stack, &x, &y);
		visited[y][x] = 1;
		i = 0;
		while (i < 4)
		{
			new_x = x + directions[i][0];
			new_y = y + directions[i][1];
			if (new_x < 0 || new_y < 0 || new_x >= width || new_y >= height || map[new_y][new_x] == ' ' || map[new_y][new_x] == '\n' || map[new_y][new_x] == '\0')
			{
				delete_stack(&stack);
				return (0);
			}
			else if (map[new_y][new_x] == '0' && !visited[new_y][new_x])
				push(&stack, new_x, new_y);
			i++;
		}
	}
	return (1);
}

void	push(t_stack **stack, int x, int y)
{
	t_stack	*new;
	t_stack	*tmp;

	new = malloc(sizeof(t_stack));
	new->x = x;
	new->y = y;
	new->next = NULL;
	if (*stack == NULL)
		*stack = new;
	else
	{
		tmp = *stack;
		*stack = new;
		(*stack)->next = tmp;
	}
}

void	pop(t_stack **stack, int *x, int *y)
{
	t_stack	*tmp;

	*x = (*stack)->x;
	*y = (*stack)->y;
	tmp = (*stack)->next;
	free(*stack);
	*stack = tmp;
}

void	delete_stack(t_stack **stack)
{
	t_stack	*tmp;

	while (*stack)
	{
		tmp = (*stack)->next;
		free(*stack);
		*stack = tmp;
	}
}