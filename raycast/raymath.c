/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raymath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandie@student.42luxembourg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:49:58 by rpandipe          #+#    #+#             */
/*   Updated: 2024/09/17 00:35:47 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	cast_horizontal(t_data *data, int yo, int dof)
{
	int	xo;
	int	mx;
	int	my;
	
	if (sin (data->ra) > 0)
	{
		data->ry = ((data->player->py / 64.0) * 64.0 - 0.0001);
		yo = -64;
		data->rx = data->player->px + (data->ry - data->player->py) / tan(data->ra);
	}
	else if (sin (data->ra) < 0)
	{
		data->ry = ((data->player->py * 64.0)) + 64.0;
		data->rx = data->player->px + (data->ry - data->player->py) / tan(data->ra);
	}
	else
	{
		data->rx = data->player->px;
		data->ry = data->player->py;
		dof = 8;
	}
	xo = yo / (tan (data->ra));
	while (dof < 8)
	{
		mx = (int) data->rx / 64.0;
		my = (int) data->ry / 64.0;
		if (mx >=0 && mx < data->map_x && my >= 0 && my < data->map_y && data->map[my * data->map_x + mx] == 1)
			dof = 8;
		else
		{
			data->rx += xo;
			data->ry += yo;
			dof++;
		}
	}
	return (sqrt(((data->rx - data->player->px) * (data->rx - data->player->px) + (data->ry - data->player->py) * (data->ry - data->player->py))) * cos(data->player->pa - data->ra));
}

double	cast_vertical(t_data *data, int xo, int dof)
{
	int	yo;
	int	mx;
	int	my;
	
	if (cos (data->ra) < 0)
	{
		data->rx = ((data->player->px / 64.0) * 64.0 - 0.0001);
		xo = -64;
		data->ry = data->player->py \
					+  (data->rx - data->player->px) * (tan (data->ra));
	}
	else if (cos (data->ra) > 0)
	{
		data->rx = ((data->player->px * 64.0)) + 64.0;
		data->ry = data->player->py \
					+ (data->rx - data->player->px) * (tan (data->ra));
	}
	else
	{
		data->rx = data->player->px;
		data->ry = data->player->py;
		dof = 8;
	}
	yo = xo * (tan (data->ra));
	while (dof < 8)
	{
		mx = (int) data->rx / 64.0;
		my = (int) data->ry / 64.0;
		if (mx >=0 && mx < data->map_x && my >= 0 && my < data->map_y && data->map[my * data->map_x + mx] == 1)
			dof = 8;
		else
		{
			data->rx += xo;
			data->ry += yo;
			dof++;
		}
	}
	return (sqrt((data->rx - data->player->px) * (data->rx - data->player->px) + (data->ry - data->player->py) * (data->ry - data->player->py)) * cos(data->player->pa - data->ra));
}

void draw_wall(t_data *data, double ray_dist, int ray_index)
{
    int wall_height;
    int line_start;
    int line_end;
    int screen_half_height = WINDOW_HEIGHT / 2;
    int mex = (data->map_x * data->tile_size) + 20;  // Start rendering after the map on the right half of the screen
    int column_start = mex + ray_index * (WINDOW_WIDTH - mex) / data->rays_count;  // Column for this ray

    // Calculate the wall height based on distance (inverse proportion for 3D effect)
    wall_height = (int)(64 * WINDOW_HEIGHT / ray_dist);  // 64 is the wall size in the world

    // Calculate where the wall should start and end vertically
    line_start = screen_half_height - wall_height / 2;
    line_end = screen_half_height + wall_height / 2;

    // Ensure the line is within the screen boundaries
    if (line_start < 0)
        line_start = 0;
    if (line_end >= WINDOW_HEIGHT)
        line_end = WINDOW_HEIGHT - 1;

    // Draw the vertical wall slice (thick line for 3D effect)
    for (int y = line_start; y < line_end; y++)
    {
        for (int column = column_start; column < column_start + (WINDOW_WIDTH - mex) / data->rays_count; column++)
        {
            if (column < WINDOW_WIDTH && y < WINDOW_HEIGHT)
            {
                data->img_bfr[y * WINDOW_WIDTH + column] = 0xFF00FF;  // Wall color (purple)
            }
        }
    }
}

void	raytrace(t_data *data)
{
	int	i;
	int	yo;
	int	dof;
	double	ray_dist;
	double	ray_step;

	i = -1;
	yo = 64;
	dof = 0;
	data->ra = data->player->pa - (data->fov / 2);
	ray_step = data->fov / data->rays_count;
	while (++i < data->rays_count)
	{
		data->dis_h = cast_horizontal(data, yo, dof);
		data->dis_v = cast_vertical(data, yo, dof);
		ray_dist = data->dis_h;
		if (data->dis_v < data->dis_h)
			ray_dist = data->dis_v;
		//ray_dist *= cos(data->player->pa - data->ra);
		draw_wall(data, ray_dist, i);
		data->ra += ray_step;
	}
}
