/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:53:39 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/08 17:53:39 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	render_map(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			mlx_put_image_to_window(data->mlx, data->win, data->img_floor, x * data->tile_size, y * data->tile_size);
			if (data->map[y][x] == '1')
				mlx_put_image_to_window(data->mlx, data->win, data->img_wall, x * data->tile_size, y * data->tile_size);
			if (data->map[y][x] == 'P')
				mlx_put_image_to_window(data->mlx, data->win, data->img_player, x * data->tile_size, y * data->tile_size);
			if (data->map[y][x] == 'C')
				mlx_put_image_to_window(data->mlx, data->win, data->img_collectible, x * data->tile_size, y * data->tile_size);
			if (data->map[y][x] == 'E')
				mlx_put_image_to_window(data->mlx, data->win, data->img_exit, x * data->tile_size, y * data->tile_size);
			x++;
		}
		y++;
	}
}
