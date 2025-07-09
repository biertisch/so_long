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

static void	draw_object(t_data *data, char c, int x, int y)
{
	if (c == '1')
		mlx_put_image_to_window(data->mlx, data->win, data->img_wall, x, y);
	else if (c == 'P')
		mlx_put_image_to_window(data->mlx, data->win, data->img_player, x, y);
	else if (c == 'C')
		mlx_put_image_to_window(data->mlx, data->win, data->img_collect, x, y);
	else if (c == 'E')
		mlx_put_image_to_window(data->mlx, data->win, data->img_exit, x, y);
}

void	render_map(t_data *data)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			x = j * TILE_SIZE;
			y = i * TILE_SIZE;
			mlx_put_image_to_window(data->mlx, data->win, data->img_floor, x,
				y);
			draw_object(data, data->map[i][j], x, y);
			j++;
		}
		i++;
	}
}
