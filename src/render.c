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

static void	render_enemy(t_data *data, char c, int x, int y)
{
	int		dir;
	int		frame;
	
	dir = data->enemy.current_dir;
	frame = data->enemy.current_frame;
	if (c == 'E')
		mlx_put_image_to_window(data->mlx, data->win,
			data->enemy.exit_layer[dir][frame].img, x, y);
	else if (c == 'C')
		mlx_put_image_to_window(data->mlx, data->win,
			data->enemy.collect_layer[dir][frame].img, x, y);
	else
		mlx_put_image_to_window(data->mlx, data->win,
			data->enemy.frames[dir][frame].img, x, y);
}

static void	render_player(t_data *data, char c, int x, int y)
{
	int		dir;
	int		frame;

	dir = data->player.current_dir;
	frame = data->player.current_frame;
	if (c == 'E')
		mlx_put_image_to_window(data->mlx, data->win,
			data->player.exit_layer[dir][frame].img, x, y);
	else
		mlx_put_image_to_window(data->mlx, data->win,
			data->player.frames[dir][frame].img, x, y);
}

static void	render_environment(t_data *data, char c, int x, int y)
{
	mlx_put_image_to_window(data->mlx, data->win, data->floor.img, x, y);
	if (c == '1')
		mlx_put_image_to_window(data->mlx, data->win,
			data->wall.frames[data->wall.current_frame].img, x, y);
	else if (c == 'C')
		mlx_put_image_to_window(data->mlx, data->win, data->collect.img, x, y);
	else if (c == 'E')
		mlx_put_image_to_window(data->mlx, data->win, data->exit.img, x, y);
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
			y = i * TILE_SIZE + TILE_SIZE / 2;
			render_environment(data, data->map[i][j], x, y);
			if (data->player.row == i && data->player.col == j)
				render_player(data, data->map[i][j], x, y);
			if (i != 0 && j != 0 &&	data->enemy.row == i && data->enemy.col == j)
				render_enemy(data, data->map[i][j], x, y);
			j++;
		}
		i++;
	}
}
