/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:27:22 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/08 16:27:22 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	load_img(t_data *data, void **img, char *filename)
{
	int	w;
	int	h;

	*img = mlx_xpm_file_to_image(data->mlx, filename, &w, &h);
	if (!*img)
		error_exit(data, "Error: Failed to load image\n");
	if (w != data->tile_size || h != data->tile_size)
    	error_exit(data, "Error: Tile size mismatch\n");
}

void	init_mlx_data(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		error_exit(data, "Error: Failed to initiate mlx connection\n");
	data->win_size.row = data->map_size.row * data->tile_size;
	data->win_size.col = data->map_size.col * data->tile_size;
	data->win = mlx_new_window(data->mlx, data->win_size.col,
		data->win_size.row, "So Long");
	if (!data->win)
		error_exit(data, "Error: Failed to create window\n");
	load_img(data, &data->img_floor, "textures/floor.xpm");	
	load_img(data, &data->img_wall, "textures/wall.xpm");
	load_img(data, &data->img_player, "textures/player.xpm");
	load_img(data, &data->img_collectible, "textures/collectible.xpm");
	load_img(data, &data->img_exit, "textures/exit.xpm");
	if (!data->img_floor || !data->img_wall || !data->img_player
		|| !data->img_exit || !data->img_collectible)
		error_exit(data, "Error: Failed to convert images\n");
}
