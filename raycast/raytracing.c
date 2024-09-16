/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandie@student.42luxembourg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:13:58 by rpandipe          #+#    #+#             */
/*   Updated: 2024/09/17 00:38:49 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	destroy_mlx(t_data *data)
{
	if (data->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	if (data->win_ptr && data->mlx_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		//mlx_loop_end(data->mlx_ptr); //not available in mac
		//mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	exit(EXIT_SUCCESS);
}

void	re_render(t_data *data)
{
	if (data->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	draw_map(data);
}

int	is_wall(int x, int y, t_data *data)
{
	int	map_x;
	int	map_y;

	map_x = x / data->tile_size;
	map_y = y / data->tile_size;
	if (data->map[map_y * data->map_x + map_x] == 1)
		return (1);
	return (0);
}

int	handle_key(int keycode, t_data *data)
{
	double	new_px;
	double	new_py;

	new_px = data->player->px;
	new_py = data->player->py;
	if (keycode == 53) //ESC
		destroy_mlx(data);
	else if (keycode == 0 || keycode == 123) //a || left arrow
	{
		data->player->pa -= data->player->rot_speed;
		if (data->player->pa < 0)
			data->player->pa += 2 * PI;
		data->player->pdx = cos (data->player->pa) * data->player->speed;
		data->player->pdy = sin (data->player->pa) * data->player->speed;
	}
	else if (keycode == 13 || keycode == 126) //w
	{
		new_px += data->player->pdx;
		new_py += data->player->pdy;
	}
	else if (keycode == 1 || keycode == 125) //s
	{
		new_px -= data->player->pdx;
		new_py -= data->player->pdy;
	}
	else if (keycode == 2 || keycode == 124) //d
	{
		data->player->pa += data->player->rot_speed;
		if (data->player->pa > 2 * PI)
			data->player->pa -= 2 * PI;
		data->player->pdx = cos (data->player->pa) * data->player->speed;
		data->player->pdy = sin (data->player->pa) * data->player->speed;
	}
	else
		return (0);
	if (!is_wall(new_px, new_py, data))
	{
		data->player->px = new_px;
		data->player->py = new_py;
	}
	re_render(data);
	return (0);
}

void	events_init(t_data *data)
{
	mlx_hook(data->win_ptr, 2, 0, handle_key, data);
	//mlx_hook(data->win_ptr, 4, 0, handle_mouse, data);
	mlx_hook(data->win_ptr, 17, 0, destroy_mlx, NULL);
}

void	init_player(t_data *data)
{
	int	x;
	int	y;

	data->player->size = 10;
	data->player->speed = 10;
	data->player->rot_speed = 0.1;
	data->player->pa = 3 * PI / 2;
	data->player->pdx = cos (data->player->pa) * data->player->speed;
	data->player->pdy = sin (data->player->pa) * data->player->speed;
	data->player->line = 2;
	data->rays_count = 100;
	data->fov = 60 * (PI / 180);
	y = 0;
	while (y < data->map_y)
	{
		x = 0;
		while (x < data->map_x)
		{
			if (data->map[y * data->map_x + x] == 2)
			{
				data->player->px = (x + 0.5) * data->tile_size;
				data->player->py = (y + 0.5) * data->tile_size;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	color_tile(int x, int y, int color, t_data *data)
{
	int	img_x;
	int	img_y;
	int	tile_x;
	int	tile_y;

	tile_y = 0;
	while (tile_y < data->tile_size)
	{
		tile_x = 0;
		while (tile_x < data->tile_size)
		{
			img_x = x * data->tile_size + tile_x;
			img_y = y * data->tile_size + tile_y;
			if (img_x < WINDOW_WIDTH && img_y < WINDOW_HEIGHT)
				data->img_bfr[img_y * WINDOW_WIDTH + img_x] = color;
			tile_x++;
		}
		tile_y++;
	}
}

void draw_line(t_data *data, int x0, int y0)
{
	int	x1;
	int	y1;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	x1 = (int)x0 + data->player->pdx * data->player->line;
	y1 = (int) y0 + data->player->pdy * data->player->line;
	dx = abs(x1 -x0);
	dy = abs(y1 - y0);
	sx = -1;
	if (x0 < x1)
		sx = 1;
	sy = -1;
	if (y0 < y1)
		sy = 1;
	err = dx - dy;
    
    while (1)
    {
        if (x0 >= 0 && x0 < WINDOW_WIDTH && y0 >= 0 && y0 < WINDOW_HEIGHT)
            data->img_bfr[(int)y0 * WINDOW_WIDTH + (int)x0] = 0xFF0000;

        if (x0 == x1 && y0 == y1)
            break;
        
        e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void	draw_player(t_data *data)
{
	double	x;
	double	y;
	int	px;
	int	py;

	y = -(data->player->size) / 2;
	while (y < data->player->size / 2)
	{
		x = -(data->player->size) / 2;
		while (x < data->player->size / 2)
		{
			px = (int) data->player->px + x;
			py = (int) data->player->py + y;
			if (px < WINDOW_WIDTH && py < WINDOW_HEIGHT)
					data->img_bfr[py * WINDOW_WIDTH + px] = 0xFF0000;
			x++;
		}
		y++;
	}
	draw_line(data, data->player->px, data->player->py);
}

void	draw_map(t_data *data)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	data->img_ptr = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->img_bfr = (int *)mlx_get_data_addr(\
					data->img_ptr, &data->bpp, &data->sizeline, &data->endian);
	while (y < data->map_y)
	{
		x = 0;
		while (x < data->map_x)
		{
			if (data->map[y * data->map_x + x] == 1)
				color = 0xFFFFFF;
			else
				color = 0x000000;
			color_tile(x, y, color, data);
			//data->img_bfr[y * WINDOW_WIDTH + x] = color;
			x++;
		}
		y++;
	}
	draw_player(data);
	raytrace(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
}

void	initialize_mlx(t_data *data, char *name)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		exit (EXIT_FAILURE);
	data->win_ptr = mlx_new_window(data->mlx_ptr, \
						WINDOW_WIDTH, WINDOW_HEIGHT, name);
	if (!data->win_ptr)
	{
		free(data->mlx_ptr);
		exit (EXIT_FAILURE);
	}
	data->img_ptr = NULL;
	data->map_x = 8;
	data->map_y = 8;
	data->tile_size = 64;
	init_player(data);
}

int	main(void)
{
	t_data		data;
	t_player	player;
	int map[]= {
				1,1,1,1,1,1,1,1,
				1,0,1,0,0,0,0,1,
				1,0,1,0,0,2,0,1,
				1,0,1,0,0,0,0,1,
				1,0,0,0,0,0,0,1,
				1,0,0,0,0,1,0,1,
				1,0,0,0,0,0,0,1,
				1,1,1,1,1,1,1,1,	
				};
	
	data.player = &player;
	data.map = map;
	initialize_mlx(&data, "Cube3D");
	draw_map(&data);
	events_init(&data);
	mlx_loop(data.mlx_ptr);
}