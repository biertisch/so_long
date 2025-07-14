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
