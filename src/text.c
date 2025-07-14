/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:18:19 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/14 16:18:19 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	load_text_image(t_data *data, t_image *text, char *filename)
{
	text->img = mlx_xpm_file_to_image(data->mlx, filename, &text->width,
		&text->height);
	if (!text->img)
		error_exit(data, "Error: Failed to load image\n");
}

void	load_text(t_data *data)
{
	char	path[64];
	int		i;
	
	load_text_image(data, &data->text_background, "textures/text_background.xpm");
	load_text_image(data, &data->text_moves, "textures/text_moves.xpm");
	load_text_image(data, &data->text_closed_exit, "textures/text_closed_exit.xpm");
	load_text_image(data, &data->text_victory, "textures/text_victory.xpm");
	load_text_image(data, &data->text_defeat, "textures/text_defeat.xpm");
	data->chars = malloc(sizeof(t_image) * 10);
	if (!data->chars)
		error_exit(data, "Error: Memory allocation failed\n");
	i = 0;
	while (i < 10)
	{
		build_char_filename(path, i);
		load_text_image(data, &data->chars[i], path);
		i++;
	}
}
