/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_cub_scene.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:14:26 by thomas            #+#    #+#             */
/*   Updated: 2024/10/24 15:02:35 by tle-moel         ###   ########.fr       */
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
		init_horizontal_ray(data, &ray_h, data->player.x, data->player.y);
		determine_hit_ray(data, &ray_h);
		calculate_distance(data, &ray_h);
		init_vertical_ray(data, &ray_v, data->player.x, data->player.y);
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
	(void)r;
	if (ray_v.dist < ray_h.dist)
	{
		draw_line(data, ray_v.x * PIXELS_PER_CELL, ray_v.y * PIXELS_PER_CELL, convert_color(0, 0, 128, 0));
		draw_wall_slice(data, ray_v, r);
	}
	else
	{
		draw_line(data, ray_h.x * PIXELS_PER_CELL, ray_h.y * PIXELS_PER_CELL, convert_color(0, 0, 128, 0));
		draw_wall_slice(data, ray_h, r);
	}
}
