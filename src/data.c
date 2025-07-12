/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:53:21 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/12 13:53:21 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	init_mlx_data(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		error_exit(data, "Error: Failed to initiate mlx connection\n");
	data->win_width = data->map_width * TILE_SIZE;
	data->win_height = data->map_height * TILE_SIZE;
	data->win = mlx_new_window(
		data->mlx,
		data->win_width,
		data->win_height,
		"So Long");
	if (!data->win)
		error_exit(data, "Error: Failed to create window\n");
	load_image(data, &data->floor, 0, "textures/floor.xpm");
	load_image(data, &data->collect, 1, "textures/collectible.xpm");
	load_exit_frames(data);
	load_wall_frames(data);
	load_player_frames(data);
}

static void	count_collectibles(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'C')
				data->collectibles++;
			j++;
		}
		i++;
	}
}

static void	set_player_position(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'P')
			{
				data->player_row = i;
				data->player_col = j;
			}
			j++;
		}
		i++;
	}
}

static void	set_map_size(t_data *data)
{
	int	i;

	i = 0;
	data->map_width = ft_strlen(data->map[i]);
	while (data->map[i++])
		data->map_height++;
}

void	init_map_data(t_data *data)
{
	set_map_size(data);
	set_player_position(data);
	count_collectibles(data);
}