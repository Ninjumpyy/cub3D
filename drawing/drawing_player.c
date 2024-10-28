/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:53:15 by rpandipe          #+#    #+#             */
/*   Updated: 2024/10/28 11:42:55 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	draw_player(t_data *data)
{
	float	px;
	float	py;
	int		i;
	int		j;

	px = (data->player.x * PIXELS_PER_CELL) - data->player.offset_x
		- (SIZE_PIXEL_PLAYER / 2);
	py = (data->player.y * PIXELS_PER_CELL) - data->player.offset_y
		- (SIZE_PIXEL_PLAYER / 2);
	j = 0;
	while (j < SIZE_PIXEL_PLAYER)
	{
		i = 0;
		while (i < SIZE_PIXEL_PLAYER)
		{
			draw_pixel(&(data)->minimap, (int)px + i, (int)py + j,
				convert_color(122, 255, 255, 0));
			i++;
		}
		j++;
	}
}

void	draw_player_sprite(t_data *data, t_img *img)
{
	int		x;
	int		y;
	char	*src_pixel;
	char	*dst_pixel;
	float	px;
	float	py;
	int		color;

	y = 0;
	px = (CUB_WIDTH / 2) - (img->width / 2);
	py = (CUB_HEIGHT) - (img->height);
	if (px < 0 || px >= CUB_WIDTH || py < 0 || py >= CUB_HEIGHT)
	{
		printf("Player position is out of bounds, px: %f, py: %f\n", px, py);
        return;
	}
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			src_pixel = img->addr + (y * img->line_size + x * (img->bits_per_pixel / 8));
			color = *(unsigned int *)src_pixel;
			int dst_x = (int)(px + x);
            int dst_y = (int)(py + y);

            if (dst_x >= 0 && dst_x < CUB_WIDTH && dst_y >= 0 && dst_y < CUB_HEIGHT)
			{
				if (((color >> 24) & 0xFF) == 0)
				{
					dst_pixel = data->cub.addr + ((int)(py + y) * data->cub.line_size + (int)(px + x) * (data->cub.bits_per_pixel / 8));
					*(unsigned int *)dst_pixel = color;
				}
			}
			x++;
		}
		y++;
	}
}
