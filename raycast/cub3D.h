/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandie@student.42luxembourg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:53:15 by rpandipe          #+#    #+#             */
/*   Updated: 2024/09/16 16:08:39 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "./libft/libft.h"
# include "./mlx/mlx.h"

# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 500
# define PI 3.14159265358979

typedef	struct	s_player
{
	double	px;
	double	py;
	int		size;
	double	pdx;
	double	pdy;
	double	pa;
	int		speed;
	double	rot_speed;
	int		line;
} t_player;

typedef struct	s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	int			*img_bfr;
	int			bpp;
	int			sizeline;
	int			endian;
	int			map_x; //add number of rows in the given map
	int			map_y; // number of cols
	int			tile_size; // number of pixels to color. needs a generic approach
	double		rx;
	double		ry;
	double		ra;
	double		dis_h;
	double		dis_v;
	int			*map;
	int			rays_count;
	double		fov;
	t_player	*player;
}	t_data;

void	draw_map(t_data *data);
void	draw_line(t_data *data, int x0, int y0);
void	raytrace(t_data *data);