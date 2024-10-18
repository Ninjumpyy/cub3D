/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_cub_scene.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:14:26 by thomas            #+#    #+#             */
/*   Updated: 2024/10/18 16:37:45 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	draw_cub_scene(t_data *data)
{
	int	r;
	t_ray	ray_h;
	t_ray	ray_v;
	float	da;

	r = 0;
	init_ray_data(data, &ray_h, 0, HORIZONTAL);
	init_ray_data(data, &ray_v, 0, VERTICAL);
	da = (DR * FOV) / CUB_WIDTH;
	while (r < CUB_WIDTH)
	{
		init_ray_data(data, &ray_h, 1, HORIZONTAL);
		init_ray_data(data, &ray_v, 1, VERTICAL);
		init_horizontal_ray(data, &ray_h, data->player.x * PIXELS_PER_CELL, data->player.y * PIXELS_PER_CELL);
		determine_hit_ray(data, &ray_h);
		calculate_distance(data, &ray_h);
		init_vertical_ray(data, &ray_v, data->player.x * PIXELS_PER_CELL, data->player.y * PIXELS_PER_CELL);
		determine_hit_ray(data, &ray_v);
		calculate_distance(data, &ray_v);
		process_and_draw_wall_slice(data, ray_v, ray_h, r);
		r++;
		ray_h.angle += da;
		normalize_angle(&ray_h);
		ray_v.angle = ray_h.angle;
	}
}

void	process_and_draw_wall_slice(t_data *data, t_ray ray_v, t_ray ray_h, int r)
{
	if (ray_v.dist < ray_h.dist)
	{
		draw_line(data, (int)ray_v.x, (int)ray_v.y, convert_color(0, 128, 0));
		draw_cub(data, ray_v, r);
	}
	else
	{
		draw_line(data, (int)ray_h.x, (int)ray_h.y, convert_color(0, 128, 0));
		draw_cub(data, ray_h, r);
	}
}

void	draw_cub(t_data *data, t_ray ray, int r)
{
	float	line_height;
	int		y_start;
	int		y_end;
	int		y;
	float	wall_hit_x;
	int		tex_x;
	int		tex_y;
	float	tex_pos;
	float	tex_step;
	int		color;

	line_height = (TILE_SIZE * CUB_HEIGHT) / (ray.dist * cos(data->player.angle - ray.angle));

	tex_step = (float)ray.text.height / line_height;

	if (line_height > CUB_HEIGHT)
	{
		tex_pos = (line_height - CUB_HEIGHT) / 2 * tex_step;
		line_height = CUB_HEIGHT;
	}
	else
		tex_pos = 0;
	
	y_start = (CUB_HEIGHT - line_height) / 2;
	if (y_start < 0)
    {
        tex_pos += -y_start * tex_step;
        y_start = 0;
    }
	y_end = y_start + line_height;
	if (y_end > CUB_HEIGHT)
		y_end = CUB_HEIGHT;

	if (ray.type == VERTICAL)
	{
		ray.y /= 32;
		wall_hit_x = ray.y - (int)ray.y;
	}
	else
	{
		ray.x /= 32;
		wall_hit_x = ray.x - (int)ray.x;
	}

	tex_x = (int)(wall_hit_x * ray.text.width);
	
	y = y_start;
	while (y < y_end)
	{
		tex_y = (int)tex_pos % ray.text.height;
		tex_pos += tex_step;

		color = get_texture_color(&ray.text, tex_x, tex_y);
		draw_pixel(&(data)->cub, r, y, color);
		y++;
	}
}


int get_texture_color(t_text *texture, int x, int y)
{
    char    *pixel;
    int     color;

    pixel = texture->addr + (y * texture->line_size + x * (texture->bits_per_pixel / 8));
    color = *(int *)pixel;
    return (color);
}

