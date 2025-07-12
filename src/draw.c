/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:00:17 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/09 16:00:17 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static unsigned int	get_pixel(t_image *img, int row, int col)
{
	char			*pixel;
	unsigned int	color;

	if (row < 0 || row >= img->height || col < 0 || col >= img->height)
		return (0);
	pixel = img->addr + (row * img->line_len + col * (img->bpp / 8));
	color = *(unsigned int *)pixel;
	return (color);
}

static void	set_pixel(t_image *img, int row, int col, unsigned int color)
{
	char	*pixel;

	if (row < 0 || row >= img->height || col < 0 || col >= img->height)
		return ;
	pixel = img->addr + (row * img->line_len + col * (img->bpp / 8));
	*(unsigned int *)pixel = color;
}

void	draw_with_transparency(t_image *dest, t_image *src)
{
	int				row;
	int				col;
	unsigned int	color;

	row = 0;
	while (row < src->height)
	{
		col = 0;
		while (col < src->width)
		{
			color = get_pixel(src, row, col);
			if (color != MAGIC_COLOR)
				set_pixel(dest, row, col, color);
			col++;
		}
		row++;
	}
}

void	create_image_buffer(t_data *data, t_image *dest)
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

t_image	process_raw_image(t_data *data, char *filename)
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
