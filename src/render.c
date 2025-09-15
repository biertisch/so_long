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

int	render_counter(t_data *data, int n, int x)
{
	int	digits[10];
	int	len;	

	len = 0;
	if (n == 0)
		digits[len++] = 0;
	while (n > 0)
	{
		digits[len++] = n % 10;
		n /= 10;
	}
	while (--len >= 0)
	{
		mlx_put_image_to_window(data->mlx, data->win.ptr,
			data->chars[digits[len]].img, x, 0);
		x += 16;
	}
	return (x);
}

static void	render_ent(t_data *data, t_ent *ent, char id, int extra_layer)
{
	int	x;
	int	y;

	x = ent->col * TILE_SIZE;
	y = ent->row * TILE_SIZE + TILE_SIZE / 2;
	if (id == 'E')
		mlx_put_image_to_window(data->mlx, data->win.ptr,
			ent->exit_layer[ent->current_dir][ent->current_frame].img, x, y);
	else if (id == 'C' && extra_layer)
		mlx_put_image_to_window(data->mlx, data->win.ptr,
			ent->collect_layer[ent->current_dir][ent->current_frame].img, x, y);
	else
		mlx_put_image_to_window(data->mlx, data->win.ptr,
			ent->frames[ent->current_dir][ent->current_frame].img, x, y);
}

static void	render_env(t_data *data, char c, int i, int j)
{
	int	x;
	int	y;

	x = j * TILE_SIZE;
	y = i * TILE_SIZE + TILE_SIZE / 2;
	mlx_put_image_to_window(data->mlx, data->win.ptr, data->floor.img, x, y);
	if (c == '1')
		mlx_put_image_to_window(data->mlx, data->win.ptr,
			data->wall.frames[data->wall.current_frame].img, x, y);
	else if (c == 'C')
		mlx_put_image_to_window(data->mlx, data->win.ptr, data->collect.img, x,
			y);
	else if (c == 'E')
		mlx_put_image_to_window(data->mlx, data->win.ptr, data->exit.img, x, y);
}

void	render_map(t_data *data, char **map)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			render_env(data, map[i][j], i, j);
			if (data->player.row == i && data->player.col == j)
				render_ent(data, &data->player, map[i][j], 0);
			k = 0;
			while (k < data->enemy_count)
			{
				if (i != 0 && j != 0 && data->enemy[k].row == i
					&& data->enemy[k].col == j)
					render_ent(data, &data->enemy[k], map[i][j], 1);
				k++;
			}
			j++;
		}
		i++;
	}
}
