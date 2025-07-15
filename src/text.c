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

	load_text_image(data, &data->black, "textures/text/black.xpm");
	load_text_image(data, &data->move_counter,
		"textures/text/move_counter.xpm");
	load_text_image(data, &data->collect_counter,
		"textures/text/collect_counter.xpm");
	load_text_image(data, &data->closed_exit, "textures/text/closed_exit.xpm");
	load_text_image(data, &data->victory, "textures/text/victory.xpm");
	load_text_image(data, &data->defeat, "textures/text/defeat.xpm");
	data->chars = ft_calloc(sizeof(t_image), CHAR_FRAMES);
	if (!data->chars)
		error_exit(data, "Error: Memory allocation failed\n");
	i = 0;
	while (i < CHAR_FRAMES)
	{
		build_char_filename(path, i);
		load_text_image(data, &data->chars[i], path);
		i++;
	}
}
