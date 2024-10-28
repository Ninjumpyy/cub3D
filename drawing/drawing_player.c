/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:53:15 by rpandipe          #+#    #+#             */
/*   Updated: 2024/10/28 14:41:12 by rpandipe         ###   ########.fr       */
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

void	draw_player_pixels(int xy[2], t_img *img, int pxy[2], t_data *data)
{
	char	*src_pixel;
	char	*dst_pixel;
	int		dst_x;
	int		dst_y;
	int		color;

	src_pixel = img->addr + (xy[1] * img->line_size + xy[0] * \
							(img->bits_per_pixel / 8));
	color = *(unsigned int *)src_pixel;
	dst_x = (int)(pxy[0] + xy[0]);
	dst_y = (int)(pxy[1] + xy[1]);
	if (dst_x >= 0 && dst_x < CUB_WIDTH && dst_y >= 0 && dst_y < CUB_HEIGHT)
	{
		if (((color >> 24) & 0xFF) == 0)
		{
			dst_pixel = data->cub.addr + ((int)(pxy[1] + xy[1]) *\
						data->cub.line_size + (int)(pxy[0] + xy[0]) *\
						(data->cub.bits_per_pixel / 8));
			*(unsigned int *)dst_pixel = color;
		}
	}
}

void	draw_player_sprite(t_data *data, t_img *img)
{
	int		x;
	int		y;
	float	px;
	float	py;

	y = 0;
	px = (CUB_WIDTH / 2) - (img->width / 2);
	py = (CUB_HEIGHT) - (img->height);
	if (px < 0 || px >= CUB_WIDTH || py < 0 || py >= CUB_HEIGHT)
		return ;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			draw_player_pixels((int[2]){x, y}, img, (int[2]){px, py}, data);
			x++;
		}
		y++;
	}
}
