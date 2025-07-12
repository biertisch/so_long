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

static void	render_player(t_data *data, char c, int x, int y)
{
	char	path[64];
	int		dir;
	int		frame;

	dir = data->player.current_dir;
	frame = data->player.current_frame;
	if (c == 'E')
	{
		if (data->player.on_exit_frame.img)
			mlx_destroy_image(data->mlx, data->player.on_exit_frame.img);
		build_ent_filename(path, "player", dir, frame);
		load_image(data, &data->player.on_exit_frame, 2, path);
		mlx_put_image_to_window(data->mlx, data->win, 
			data->player.on_exit_frame.img, x, y);
	}
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
		mlx_put_image_to_window(data->mlx, data->win,
			data->exit.frames[data->exit.current_frame].img, x, y);
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
			render_environment(data, data->map[i][j], x, y);
			if (data->player_row == i && data->player_col == j)
				render_player(data, data->map[i][j], x, y);
			j++;
		}
		i++;
	}
}
