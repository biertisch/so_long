/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:05:02 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/07 13:05:02 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	create_image_buffer(t_data *data, t_image *dest)
{
	dest->img = mlx_new_image(data->mlx, TILE_SIZE, TILE_SIZE);
	if (!dest->img)
		error_exit(data, "Error: Failed to create image buffer\n");
	dest->addr = mlx_get_data_addr(dest->img, &dest->bpp, &dest->line_len,
			&dest->endian);
	if (!dest->addr)
		error_exit(data, "Error failed to access image buffer\n");
	dest->width = TILE_SIZE;
	dest->height = TILE_SIZE;
}

static t_image	process_raw_image(t_data *data, char *filename)
{
	t_image	raw;

	raw.img = mlx_xpm_file_to_image(data->mlx, filename, &raw.width,
			&raw.height);
	if (!raw.img)
		error_exit(data, "Error: Failed to load image\n");
	if (raw.width != TILE_SIZE || raw.height != TILE_SIZE)
	{
		mlx_destroy_image(data->mlx, raw.img);
		error_exit(data, "Error: Tile size mismatch\n");
	}
	raw.addr = mlx_get_data_addr(raw.img, &raw.bpp, &raw.line_len,
			&raw.endian);
	if (!raw.addr)
	{
		mlx_destroy_image(data->mlx, raw.img);
		error_exit(data, "Error: Failed to access image data\n");
	}
	return (raw);
}

static void	load_image(t_data *data, t_image *dest, t_image *floor,
	char *filename)
{
	t_image	src;

	src = process_raw_image(data, filename);
	create_image_buffer(data, dest);
	if (floor && dest->img != floor->img)
		draw_with_transparency(dest, floor);
	draw_with_transparency(dest, &src);
	mlx_destroy_image(data->mlx, src.img);
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
	load_image(data, &data->floor, NULL, "textures/floor.xpm");
	load_image(data, &data->wall, &data->floor, "textures/wall.xpm");
	load_image(data, &data->player, &data->floor, "textures/player.xpm");
	load_image(data, &data->collect, &data->floor, "textures/collect.xpm");
	load_image(data, &data->exit, &data->floor, "textures/exit.xpm");
}
