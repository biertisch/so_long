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
		mlx_put_image_to_window(data->mlx, data->win,
			data->chars[digits[len]].img, x, 0);
		x += 16;
	}
	return (x);
}

static void	render_enemy(t_data *data, t_ent_anim *enemy, char c)
{
	int	dir;
	int	frame;
	int	x;
	int	y;

	dir = enemy->current_dir;
	frame = enemy->current_frame;
	x = enemy->col * TILE_SIZE;
	y = enemy->row * TILE_SIZE + TILE_SIZE / 2;
	if (c == 'E')
		mlx_put_image_to_window(data->mlx, data->win,
			enemy->exit_layer[dir][frame].img, x, y);
	else if (c == 'C')
		mlx_put_image_to_window(data->mlx, data->win,
			enemy->collect_layer[dir][frame].img, x, y);
	else
		mlx_put_image_to_window(data->mlx, data->win,
			enemy->frames[dir][frame].img, x, y);
}

static void	render_player(t_data *data, char c)
{
	int	dir;
	int	frame;
	int	x;
	int	y;

	dir = data->player.current_dir;
	frame = data->player.current_frame;
	x = data->player.col * TILE_SIZE;
	y = data->player.row * TILE_SIZE + TILE_SIZE / 2;
	if (c == 'E')
		mlx_put_image_to_window(data->mlx, data->win,
			data->player.exit_layer[dir][frame].img, x, y);
	else
		mlx_put_image_to_window(data->mlx, data->win,
			data->player.frames[dir][frame].img, x, y);
}

static void	render_environment(t_data *data, char c, int i, int j)
{
	int	x;
	int	y;

	x = j * TILE_SIZE;
	y = i * TILE_SIZE + TILE_SIZE / 2;
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
	int	k;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			render_environment(data, data->map[i][j], i, j);
			if (data->player.row == i && data->player.col == j)
				render_player(data, data->map[i][j]);
			k = 0;
			while (k < data->enemy_count)
			{
				if (i != 0 && j != 0 && data->enemy[k].row == i
					&& data->enemy[k].col == j)
					render_enemy(data, &data->enemy[k], data->map[i][j]);
				k++;
			}
			j++;
		}
		i++;
	}
}
