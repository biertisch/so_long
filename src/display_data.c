/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:05:02 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/07 13:05:02 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	load_image(t_data *data, void **img, char *filename)
{
	int	w;
	int	h;

	*img = mlx_xpm_file_to_image(data->mlx, filename, &w, &h);
	if (!*img)
		error_exit(data, "Error: Failed to load image\n");
	if (w != TILE_SIZE || h != TILE_SIZE)
		error_exit(data, "Error: Tile size mismatch\n");
}

void	init_display_data(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		error_exit(data, "Error: Failed to initiate mlx connection\n");
	data->win_width = data->map_width * TILE_SIZE;
	data->win_height = data->map_height * TILE_SIZE;
	data->win = mlx_new_window(data->mlx, data->win_width, data->win_height,
			"So Long");
	if (!data->win)
		error_exit(data, "Error: Failed to create window\n");
	load_image(data, &data->img_floor, "textures/floor.xpm");
	load_image(data, &data->img_wall, "textures/wall.xpm");
	load_image(data, &data->img_player, "textures/player.xpm");
	load_image(data, &data->img_collect, "textures/collect.xpm");
	load_image(data, &data->img_exit, "textures/exit.xpm");
	if (!data->img_floor || !data->img_wall || !data->img_player
		|| !data->img_exit || !data->img_collect)
		error_exit(data, "Error: Failed to convert images\n");
}
